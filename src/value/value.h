#ifndef PUQ_VALUE_H
#define PUQ_VALUE_H

#include <vector>

#include "../settings.h"

#ifdef FRACTIONAL_EXPONENTS
class Exponent {
public:
  int numerator;
  int denominator;
  Exponent(): numerator(1), denominator(1) {}
  Exponent(int n): numerator(n), denominator(1) {};
  Exponent(int n, int d): numerator(n), denominator(d) {};
  void operator+=(Exponent const&e);
  void operator-=(Exponent const&e);
  void operator*=(Exponent const&e);
  std::string to_string();
  void rebase();
};
#endif

class BaseUnit {
public:
  std::string prefix;
  std::string unit;
  EXPONENT_TYPE exponent;
  BaseUnit() {};
  BaseUnit(int n): exponent(n) {};
#ifdef FRACTIONAL_EXPONENTS
  BaseUnit(int n, int d): exponent(n,d) {};
#endif
  BaseUnit(std::string p, std::string u, EXPONENT_TYPE e): prefix(p), unit(u), exponent(e) {};
#ifdef FRACTIONAL_EXPONENTS
  BaseUnit(std::string p, std::string u, int n, int d): prefix(p), unit(u), exponent(n,d) {};
#endif
  std::string to_string();
};

typedef std::vector<BaseUnit> BaseUnitsList;
class BaseUnits {
private:
  BaseUnitsList baseunits;
public:
  BaseUnits() {}
  BaseUnits(BaseUnitsList &bu): baseunits(bu) {}
  void append(BaseUnit bu);
  void append(std::string p, std::string u, EXPONENT_TYPE e);
#ifdef FRACTIONAL_EXPONENTS
  void append(std::string p, std::string u, int n, int d);
#endif
  std::string to_string();
  BaseUnit& operator[] (int index);
  void operator+=(BaseUnits &bu);
  void operator-=(BaseUnits &bu);
  void operator*=(EXPONENT_TYPE const&e);
  BaseUnitsList::iterator begin();
  BaseUnitsList::iterator end();
  std::size_t size();
};

class UnitValue {
public:
  MAGNITUDE_TYPE magnitude;
  BaseUnits baseunits;
  UnitValue() {}
  UnitValue(MAGNITUDE_TYPE m, BaseUnits bu): magnitude(m), baseunits(bu) {}
  UnitValue(MAGNITUDE_TYPE m, BaseUnitsList bul): magnitude(m), baseunits(bul) {}
  std::string to_string();
  void power(EXPONENT_TYPE &e);
  void operator*=(UnitValue &v);
  void operator/=(UnitValue &v);
};

#endif // PUQ_VALUE_H
