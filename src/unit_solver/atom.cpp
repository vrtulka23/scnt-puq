#include <regex>

#include "solver.h"

UnitValue UnitAtom::from_string(std::string expr_orig) {
  std::string expr = expr_orig;
  // parse a number
  struct UnitValue q;
  std::smatch m;
  std::regex rx_number("^((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?$");
  std::regex rx_unit("^([a-zA-Z_%']+)([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)$");
  if (std::regex_match(expr, rx_number)) {
    q.magnitude = std::stof(expr);
  } else if (std::regex_match(expr, m, rx_unit)) {
    BaseUnit bu;
    bu.exponent.numerator   = m[2]=="" ? 1 : std::stoi(m[2]);
    bu.exponent.denominator = m[4]=="" ? 1 : std::stoi(m[4]);
    expr = m[1];
    for (auto unit: UnitList) {
      if (unit.symbol.size()>expr.size() || unit.symbol.size()==bu.unit.size())
	continue;
      if (expr.compare(expr.size()-unit.symbol.size(), unit.symbol.size(), unit.symbol)==0) {
	bu.unit = unit.symbol;
      }
    }
    if (bu.unit.size()==0) {
      throw std::invalid_argument("Unknown unit base: "+expr_orig);
    }
    expr = expr.substr(0,expr.size()-bu.unit.size());
    if (expr.size()>0) {
      for (auto prefix: UnitPrefixList) {
	if (prefix.symbol==expr) {
	  bu.prefix = prefix.symbol;
	}
      }
      if (bu.prefix.size()==0) {
	throw std::invalid_argument("Unknown unit prefix: "+expr_orig);
      }
    }
    q.magnitude = 1;
    q.baseunits.append(bu);
  }
  return UnitValue(q);
}

std::string UnitAtom::to_string() {
  return value.to_string();
}

void UnitAtom::math_multiply(UnitAtom *other) {
  value *= other->value;
}

void UnitAtom::math_divide(UnitAtom *other) {
  value /= other->value;
}
