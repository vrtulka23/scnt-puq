#include <sstream>
#include <iostream>
#include <iomanip>

#include "systems.h"
#include "../nostd/nostd.h"

namespace puq {

  std::string table_header(std::string title, std::vector<std::string> header, std::vector<int> width) {
    std::stringstream ss;
    ss << std::endl;
    ss << title << std::endl << std::endl;
    for (size_t i=0; i<header.size(); i++) {
      ss << std::setfill(' ') << std::setw(width[i])  << std::left << header[i];
    }
    ss << std::endl;
    for (size_t i=0; i<header.size(); i++) {
      ss << std::setfill('-') << std::setw(width[i])  << std::right << "  ";
    }
    ss << std::endl;
    return ss.str();
  }

  namespace lists {
  
    std::string unit_systems() {
      std::stringstream ss;
      ss << std::endl << "Unit systems:" << std::endl << std::endl;
      for (auto sys: SystemMap) {
	ss << std::setfill(' ') << std::setw(8)  << std::left << sys.second->SystemAbbrev;
	ss << std::setfill(' ') << std::setw(22)  << std::left << sys.second->SystemName;
	ss << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

    std::string prefixes() {
      std::stringstream ss;
      ss << table_header("Prefixes:", {"Symbol","Name","Magnitude"}, {8,8,11});
      for (auto symbol: UnitPrefixOrder) {
	auto prefix = UnitPrefixList.at(symbol);
	ss << std::setfill(' ') << std::setw(8)  << std::left << symbol;
	ss << std::setfill(' ') << std::setw(8)  << std::left << prefix.name;
	ss << std::setfill(' ') << std::setw(11) << std::left << nostd::to_string(prefix.magnitude);
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

    std::string base_units() {
      std::stringstream ss;
      ss << table_header("Base units:", {"Symbol","Name","Allowed prefixes"}, {8,19,22});
      for (auto symbol: SystemData::BaseUnitOrder) {
	auto unit = UnitSystem::Data->UnitList.at(symbol);
	if ((unit.utype & Utype::BAS)!=Utype::BAS) continue;
	ss << std::setfill(' ') << std::setw(8)  << std::left << symbol;
	ss << std::setfill(' ') << std::setw(19) << std::left << unit.name;
	ss << std::setfill(' ') << std::setw(22) << std::left << nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

    std::string derived_units() {
      std::stringstream ss;
      ss << table_header("Derived units:", {"Symbol","Name","Magnitude","Dimension","Definition","Allowed prefixes"}, {9,22,13,30,25,22});
      std::map<std::string, UnitStruct> ordered(UnitSystem::Data->UnitList.begin(), UnitSystem::Data->UnitList.end());
      for (auto unit: ordered) {
	if ((unit.second.utype & Utype::LIN)!=Utype::LIN) continue;
	if ((unit.second.utype & Utype::BAS)==Utype::BAS) continue;
	if ((unit.second.utype & Utype::CST)==Utype::CST) continue;
	if ((unit.second.utype & Utype::CSB)==Utype::CSB) continue;
	UnitValue uv(unit.first);
	Dimensions dim = uv.baseunits.dimensions();
	ss << std::setfill(' ') << std::setw(9)  << std::left << unit.first;
	ss << std::setfill(' ') << std::setw(22) << std::left << unit.second.name;
	ss << std::setfill(' ') << std::setw(13) << std::left << dim.to_string(Dformat::NUM);
	ss << std::setfill(' ') << std::setw(30) << std::left << dim.to_string(Dformat::PHYS);
	ss << std::setfill(' ') << std::setw(25) << std::left << unit.second.definition;
	ss << std::setfill(' ') << std::setw(22) << std::left << nostd::to_string(unit.second.use_prefixes, unit.second.allowed_prefixes);
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

    std::string constants() {
      std::stringstream ss;
      ss << table_header("Constants:", {"Symbol","Name","Magnitude","Dimension","Definition"}, {9,19,30,20,30});
      std::map<std::string, UnitStruct> ordered(UnitSystem::Data->UnitList.begin(), UnitSystem::Data->UnitList.end());
      for (auto unit: ordered) {
	if ((unit.second.utype & Utype::CST)!=Utype::CST) continue;
	UnitValue uv(unit.first);
	Dimensions dim = uv.baseunits.dimensions();
	ss << std::setfill(' ') << std::setw(9)  << std::left << unit.first;
	ss << std::setfill(' ') << std::setw(19) << std::left << unit.second.name;
	ss << std::setfill(' ') << std::setw(30) << std::left << dim.to_string(Dformat::NUM);
	ss << std::setfill(' ') << std::setw(20) << std::left << dim.to_string(Dformat::PHYS);
	ss << std::setfill(' ') << std::setw(30) << std::left << unit.second.definition;
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

    std::string quantities() {
      std::stringstream ss;
      ss << table_header("Constants:", {"Symbol","Name","Magnitude","Dimension","Definition","SI factor"}, {10,30,30,22,25,11});
      std::map<std::string, QuantityStruct> ordered(UnitSystem::Data->QuantityList.begin(), UnitSystem::Data->QuantityList.end());
      for (auto quantity: ordered) {
	std::string symbol = SYMBOL_QUANTITY_START+quantity.first+SYMBOL_QUANTITY_END;
	UnitValue uv(symbol);
	Dimensions dim = uv.baseunits.dimensions();
	ss << std::setfill(' ') << std::setw(10)  << std::left << symbol;
	ss << std::setfill(' ') << std::setw(30) << std::left << QuantityNames.at(quantity.first);
	ss << std::setfill(' ') << std::setw(30) << std::left << dim.to_string(Dformat::NUM);
	ss << std::setfill(' ') << std::setw(22) << std::left << dim.to_string(Dformat::PHYS);
	ss << std::setfill(' ') << std::setw(25) << std::left << quantity.second.definition;
	ss << std::setfill(' ') << std::setw(11) << std::left << ((quantity.second.sifactor=="") ? "no" : "yes");
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }

#ifdef UNITS_TEMPERATURES
    std::string temperature_units() {
      std::stringstream ss;
      ss << table_header("Temperatures:", {"Symbol","Name","Allowed prefixes"}, {9,19,22});
      std::map<std::string, UnitStruct> ordered(UnitSystem::Data->UnitList.begin(), UnitSystem::Data->UnitList.end());
      for (auto unit: ordered) {
	if ((unit.second.utype & Utype::TMP)!=Utype::TMP) continue;
	ss << std::setfill(' ') << std::setw(9)  << std::left << unit.first;
	ss << std::setfill(' ') << std::setw(19) << std::left << unit.second.name;
	ss << std::setfill(' ') << std::setw(22) << std::left << nostd::to_string(unit.second.use_prefixes, unit.second.allowed_prefixes);
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }
#endif

#ifdef UNITS_LOGARITHMIC
    std::string logarithmic_units() {
      std::stringstream ss;
      ss << table_header("Logarithmic units:", {"Symbol","Name","Allowed prefixes"}, {9,19,22});
      std::map<std::string, UnitStruct> ordered(UnitSystem::Data->UnitList.begin(), UnitSystem::Data->UnitList.end());
      for (auto unit: ordered) {
	if ((unit.second.utype & Utype::LOG)!=Utype::LOG) continue;
	ss << std::setfill(' ') << std::setw(9)  << std::left << unit.first;
	ss << std::setfill(' ') << std::setw(19) << std::left << unit.second.name;
	ss << std::setfill(' ') << std::setw(22) << std::left << nostd::to_string(unit.second.use_prefixes, unit.second.allowed_prefixes);
	ss << std::scientific << std::endl;
      }
      ss << std::endl;
      return ss.str();
    }
#endif

  }
    
}
