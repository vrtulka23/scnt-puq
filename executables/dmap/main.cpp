#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <limits>
#include <chrono>
#include <ctime>    

#include "../../src/quantity.h"
#include "../../src/nostd.h"
#include "../../src/solver/solver.h"
#include "../../src/lists/lists.h"

void add_line(std::stringstream& ss, const std::string& symbol, puq::Dimensions& dim) {
  ss << "{";
  ss << std::setfill(' ') << std::setw(15)  << std::left;
  ss << "\""+symbol+"\",";
  ss << "{";
  ss << std::setfill(' ') << std::setw(25)  << std::left;
  ss << dim.to_string(puq::Dformat::NUM, std::numeric_limits<MAGNITUDE_PRECISION>::digits10)+",";
  ss << "{";
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (i>0)
      ss << ",";
    ss << std::setfill(' ') << std::setw(2) << std::right;
#ifdef EXPONENT_FRACTIONS
    if (dim.physical[i].denominator==1) {
      ss << dim.physical[i];
    } else {
      ss << "(FRC){" + std::to_string(dim.physical[i].numerator) + "," + std::to_string(dim.physical[i].denominator) + "}";
    }
#else
    ss << dim.physical[i];
#endif
  }
  ss << "} } },\n";
}

inline void solve_units(std::stringstream& ss, puq::DimensionMapType& dmap, puq::UnitSolver& solver) {
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    if (dmap.find(unit.symbol)!=dmap.end())
      continue;
    if ((unit.utype & puq::Utype::BAS)==puq::Utype::BAS)  
      continue;
    puq::UnitAtom atom = solver.solve(unit.definition);
    puq::Dimensions dim(atom.value.magnitude);
    std::string missing = "";
    for (auto bu: atom.value.baseunits) {
      // find prefix
      auto prefix = puq::UnitPrefixList.find(bu.prefix);
      if (prefix!=puq::UnitPrefixList.end()) {
	dim.numerical *= puq::nostd::pow(prefix->second.magnitude, (puq::EXPONENT_TYPE)bu.exponent);
      }
      // dimensions
      auto it = dmap.find(bu.unit);
      if (it != dmap.end()) {
	dim.numerical *= puq::nostd::pow(it->second.magnitude, (puq::EXPONENT_TYPE)bu.exponent);
	for (int i=0; i<NUM_BASEDIM; i++) {
	  dim.physical[i] += it->second.dimensions[i] * bu.exponent;
	}
      } else {
	missing = bu.unit;
	break;
      }
    }
    if ((unit.utype & puq::Utype::LOG)==puq::Utype::LOG)
      dim.numerical = 1; // for logarithmic units this has to be 1
    if (missing=="") {
      add_line(ss, unit.symbol, dim);
      dmap.insert({unit.symbol, {dim.numerical, dim.physical}});
    }
  }
}

inline void solve_quantities(std::stringstream& ss, puq::DimensionMapType& dmap, puq::UnitSolver& solver) {
  for (auto quant: puq::UnitSystem::Data->QuantityList) {
    puq::UnitAtom atom = solver.solve(quant.second.definition);
    puq::Dimensions dim(atom.value.magnitude);
    for (auto bu: atom.value.baseunits) {
      auto it = dmap.find(bu.unit);
      if (it != dmap.end()) {
	dim.numerical *= puq::nostd::pow(it->second.magnitude, (puq::EXPONENT_TYPE)bu.exponent);
	for (int i=0; i<NUM_BASEDIM; i++) {
	  dim.physical[i] += it->second.dimensions[i] * bu.exponent;
	}
      } else {
	throw puq::DimensionMapExcept("Quantity '"+quant.first+"' could not be constructued from a definition '"+quant.second.definition+"'. Missing unit: "+bu.unit);
      }
    }
    std::string symbol = SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END;
    add_line(ss, symbol, dim);
    dmap.insert({symbol, {dim.numerical, dim.physical}});
  }
}

void create_map(const std::string file_header) {
  puq::UnitSolver solver;
  puq::DimensionMapType dmap;
  size_t nit = 0;
  size_t nmax = puq::UnitSystem::Data->UnitList.size();
  std::stringstream ss;
  for (auto d: puq::SystemData::_BASE_MAP) {
    dmap.insert(d);
    puq::Dimensions dim(d.second.magnitude, d.second.dimensions);
    add_line(ss, d.first, dim);
  }
  while (dmap.size() < nmax && nit < nmax) {
    nit++;
    solve_units(ss, dmap, solver);
  }
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
  fs << " * Last modification: " << std::ctime(&now_time);
  fs << " * Code version: " << CODE_VERSION << std::endl;
  fs << " */" << std::endl;
  fs << ss.str();
  fs.close();
}

int main(int argc, char * argv[]) {

  std::cout << "Generating dimension maps:" << std::endl;
  for (auto sys: puq::SystemData::SystemMap) {
    std::string file_header = "src/lists/dmap_"+sys.first+".h";
    puq::UnitSystem us(*sys.second);
    create_map(file_header);
    std::cout << file_header << std::endl;
  }
  
}
