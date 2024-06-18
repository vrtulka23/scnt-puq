#include <sstream>

#include "unit_value.h"

std::string UnitValue::to_string() {
  std::stringstream ss;
#ifdef MAGNITUDE_ERRORS
  if (magnitude.magnitude!=1)
    ss << magnitude.to_string() << SYMBOL_MULTIPLY;
#else
  if (magnitude!=1)
    ss << magnitude << std::scientific << SYMBOL_MULTIPLY;
#endif
  if (baseunits.size()>0)
    ss << baseunits.to_string() << SYMBOL_MULTIPLY;
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

void UnitValue::power(EXPONENT_TYPE &e) {
#ifdef EXPONENT_FRACTIONS
#ifdef MAGNITUDE_ERRORS  // TODO: implement power of errors
  magnitude.magnitude = std::pow(magnitude.magnitude, e.numerator/e.denominator);
#else
  magnitude = std::pow(magnitude, e.numerator/e.denominator);
#endif
#else
#ifdef MAGNITUDE_ERRORS  // TODO: implement power of errors
  magnitude.magnitude = std::pow(magnitude.magnitude, e);
#else
  magnitude = std::pow(magnitude, e);
#endif
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

