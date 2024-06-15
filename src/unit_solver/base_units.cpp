#include "solver.h"

void BaseUnits::append(BaseUnit bu) {
  bool exists = false;
  for (auto &unit: baseunits) {
    if (unit.prefix==bu.prefix && unit.unit==bu.unit) {
      exists = true;
      unit.exponent += bu.exponent;
      // TODO: here we should remove an item if its numerator ends up to be zero
      break;
    }
  }
  if (!exists)
    baseunits.push_back(bu);
}

void BaseUnits::append(std::string p, std::string u, Exponent e) {
  append(BaseUnit(p,u,e));
}

void BaseUnits::append(std::string p, std::string u, int n, int d) {
  append(BaseUnit(p,u,n,d));
}

std::string BaseUnits::to_string() {
  std::stringstream ss;
  for (auto unit: baseunits) {
    ss << unit.to_string() << SYMBOL_MULTIPLY;
  }
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

void BaseUnits::operator+=(BaseUnits &bu) {
  for (auto const &unit: bu) {
    append(unit);
  }
}

void BaseUnits::operator-=(BaseUnits &bu) {
  for (auto unit: bu) {
    unit.exponent.numerator = -unit.exponent.numerator;
    append(unit);
  }
}

void BaseUnits::power(Exponent &e) {
  for (auto &unit: baseunits) {
    unit.exponent *= e;
  }
}
