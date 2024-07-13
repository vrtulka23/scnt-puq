#include <string>
#include <sstream>
#include <iostream>

#include "../settings.h"
#include "../nostd.h"
#include "value.h"
#include "../solver/solver.h"

namespace puq {

BaseUnits::BaseUnits(const std::string& s) {
  UnitSolver solver;  
  UnitAtom atom = solver.solve(s);
  baseunits = atom.value.baseunits.baseunits;
}

std::string BaseUnit::to_string() {
  std::stringstream ss;
  ss << prefix << unit;
#ifdef EXPONENT_FRACTIONS
  ss << exponent.to_string();
#else
  if (exponent!=1) ss << std::to_string(exponent);
#endif
  return ss.str();
}

void BaseUnits::append(BaseUnit bu) {
  bool exists = false;
  for (auto it = baseunits.begin(); it != baseunits.end(); ++it) {
    if (it->prefix==bu.prefix && it->unit==bu.unit) {
      exists = true;
      it->exponent += bu.exponent;
      // removing zero exponents
      if (it->exponent==0) {
	baseunits.erase(it);
      }
      break;
    }
  }
  if (!exists && bu.exponent!=0) {
    baseunits.push_back(bu);
  }
}

void BaseUnits::append(std::string p, std::string u, EXPONENT_TYPE e) {
  append(BaseUnit(p,u,e));
}

#ifdef EXPONENT_FRACTIONS
void BaseUnits::append(std::string p, std::string u, EXPONENT_INT_PRECISION n, EXPONENT_INT_PRECISION d) {
  append(BaseUnit(p,u,n,d));
}
#endif

std::string BaseUnits::to_string() const {
  std::stringstream ss;
  for (auto unit: baseunits) {
    ss << unit.to_string() << SYMBOL_MULTIPLY;
  }
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

const BaseUnit& BaseUnits::operator[] (int index) const {
  return baseunits[index];
}

BaseUnits operator+(const BaseUnits& bu1, const BaseUnits& bu2) {
  BaseUnits nbu(bu1.baseunits);  
  for (auto const&unit: bu2) {
    nbu.append(unit);
  }
  return nbu;
}
void BaseUnits::operator+=(const BaseUnits& bu) {
  for (auto unit: bu) {
    append(unit);
  }
}

BaseUnits operator-(const BaseUnits& bu1, const BaseUnits& bu2) {
  BaseUnits nbu(bu1.baseunits);  
  for (auto unit: bu2) {
    unit.exponent = -unit.exponent;
    nbu.append(unit);
  }
  return nbu;
}
void BaseUnits::operator-=(const BaseUnits& bu) {
  for (auto unit: bu) {
    unit.exponent = -unit.exponent;
    append(unit);
  }
}
 
void BaseUnits::operator*=(const EXPONENT_TYPE& e) {
  for (auto &unit: baseunits) {
     unit.exponent *= e;
  }
}

BaseUnitsList::const_iterator BaseUnits::begin() const {
  return baseunits.begin();
}

BaseUnitsList::const_iterator BaseUnits::end() const {
  return baseunits.end();
}
 
std::size_t BaseUnits::size() const {
  return baseunits.size();
}
 
void BaseUnits::rebase() {
}

Dimensions BaseUnits::dimensions() const {
  Dimensions dim;
  for (auto &bu: baseunits) {
    for (auto &prefix: UnitPrefixList) {
      if (prefix.symbol==bu.prefix) {
	dim.numerical *= nostd::pow(prefix.magnitude, (EXPONENT_TYPE)bu.exponent);
	break;
      }
    }
    for (auto &unit: *UnitList) {
      if (unit.symbol==bu.unit) {
	if ((unit.utype & Utype::LIN)==Utype::LIN)  // standard linear conversion
	  dim.utype = dim.utype | Utype::LIN;
	if (unit.utype==Utype::TMP)                 // unit requires conversion of temperatures
	  dim.utype = dim.utype | unit.utype;
	if (unit.utype==Utype::LOG)                 // unit requires logarithmic conversions
	  dim.utype = dim.utype | unit.utype;
	dim.symbols.push_back(unit.symbol);
	dim.numerical *= nostd::pow(unit.magnitude, (EXPONENT_TYPE)bu.exponent);
	for (int i=0; i<NUM_BASEDIM; i++) {
	  dim.physical[i] += unit.dimensions[i] * bu.exponent;
	}
	break;
      }
    }
  }
  return dim;
}

}
