#include <string>
#include <sstream>

#include "../settings.h"
#include "value.h"

std::string BaseUnit::to_string() {
  std::stringstream ss;
#ifdef FRACTIONAL_EXPONENTS
  ss << prefix << unit << exponent.to_string();
#else
  ss << prefix << unit;
  if (exponent!=1) ss << std::to_string(exponent);
#endif
  return ss.str();
}

void BaseUnits::append(BaseUnit bu) {
  bool exists = false;
  for (auto it = baseunits.begin(); it != baseunits.end(); ++it) {
    if (it->prefix==bu.prefix && it->unit==bu.unit) {
      exists = true;
      it->exponent += bu.exponent;
#ifdef FRACTIONAL_EXPONENTS
      if (it->exponent.numerator==0) { // removing zero exponents
#else
      if (it->exponent==0) { // removing zero exponents
#endif
	baseunits.erase(it);
      }
      break;
    }
  }
#ifdef FRACTIONAL_EXPONENTS
  if (!exists && bu.exponent.numerator!=0)
    baseunits.push_back(bu);
#else
  if (!exists && bu.exponent!=0)
    baseunits.push_back(bu);
#endif
}

void BaseUnits::append(std::string p, std::string u, EXPONENT_TYPE e) {
  append(BaseUnit(p,u,e));
}

#ifdef FRACTIONAL_EXPONENTS
void BaseUnits::append(std::string p, std::string u, int n, int d) {
  append(BaseUnit(p,u,n,d));
}
#endif

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
#ifdef FRACTIONAL_EXPONENTS
    unit.exponent.numerator = -unit.exponent.numerator;
#else
    unit.exponent = -unit.exponent;
#endif
    append(unit);
  }
}

void BaseUnits::operator*=(EXPONENT_TYPE const&e) {
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
