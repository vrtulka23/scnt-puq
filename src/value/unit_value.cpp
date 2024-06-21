#include <sstream>
#include <iostream>

#include "unit_value.h"

std::string UnitValue::to_string() {
  std::stringstream ss;
#ifdef MAGNITUDE_ERRORS
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

UnitValue UnitValue::operator*(UnitValue &v) {
  return UnitValue(magnitude * v.magnitude, baseunits + v.baseunits);
}
void UnitValue::operator*=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
  magnitude *= v.magnitude;
  baseunits += v.baseunits;
}

UnitValue UnitValue::operator/(UnitValue &v) {
  return UnitValue(magnitude / v.magnitude, baseunits - v.baseunits);
} 
void UnitValue::operator/=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
  magnitude /= v.magnitude;
  baseunits -= v.baseunits;
} 

void UnitValue::power(EXPONENT_TYPE &e) {
#ifdef MAGNITUDE_ERRORS 
  magnitude ^= e;
#else
#ifdef EXPONENT_FRACTIONS
  magnitude = std::pow(magnitude, e.to_real());
#else
  magnitude = std::pow(magnitude, e);
#endif
#endif
  baseunits *= e;
}
