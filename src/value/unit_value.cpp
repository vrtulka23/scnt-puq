#include <sstream>
#include <iostream>
#include <memory>

#include "value.h"
#include "../solver/solver.h"
#include "../converter.h"

namespace puq {
  
  UnitValue::UnitValue(const std::string& s) {
    UnitSolver solver;  
    UnitAtom atom = solver.solve(s);
    magnitude = atom.value.magnitude;
    baseunits = atom.value.baseunits;
  }

  UnitValue::UnitValue(const MAGNITUDE_TYPE& m, const std::string& s) {
    UnitSolver solver;  
    UnitAtom atom = solver.solve(s);
    magnitude = m * atom.value.magnitude;
    baseunits = atom.value.baseunits;
  }

  UnitValue::UnitValue(const MAGNITUDE_TYPE& m, const Dimensions& dim) {
    magnitude = m * dim.numerical;
    for (int i=0; i<NUM_BASEDIM; i++) {
      std::string symbol = SystemData::BaseUnitOrder[i];
      baseunits.append("", symbol, dim.physical[i]);
    }
  }

  std::string UnitValue::to_string() const {
    std::stringstream ss;
  #if defined(MAGNITUDE_ERRORS)
    if (magnitude.value!=1 || baseunits.size()==0)
      ss << magnitude.to_string() << SYMBOL_MULTIPLY;
  #elif defined(MAGNITUDE_ARRAYS)
    if (magnitude!=1 || baseunits.size()==0)
      ss << magnitude.to_string() << SYMBOL_MULTIPLY;
  #else
    if (magnitude!=1 || baseunits.size()==0)
      ss << magnitude << std::scientific << SYMBOL_MULTIPLY;
  #endif
    if (baseunits.size()>0)
      ss << baseunits.to_string() << SYMBOL_MULTIPLY;
    std::string s = ss.str();
    return s.substr(0,s.size()-1);
  }

  UnitValue operator+(const UnitValue& v1, const UnitValue& v2) {
    Converter conv(v2.baseunits, v1.baseunits);
  #ifdef UNITS_LOGARITHMIC
    if (conv.utype==Utype::LOG) {
      MAGNITUDE_TYPE m1 = v1.magnitude * conv.dimensions1.numerical;
      MAGNITUDE_TYPE m2 = conv.convert(v2.magnitude) * conv.dimensions2.numerical;
      if ((conv.dimensions1.utype & Utype::LOG) == Utype::LOG)
	m1 = nostd::pow(10, m1);
      if ((conv.dimensions2.utype & Utype::LOG) == Utype::LOG)
	m2 = nostd::pow(10, m2);
      return UnitValue(nostd::log10(m1 + m2) / conv.dimensions1.numerical, v1.baseunits);
    }
  #endif
    return UnitValue(v1.magnitude + conv.convert(v2.magnitude), v1.baseunits);
  }

  void UnitValue::operator+=(const UnitValue& v) {
    Converter conv(v.baseunits, baseunits);
  #ifdef UNITS_LOGARITHMIC
    if (conv.utype==Utype::LOG) {
      MAGNITUDE_TYPE m1 = magnitude * conv.dimensions1.numerical;
      MAGNITUDE_TYPE m2 = conv.convert(v.magnitude) * conv.dimensions2.numerical;
      if ((conv.dimensions1.utype & Utype::LOG) == Utype::LOG)
	m1 = nostd::pow(10, m1);
      if ((conv.dimensions2.utype & Utype::LOG) == Utype::LOG)
	m2 = nostd::pow(10, m2);
      magnitude = nostd::log10(m1 + m2) / conv.dimensions1.numerical;
      return;
    }
  #endif
    magnitude += conv.convert(v.magnitude);
  }

  UnitValue operator-(const UnitValue& v1, const UnitValue& v2) {
    Converter conv(v2.baseunits, v1.baseunits);
  #ifdef UNITS_LOGARITHMIC
    if (conv.utype==Utype::LOG) {
      MAGNITUDE_TYPE m1 = v1.magnitude * conv.dimensions1.numerical;
      MAGNITUDE_TYPE m2 = conv.convert(v2.magnitude) * conv.dimensions2.numerical;
      if ((conv.dimensions1.utype & Utype::LOG) == Utype::LOG)
	m1 = nostd::pow(10, m1);
      if ((conv.dimensions2.utype & Utype::LOG) == Utype::LOG)
	m2 = nostd::pow(10, m2);
      return UnitValue(nostd::log10(m1 - m2) / conv.dimensions1.numerical, v1.baseunits);
    }
  #endif
    return UnitValue(v1.magnitude - conv.convert(v2.magnitude), v1.baseunits);
  }

  void UnitValue::operator-=(const UnitValue& v) {
    Converter conv(v.baseunits, baseunits);
  #ifdef UNITS_LOGARITHMIC
    if (conv.utype==Utype::LOG) {
      MAGNITUDE_TYPE m1 = magnitude * conv.dimensions1.numerical;
      MAGNITUDE_TYPE m2 = conv.convert(v.magnitude) * conv.dimensions2.numerical;
      if ((conv.dimensions1.utype & Utype::LOG) == Utype::LOG)
	m1 = nostd::pow(10, m1);
      if ((conv.dimensions2.utype & Utype::LOG) == Utype::LOG)
	m2 = nostd::pow(10, m2);
      magnitude = nostd::log10(m1 - m2) / conv.dimensions1.numerical;
      return;
    }
  #endif
    magnitude -= conv.convert(v.magnitude);
  }

  UnitValue operator*(const UnitValue& v1, const UnitValue& v2) {
    return UnitValue(v1.magnitude * v2.magnitude, v1.baseunits + v2.baseunits);
  }

  void UnitValue::operator*=(const UnitValue& v) {
    magnitude *= v.magnitude;
    baseunits += v.baseunits;
  }

  UnitValue operator/(const UnitValue& v1, const UnitValue& v2) {
    return UnitValue(v1.magnitude / v2.magnitude, v1.baseunits - v2.baseunits);
  }

  void UnitValue::operator/=(const UnitValue& v) {
    magnitude /= v.magnitude;
    baseunits -= v.baseunits;
  } 

  void UnitValue::pow(const EXPONENT_TYPE& e) {
  #if defined(MAGNITUDE_ERRORS) || defined(MAGNITUDE_ARRAYS)
    magnitude.pow(e);
  #else
    magnitude = std::pow(magnitude, (EXPONENT_REAL_PRECISION)e);
  #endif
    baseunits *= e;
  }

  UnitValue UnitValue::convert(const std::string& s) const {
    UnitValue uv = UnitValue(s);
    return convert(uv);
  }

  UnitValue UnitValue::convert(const UnitValue& v) const {
    Converter conv(baseunits, v.baseunits);
    return UnitValue(conv.convert(magnitude, v.magnitude), v.baseunits);
  }

  UnitValue UnitValue::convert(const BaseUnits& bu) const {
    Converter conv(baseunits, bu);
    return UnitValue(conv.convert(magnitude, 1), bu);
  }

}
