#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "lists.h"
#include "../nostd.h"
#include "../value/value.h"
#include "../solver/solver.h"

namespace puq {

  DimensionMap::DimensionMap() {
    file_table = "dimension_map_"+UnitSystem::Data->SystemAbbrev+".txt";
    file_data  = "dimension_map_"+UnitSystem::Data->SystemAbbrev+".dat";
    
    if (dmap.size()==0) {
      struct stat buffer;   
      if (stat(file_data.c_str(), &buffer) == 0) {
	_read_map();
      } else {
	_create_map();
	_write_map();
      }
    }
  }
  
  inline void _solve_units(DimensionMapType& dmap, std::stringstream& dmtable, UnitSolver& solver) {
    for (auto unit: UnitSystem::Data->UnitList) {
      if (dmap.find(unit.symbol)!=dmap.end())
	continue;
      if ((unit.utype & Utype::BAS)==Utype::BAS)  
	continue;
      UnitAtom atom = solver.solve(unit.definition);
      Dimensions dim(atom.value.magnitude);
      std::string missing = "";
      for (auto bu: atom.value.baseunits) {
	// find prefix
	auto prefix = UnitPrefixList.find(bu.prefix);
	if (prefix!=UnitPrefixList.end()) {
	  dim.numerical *= nostd::pow(prefix->second.magnitude, (EXPONENT_TYPE)bu.exponent);
	}
	// dimensions
	auto it = dmap.find(bu.unit);
	if (it != dmap.end()) {
	  dim.numerical *= nostd::pow(it->second.magnitude, (EXPONENT_TYPE)bu.exponent);
	  for (int i=0; i<NUM_BASEDIM; i++) {
	    dim.physical[i] += it->second.dimensions[i] * bu.exponent;
	  }
	} else {
	  missing = bu.unit;
	  break;
	}
      }
      if (missing=="") {
	dmtable << std::setfill(' ') << std::setw(10)  << std::left << unit.symbol;
	dmtable << std::setfill(' ') << std::setw(30)  << std::left << unit.name;
	dmtable << std::setfill(' ') << std::setw(30)  << std::left << unit.definition;
	dmtable << std::setfill(' ') << std::setw(20)  << std::left << dim.to_string(Dformat::NUM);
	dmtable << std::setfill(' ') << std::setw(20)  << std::left << dim.to_string(Dformat::PHYS);
	dmtable << "\n";
	dmap.insert({unit.symbol, {dim.numerical, dim.physical}});
      }
    }
  }

  inline void _solve_quantities(DimensionMapType& dmap, std::stringstream& dmtable, UnitSolver& solver) {
    for (auto quant: UnitSystem::Data->QuantityList) {
      UnitAtom atom = solver.solve(quant.second.definition);
      Dimensions dim(atom.value.magnitude);
      for (auto bu: atom.value.baseunits) {
	auto it = dmap.find(bu.unit);
	if (it != dmap.end()) {
	  dim.numerical *= nostd::pow(it->second.magnitude, (EXPONENT_TYPE)bu.exponent);
	  for (int i=0; i<NUM_BASEDIM; i++) {
	    dim.physical[i] += it->second.dimensions[i] * bu.exponent;
	  }
	} else {
	  throw DimensionMapExcept("Quantity '"+quant.first+"' could not be constructued from a definition '"+quant.second.definition+"'. Missing unit: "+bu.unit);
	}
      }
      std::string symbol = SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END;
      dmtable << std::setfill(' ') << std::setw(10)  << std::left << symbol;
      dmtable << std::setfill(' ') << std::setw(30)  << std::left << QuantityNames.at(quant.first);
      dmtable << std::setfill(' ') << std::setw(30)  << std::left << quant.second.definition;
      dmtable << std::setfill(' ') << std::setw(20)  << std::left << dim.to_string(Dformat::NUM);
      dmtable << std::setfill(' ') << std::setw(20)  << std::left << dim.to_string(Dformat::PHYS);
      dmtable << "\n";
      dmap.insert({symbol, {dim.numerical, dim.physical}});
    }
  }
  
  void DimensionMap::_create_map() {
    dmap = SystemData::_BASE_MAP;
    UnitSolver solver;
    size_t nit = 0;
    size_t nmax = UnitSystem::Data->UnitList.size();
    std::stringstream dmtable;
    while (dmap.size() < nmax && nit < nmax) {
      nit++;
      _solve_units(dmap, dmtable, solver);
    }
    nmax += UnitSystem::Data->QuantityList.size();
    _solve_quantities(dmap, dmtable, solver);

    if (dmap.size() < nmax)
      throw DimensionMapExcept("Dimension map is not complete: "+std::to_string(dmap.size())+"/"+std::to_string(nmax));
    
    // Write dimension map table
    std::ofstream dmfile;
    dmfile.open(file_table, std::ios::out|std::ios::trunc);
    dmfile << std::setfill(' ') << std::setw(10)  << std::left << "symbol";
    dmfile << std::setfill(' ') << std::setw(30)  << std::left << "name";
    dmfile << std::setfill(' ') << std::setw(30)  << std::left << "definition";
    dmfile << std::setfill(' ') << std::setw(20)  << std::left << "numerical dim.";
    dmfile << std::setfill(' ') << std::setw(20)  << std::left << "physical dim.";
    dmfile << std::endl;
    dmfile << dmtable.str();
    dmfile.close();
  }
  
  void DimensionMap::_write_map() {
    std::ofstream fout(file_data, std::ios::out|std::ios::binary);
    size_t size = dmap.size();
    fout.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (auto d: dmap) {
      fout.write(reinterpret_cast<const char*>(&d.first), sizeof(d.first));
#if defined(MAGNITUDE_ERRORS) &&  defined(MAGNITUDE_ARRAYS)
      MAGNITUDE_PRECISION mag = d.second.magnitude.value[0];
      MAGNITUDE_PRECISION err = d.second.magnitude.error[0];
#elif defined(MAGNITUDE_ERRORS)
      MAGNITUDE_PRECISION mag = d.second.magnitude.value;
      MAGNITUDE_PRECISION err = d.second.magnitude.error;
#elif defined(MAGNITUDE_ARRAYS)
      MAGNITUDE_PRECISION mag = d.second.magnitude[0];
      MAGNITUDE_PRECISION err = 0;
#else
      MAGNITUDE_PRECISION mag = d.second.magnitude;
      MAGNITUDE_PRECISION err = 0;
#endif
      fout.write(reinterpret_cast<const char*>(&mag), sizeof(mag));
      fout.write(reinterpret_cast<const char*>(&err), sizeof(err));
      EXPONENT_INT_PRECISION num[NUM_BASEDIM];
      EXPONENT_INT_PRECISION den[NUM_BASEDIM];
      for (int i=0; i<NUM_BASEDIM; i++) {
#if defined(EXPONENT_FRACTIONS)
	num[i] = d.second.dimensions[i].numerator;
	den[i] = d.second.dimensions[i].denominator;
#else
	num[i] = d.second.dimensions[i];
	den[i] = 1;
#endif
      }
      fout.write(reinterpret_cast<const char*>(&num), sizeof(num));
      fout.write(reinterpret_cast<const char*>(&den), sizeof(den));
    }
    fout.close();       
  }
  
  void DimensionMap::_read_map() {
    std::ifstream fin(file_data, std::ios::binary);
    if (!fin.is_open()) {
      std::cerr << "Error: Failed to open file for reading." << std::endl;
    }
    size_t size = 0;
    fin.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i=0; i<size; i++) {
      std::string symbol;
      fin.read(reinterpret_cast<char*>(&symbol), sizeof(symbol));
      MAGNITUDE_PRECISION mag;
      MAGNITUDE_PRECISION err;
      fin.read(reinterpret_cast<char*>(&mag), sizeof(mag));
      fin.read(reinterpret_cast<char*>(&err), sizeof(err));
      EXPONENT_INT_PRECISION num[NUM_BASEDIM];
      EXPONENT_INT_PRECISION den[NUM_BASEDIM];
      fin.read(reinterpret_cast<char*>(&num), sizeof(num));
      fin.read(reinterpret_cast<char*>(&den), sizeof(den));
      BaseDimensions bd;
      for (int i=0; i<NUM_BASEDIM; i++) {
#if defined(EXPONENT_FRACTIONS)
	bd[i] = {num[i], den[i]};
#else
	bd[i] = num[i];
#endif
      }
#if defined(MAGNITUDE_ERRORS)
      DimensionStruct ds = {{mag, err}, bd};
#else
      DimensionStruct ds = {mag, bd};
#endif
      dmap.insert({symbol, ds});
    }
    fin.close();
  }

  DimensionStruct DimensionMap::at(const std::string& s) const {
    return dmap.at(s);
  }
  
  DimensionMapType::const_iterator DimensionMap::find(const std::string& s) const {
    return dmap.find(s);
  }
  
  DimensionMapType::const_iterator DimensionMap::begin() const {
    return dmap.begin();
  }
  
  DimensionMapType::const_iterator DimensionMap::end() const {
    return dmap.end();
  }
  
}
