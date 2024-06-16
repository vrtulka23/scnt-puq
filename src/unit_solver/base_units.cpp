#include "solver.h"

void BaseUnits::append(BaseUnit bu) {
  bool exists = false;
  for (auto it = baseunits.begin(); it != baseunits.end(); ++it) {
    if (it->prefix==bu.prefix && it->unit==bu.unit) {
      exists = true;
      it->exponent += bu.exponent;
      if (it->exponent.numerator==0) { // removing zero exponents
	baseunits.erase(it);
      }
      break;
    }
  }
  if (!exists && bu.exponent.numerator!=0)
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

BaseUnit& BaseUnits::operator[] (int index) {
  return baseunits[index];
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

void BaseUnits::operator*=(Exponent const&e) {
  for (auto &unit: baseunits) {
    unit.exponent *= e;
  }
}

BaseUnitsList::iterator BaseUnits::begin() {
  return baseunits.begin();
}

BaseUnitsList::iterator BaseUnits::end()   {
  return baseunits.end();
}

std::size_t BaseUnits::size() {
  return baseunits.size();
}
