#include <sstream>

#include "value.h"

std::string UnitValue::to_string() {
  std::stringstream ss;
  if (magnitude!=1)
    ss << magnitude << std::scientific << SYMBOL_MULTIPLY;
  if (baseunits.size()>0)
    ss << baseunits.to_string() << SYMBOL_MULTIPLY;
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}
void UnitValue::power(EXPONENT_TYPE &e) {
#ifdef FRACTIONAL_EXPONENTS
  magnitude = std::pow(magnitude, e.numerator/e.denominator);
#else
  magnitude = std::pow(magnitude, e);
#endif
  baseunits *= e;
}
void UnitValue::operator*=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
  magnitude *= v.magnitude;
  baseunits += v.baseunits;
} 
void UnitValue::operator/=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
  magnitude /= v.magnitude;
  baseunits -= v.baseunits;
} 

