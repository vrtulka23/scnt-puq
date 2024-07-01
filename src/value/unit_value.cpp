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

UnitValue UnitValue::convert(const UnitValue& v) const {
  Dimensions dim1 = baseunits.dimensions();
  Dimensions dim2 = v.baseunits.dimensions();
  if (dim1==dim2) {
    return UnitValue(magnitude*dim1.numerical/(v.magnitude*dim2.numerical), v.baseunits);
  } else {
    throw std::invalid_argument("Incompatible physical dimensions: "+dim1.to_string('p')+" != "+dim2.to_string('p'));
  }
}

UnitValue UnitValue::convert(const BaseUnits& bu) const {
  Dimensions dim1 = baseunits.dimensions();
  Dimensions dim2 = bu.dimensions();
  if (dim1==dim2) {
    return UnitValue(magnitude*dim1.numerical/dim2.numerical, bu);
  } else {
    throw std::invalid_argument("Incompatible physical dimensions: "+dim1.to_string('p')+" != "+dim2.to_string('p'));
  }
}
