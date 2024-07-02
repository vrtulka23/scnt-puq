#include <sstream>
#include <iostream>

#include "unit_value.h"
#include "../solver/unit_solver.h"

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
  return UnitValue(v1.magnitude + v2.convert(v1.baseunits).magnitude, v1.baseunits);
}

void UnitValue::operator+=(const UnitValue& v) {
  magnitude += v.convert(baseunits).magnitude;
}

UnitValue operator-(const UnitValue& v1, const UnitValue& v2) {
  return UnitValue(v1.magnitude - v2.convert(v1.baseunits).magnitude, v1.baseunits);
}

void UnitValue::operator-=(const UnitValue& v) {
  magnitude -= v.convert(baseunits).magnitude;
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

inline MAGNITUDE_TYPE _convert_temperature(const MAGNITUDE_TYPE& m, const BaseUnits& bu1, const BaseUnits& bu2) {
  std::string s1 = bu1[0].unit;
  std::string s2 = bu2[0].unit;
  MAGNITUDE_TYPE const9div5 = 9./5.;
  MAGNITUDE_TYPE const5div9 = 5./9.;
  if (s1==s2) {
    return m;
  } else if (s1=="K" && s2=="Cel") {
    return m-(MAGNITUDE_TYPE)273.15;
  } else if (s1=="K" && s2=="degF") {
    return (m-(MAGNITUDE_TYPE)273.15)*const9div5+(MAGNITUDE_TYPE)32;
  } else if (s1=="degR" && s2=="degF") {
    return m*const9div5-(MAGNITUDE_TYPE)459.67;
  } else if (s1=="degR" && s2=="Cel") {
    return (m*const9div5-(MAGNITUDE_TYPE)491.67)*const5div9;
  } else if (s1=="Cel" && s2=="K") {
    return m+(MAGNITUDE_TYPE)273.15;
  } else if (s1=="Cel" && s2=="degF") {
    return (m*const9div5)+(MAGNITUDE_TYPE)32;
  } else if (s1=="Cel" && s2=="degR") {
    return ((m*const9div5)+(MAGNITUDE_TYPE)491.67);
  } else if (s1=="degF" && s2=="K") {
    return ((m-(MAGNITUDE_TYPE)32)*const5div9)+(MAGNITUDE_TYPE)273.15;
  } else if (s1=="degF" && s2=="Cel") {
    return (m-(MAGNITUDE_TYPE)32)*const5div9;
  } else if (s1=="degF" && s2=="degR") {
    return (m+(MAGNITUDE_TYPE)459.67)*const5div9;
  } else {
    throw ConversionException(bu1, bu2);
  }
}

inline MAGNITUDE_TYPE _convert_linear(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2, const Dimensions& d1, const Dimensions& d2) {
  return (m1*d1.numerical)/(m2*d2.numerical);
}

UnitValue UnitValue::convert(const UnitValue& v) const {
  Dimensions dim1 = baseunits.dimensions();
  Dimensions dim2 = v.baseunits.dimensions();
  if (dim1==dim2) {
    if ((dim1.utype & Utype::TMP)==Utype::TMP  || (dim2.utype & Utype::TMP)==Utype::TMP) {
      if (baseunits.size()==1 && v.baseunits.size()==1 && v.magnitude==(MAGNITUDE_TYPE)1) {
	return UnitValue(_convert_temperature(magnitude, baseunits, v.baseunits), v.baseunits);
      }
    }
    else if ((dim1.utype & Utype::LOG)==Utype::LOG) {
    }
    else {
      return UnitValue(_convert_linear(magnitude, v.magnitude, dim1, dim2), v.baseunits);
    }
  }
  throw ConversionException(dim1, dim2);
}

UnitValue UnitValue::convert(const BaseUnits& bu) const {
  Dimensions dim1 = baseunits.dimensions();
  Dimensions dim2 = bu.dimensions();
  if (dim1==dim2) {
    return UnitValue(_convert_linear(magnitude, 1, dim1, dim2), bu);
  }
  throw ConversionException(dim1, dim2);
}
