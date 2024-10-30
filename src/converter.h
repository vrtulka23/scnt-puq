#ifndef PUQ_CONVERTER_H
#define PUQ_CONVERTER_H

#include <bitset>
#include <memory>
#include <sstream>

#include "nostd/nostd.h"
#include "value/value.h"
#include "data_table.h"

namespace puq {
  
  class ConvDimExcept: public std::exception {
  private:
    std::string message;
  public:
    ConvDimExcept(std::string m) : message(m) {}
    ConvDimExcept(const BaseUnits& bu1, const BaseUnits& bu2): ConvDimExcept(bu1, UnitSystem::System, bu2, UnitSystem::System) {}
    ConvDimExcept(const BaseUnits& bu1, const SystemType& s1, const BaseUnits& bu2, const SystemType& s2) {
      UnitSystem us(s1);
      Dimensions dim1 = bu1.dimensions();
      us.change(s2);
      Dimensions dim2 = bu2.dimensions();
      std::stringstream ss;
      ss << "Incompatible dimensions:" << std::endl << std::endl;
      DataTable tab({{"",8},{"System",10},{"Unit",26},{"Dimensions",26}});
      us.change(s1);
      tab.append({
	  "From", SystemMap[s1]->SystemAbbrev, bu1.to_string(),
	    ((dim1.to_string(Dformat::PHYS)=="") ? "1" : dim1.to_string(Dformat::PHYS))
	});
      us.change(s2);
      tab.append({
	  "To", SystemMap[s2]->SystemAbbrev, bu2.to_string(),
	    ((dim2.to_string(Dformat::PHYS)=="") ? "1" : dim2.to_string(Dformat::PHYS))
	});
      ss << tab.to_string() << std::endl;;
      us.change(s1);
      ss << "Possible conversions:" << std::endl << std::endl;
      tab = DataTable({{"System",10},{"Units",26},{"Name",26},{"Context",10}});
      std::string mgs = dim1.to_string(Dformat::PHYS);
      std::string mks = dim1.to_string(Dformat::PHYS|Dformat::MKS);
      std::string cgs = dim1.to_string(Dformat::PHYS|Dformat::CGS);
      if (mgs=="") {
	ss << "1";
      } else {
	tab.append({"BASE", mgs, "MGS base units"});
	if (mgs!=mks) {
	  tab.append({"BASE", mks, "MKS base units"});
	}
	if (mgs!=cgs && mks!=cgs) {
	  tab.append({"BASE", cgs, "CGS base units"});
	}
      }
      us.change(s1);
      for (auto unit: UnitSystem::Data->DimensionMap) {
	if (Dimensions(1,unit.second.dimensions) != dim1) continue;
	if (unit.first==mgs || unit.first==mks || unit.first==cgs) continue;
	if (unit.first[0]==SYMBOL_QUANTITY_START[0]) continue;
	tab.append({
	    SystemMap[s1]->SystemAbbrev, unit.first,
	      UnitSystem::Data->UnitList.find(unit.first)->second.name
	  });
      }
      us.change(s2);
      for (auto unit: UnitSystem::Data->DimensionMap) {
	if (Dimensions(1,unit.second.dimensions) != dim1) continue;
	if (unit.first==mgs || unit.first==mks || unit.first==cgs) continue;
	if (unit.first[0]==SYMBOL_QUANTITY_START[0]) continue;
	tab.append({
	    SystemMap[s2]->SystemAbbrev, unit.first,
	      UnitSystem::Data->UnitList.find(unit.first)->second.name
	  });
      }
      if (s1!=s2) {
	us.change(s1);
	for (auto quant: UnitSystem::Data->QuantityList) {
	  UnitValue uv(SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END);
	  Dimensions dim_q = uv.baseunits.dimensions();
	  if (dim_q==dim1) {
	    us.change(s2);
	    uv = UnitValue(SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END);
	    dim_q = uv.baseunits.dimensions();
	    for (auto unit: UnitSystem::Data->DimensionMap) {
	      if (Dimensions(1,unit.second.dimensions) != dim_q) continue;
	      if (unit.first==mgs || unit.first==mks || unit.first==cgs) continue;
	      if (unit.first[0]==SYMBOL_QUANTITY_START[0]) continue;
	      UnitStruct uinfo = UnitSystem::Data->UnitList[unit.first];
	      if ((uinfo.utype & Utype::LOG)==Utype::LOG) continue;
	      if ((uinfo.utype & Utype::TMP)==Utype::TMP) continue;
	      tab.append({
		  SystemMap[s2]->SystemAbbrev, unit.first,
		  UnitSystem::Data->UnitList.find(unit.first)->second.name,
		  quant.first
		});
	    }
	    us.change(s1);
	  }
	}	
      }
      ss << tab.to_string();
      message = ss.str();
    }
    const char * what () const noexcept override {
      return message.c_str();
    }
  };

  class NoConvExcept: public std::exception {
  private:
    std::string message;  
  public:
    NoConvExcept(const std::string& s1, const std::string& s2) : message("Conversion '"+s1+" -> "+s2+"' is not available!") {}
    const char * what () const noexcept override {
      return message.c_str();
    }
  };

  class Converter {
  private:
    BaseUnits baseunits1;
    BaseUnits baseunits2;
    MAGNITUDE_TYPE _convert_linear(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2);
#ifdef UNITS_LOGARITHMIC
    MAGNITUDE_TYPE _convert_logarithmic(MAGNITUDE_TYPE m);
#endif
#ifdef UNITS_TEMPERATURES
    MAGNITUDE_TYPE _convert_temperature(MAGNITUDE_TYPE m);
#endif
  public:
    Utype utype;
    Dimensions dimensions1;
    Dimensions dimensions2;
    Converter(): utype(Utype::NUL) {};
    Converter(const BaseUnits& bu1, const BaseUnits& bu2);
    Converter(const std::string& s1, const std::string& s2): Converter(BaseUnits(s1), BaseUnits(s2)) {};
    MAGNITUDE_TYPE convert(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2=1);
  };

}
  
#endif // PUQ_CONVERTER_H
