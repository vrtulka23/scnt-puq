#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <limits>
#include <chrono>
#include <ctime>    

#include "../../src/quantity.h"
#include "../../src/nostd/nostd.h"
#include "../../src/solver/solver.h"
#include "../../src/lists/lists.h"

void add_line(std::stringstream& ss, const std::string& symbol, puq::Dimensions& dim, const std::string& name) {
  ss << "{";
  ss << std::setfill(' ') << std::setw(15)  << std::left;
  ss << "\""+symbol+"\",";
  ss << "{";
  int precision = std::numeric_limits<MAGNITUDE_PRECISION>::digits10;
  ss << std::setfill(' ') << std::setw(25)  << std::left;
  ss << puq::nostd::to_string(dim.numerical.value[0], precision)+",";
  ss << std::setfill(' ') << std::setw(25)  << std::left;
  ss << puq::nostd::to_string(dim.numerical.error[0], precision)+",";
  ss << "{";
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (i>0)
      ss << ",";
    ss << std::setfill(' ') << std::setw(2) << std::right;
    if (dim.physical[i].denominator==1) {
      ss << dim.physical[i];
    } else {
      ss << "(FRC){" + std::to_string(dim.physical[i].numerator) + "," + std::to_string(dim.physical[i].denominator) + "}";
    }
  }
  ss << "} } },     // "+name+"\n";
  //std::cout << ss.str() << std::endl;
}

void solve_bu_prefix(puq::Dimensions& dim, puq::BaseUnit& bu) {
  auto prefix = puq::UnitPrefixList.find(bu.prefix);
  if (prefix!=puq::UnitPrefixList.end()) {
    dim.numerical *= puq::nostd::pow(prefix->second.magnitude, (puq::EXPONENT_TYPE)bu.exponent );
  }
}

bool solve_bu_unit(puq::DimensionMapType& dmap, puq::Dimensions& dim, puq::BaseUnit& bu) {
  auto it = dmap.find(bu.unit);
  if (it != dmap.end()) {
#ifdef MAGNITUDE_ERRORS
    puq::MAGNITUDE_TYPE m(it->second.magnitude, it->second.error);
#else
    puq::MAGNITUDE_TYPE m(it->second.magnitude);
#endif
    dim.numerical *= puq::nostd::pow(m, (puq::EXPONENT_TYPE)bu.exponent);
    for (int i=0; i<NUM_BASEDIM; i++) {
      dim.physical[i] += it->second.dimensions[i] * bu.exponent;
    }
    return true;
  }
  return false;
}

inline void solve_units(std::stringstream& ss, puq::DimensionMapType& dmap, puq::UnitSolver& solver) {
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    if (dmap.find(unit.first)!=dmap.end())
      continue;
    if ((unit.second.utype & puq::Utype::BAS)==puq::Utype::BAS)  
      continue;
    puq::UnitAtom atom = solver.solve(unit.second.definition);
    puq::Dimensions dim(atom.value.magnitude);
    std::string missing = "";
    for (auto bu: atom.value.baseunits) {
      solve_bu_prefix(dim, bu);
      if (!solve_bu_unit(dmap, dim, bu)) {
	missing = bu.unit;
	break;
      }
    }
    if ((unit.second.utype & puq::Utype::LOG)==puq::Utype::LOG)
      dim.numerical = 1; // for logarithmic units this has to be 1
    if (missing=="") {
      add_line(ss, unit.first, dim, unit.second.name);
      dmap.insert({unit.first, {dim.numerical.value[0], dim.numerical.error[0], dim.physical}});
    }
  }
}

inline void solve_quantities(std::stringstream& ss, puq::DimensionMapType& dmap, puq::UnitSolver& solver) {
  std::cout << "Solving " << puq::UnitSystem::Data->SystemAbbrev << " system" << std::endl;
  for (auto quant: puq::UnitSystem::Data->QuantityList) {
    // solve a quantity definition
    puq::UnitAtom atom = solver.solve(quant.second.definition);
    puq::Dimensions dim(atom.value.magnitude);
    for (auto bu: atom.value.baseunits) {
      solve_bu_prefix(dim, bu);
      if (!solve_bu_unit(dmap, dim, bu)) {
	throw puq::DimensionMapExcept(puq::UnitSystem::Data->SystemAbbrev+" quantity '"+quant.first+
				      "' could not be constructued from a definition '"+
				      quant.second.definition+"'. Missing unit: "+bu.unit);
      }
    }
    std::string symbol = SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END;
    add_line(ss, symbol, dim, puq::QuantityNames.at(quant.first));
    dmap.insert({symbol, {dim.numerical.value[0], dim.numerical.error[0], dim.physical}});
    
    // solve a quantity IS conversion factor, if exists
    if (quant.second.sifactor!="") {
      atom = solver.solve(quant.second.sifactor);
      puq::UnitValue value = atom.value.convert(puq::Dformat::MKS);
      // here we are interested onlin in a dimensionless conversion factor into SI
      dim = puq::Dimensions(value.magnitude);
      symbol = SYMBOL_SIFACTOR_START+quant.first+SYMBOL_SIFACTOR_END;
      add_line(ss, symbol, dim, puq::QuantityNames.at(quant.first)+" SI factor");
      dmap.insert({symbol, {dim.numerical.value[0], dim.numerical.error[0], dim.physical}});
    }
  }
}

void create_map(const std::string file_header) {
  puq::UnitSolver solver;
  puq::DimensionMapType dmap;
  std::stringstream ss;
  // add dimension of base units
  for (auto d: puq::SystemData::_BASE_MAP) {
    dmap.insert(d);
    puq::Dimensions dim(d.second.magnitude, d.second.dimensions);
    std::string name;
    auto bu = puq::UnitSystem::Data->UnitList.at(d.first);
    add_line(ss, d.first, dim, bu.name);
  }
  // iterate over units until all are solved
  size_t nit = 0;
  size_t nmax = puq::UnitSystem::Data->UnitList.size();
  while (dmap.size() < nmax && nit < nmax) {
    nit++;
    solve_units(ss, dmap, solver);
  }
  // construct all quantities and their corresponding SI factors
  nmax += puq::UnitSystem::Data->QuantityList.size();
  solve_quantities(ss, dmap, solver);

  if (dmap.size() < nmax)
    throw puq::DimensionMapExcept("Dimension map is not complete: "+std::to_string(dmap.size())+"/"+std::to_string(nmax));

  // Write dimension map table
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  std::ofstream fs;
  fs.open(file_header, std::ios::out|std::ios::trunc);
  fs << "/*" << std::endl;
  fs << " * Do not modify this file!" << std::endl;
  fs << " * This file can be updated using 'dmap' executable." << std::endl;
  fs << " * " << std::endl;
  fs << " * Unit system:  " << puq::UnitSystem::Data->SystemName << " (" << puq::UnitSystem::Data->SystemAbbrev << ")" << std::endl;
  fs << " * Last update:  " << std::ctime(&now_time);
  fs << " * Code version: " << CODE_VERSION << std::endl;
  fs << " * " << std::endl;
  fs << " * Symbol legend:" << std::endl;
  fs << " * ..    units" << std::endl;
  fs << " * [..]  constants" << std::endl;
  fs << " * [#..] collapsed constants" << std::endl;
  fs << " * <..>  quantities" << std::endl;
  fs << " * |..|  quantity SI conversion factors" << std::endl;
  fs << " */" << std::endl;
  fs << ss.str();
  fs.close();
}

int main(int argc, char * argv[]) {

  std::cout << "Generating dimension maps:" << std::endl;
  for (auto sys: puq::SystemMap) {
    std::string file_header = "src/lists/dmaps/dmap_"+sys.second->SystemAbbrev+".h";
    puq::UnitSystem us(sys.first);
    create_map(file_header);
    std::cout << "Generating dmap file: " << file_header << std::endl;
  }
  
}
