#include "solver.h"

std::string UnitValue::to_string() {
  std::stringstream ss;
  ss << magnitude << std::scientific;
  if (baseunits.size()>0)
    ss << SYMBOL_MULTIPLY << baseunits.to_string();
  return ss.str();
}
void UnitValue::power(Exponent &e) {
  magnitude = std::pow(magnitude, e.numerator/e.denominator);
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

