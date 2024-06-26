#include <sstream>
#include <iostream>

#include "unit_value.h"

std::string UnitValue::to_string() const {
  std::stringstream ss;
#if defined(MAGNITUDE_ERRORS) || defined(MAGNITUDE_ARRAYS)
  if (magnitude.value!=1 || baseunits.size()==0)
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
  if (v1.baseunits.dimensions()==v2.baseunits.dimensions()) 
    return UnitValue(v1.magnitude + v2.magnitude, v1.baseunits);
  else
    throw std::invalid_argument("Adding values with different dimensions: "+v1.baseunits.to_string()+" != "+v2.baseunits.to_string());
}
void UnitValue::operator+=(const UnitValue& v) {
  if (baseunits.dimensions()==v.baseunits.dimensions()) 
    magnitude += v.magnitude;
  else
    throw std::invalid_argument("Adding values with different dimensions: "+baseunits.to_string()+" != "+v.baseunits.to_string());
}

UnitValue operator-(const UnitValue& v1, const UnitValue& v2) {
  if (v1.baseunits.dimensions()==v2.baseunits.dimensions()) 
    return UnitValue(v1.magnitude - v2.magnitude, v1.baseunits);
  else
    throw std::invalid_argument("Subtracting values with different dimensions: "+v1.baseunits.to_string()+" != "+v2.baseunits.to_string());
} 
void UnitValue::operator-=(const UnitValue& v) {
  if (baseunits.dimensions()==v.baseunits.dimensions()) 
    magnitude -= v.magnitude;
  else
    throw std::invalid_argument("Subtracting values with different dimensions: "+baseunits.to_string()+" != "+v.baseunits.to_string());
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
