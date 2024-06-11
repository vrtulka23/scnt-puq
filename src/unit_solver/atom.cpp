#include <regex>

#include "solver.h"

UnitValue UnitAtom::from_string(std::string s) {
  struct UnitValue q;
  // parse a number
  std::smatch m;
  std::regex rx_number("^((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?$");
  std::regex rx_unit("^([a-zA-Z_%']+)([+-]?[0-9]+)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)$");
  if (std::regex_match(s, rx_number)) {
    q.magnitude = std::stof(s);
  } else if (std::regex_match(s, m, rx_unit)) {
    BaseUnit bu;
    bu.numerator = std::stoi(m[2]);
    bu.denominator = m[4]=="" ? 1 : std::stoi(m[4]);
    std::cout << s << " match " << m[1] << " " << bu.numerator << " " << bu.denominator << std::endl;
    q.magnitude = 1;
    q.baseunits.push_back(bu);
  }
  return UnitValue(q);
}

std::string UnitAtom::to_string() {
  return std::to_string(value.magnitude);
}

void UnitAtom::math_multiply(UnitAtom *other) {
  value.magnitude *= other->value.magnitude;
}

void UnitAtom::math_divide(UnitAtom *other) {
  value.magnitude /= other->value.magnitude;
}
