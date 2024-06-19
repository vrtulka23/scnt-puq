#ifndef PUQ_VALUE_H
#define PUQ_VALUE_H

#include <vector>

#include "../settings.h"

#ifdef EXPONENT_FRACTIONS
class Exponent {
public:
  EXPONENT_INT_PRECISION numerator;
  EXPONENT_INT_PRECISION denominator;
  Exponent(): numerator(1), denominator(1) {}
  Exponent(EXPONENT_INT_PRECISION const&n): numerator(n), denominator(1) {};
  Exponent(EXPONENT_INT_PRECISION const&n, EXPONENT_INT_PRECISION const&d): numerator(n), denominator(d) {};
  void operator+=(Exponent const&e);
  void operator-=(Exponent const&e);
  void operator*=(Exponent const&e);
  EXPONENT_REAL_PRECISION to_real();
  std::string to_string();
  void rebase();
};
#endif

#ifdef MAGNITUDE_ERRORS
class Magnitude {
public:
  MAGNITUDE_PRECISION value;
  MAGNITUDE_PRECISION error;
  Magnitude(): value(1), error(0) {}
  Magnitude(MAGNITUDE_PRECISION const&m): value(m), error(0) {}
  Magnitude(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e): value(m), error(e) {}
  static MAGNITUDE_PRECISION abs_to_rel(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&a);
  static MAGNITUDE_PRECISION rel_to_abs(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&r);
  std::string to_string();
  void operator*=(Magnitude const&m);
  void operator/=(Magnitude const&m);
  void operator^=(EXPONENT_TYPE &e);
};
#endif

class BaseUnit {
public:
  std::string prefix;
  std::string unit;
  EXPONENT_TYPE exponent;
  BaseUnit() {};
  BaseUnit(EXPONENT_INT_PRECISION const&n): exponent(n) {};
#ifdef EXPONENT_FRACTIONS
  BaseUnit(EXPONENT_INT_PRECISION const&n, EXPONENT_INT_PRECISION const&d): exponent(n,d) {};
#endif
  BaseUnit(std::string const&p, std::string const&u, EXPONENT_TYPE const&e): prefix(p), unit(u), exponent(e) {};
#ifdef EXPONENT_FRACTIONS
  BaseUnit(std::string const&p, std::string const&u, EXPONENT_INT_PRECISION const&n, EXPONENT_INT_PRECISION const&d): prefix(p), unit(u), exponent(n,d) {};
#endif
  std::string to_string();
};

typedef std::vector<BaseUnit> BaseUnitsList;
class BaseUnits {
private:
  BaseUnitsList baseunits;
public:
  BaseUnits() {}
  BaseUnits(BaseUnitsList const&bu): baseunits(bu) {}
  void append(BaseUnit bu);
  void append(std::string p, std::string u, EXPONENT_TYPE e);
#ifdef EXPONENT_FRACTIONS
  void append(std::string p, std::string u, EXPONENT_INT_PRECISION n, EXPONENT_INT_PRECISION d);
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
  UnitValue(): magnitude(1) {}
  UnitValue(MAGNITUDE_TYPE const&m): magnitude(m) {}
  UnitValue(MAGNITUDE_TYPE const&m, BaseUnits const&bu): magnitude(m), baseunits(bu) {}
  UnitValue(MAGNITUDE_TYPE const&m, BaseUnitsList const&bul): magnitude(m), baseunits(bul) {}
#ifdef MAGNITUDE_ERRORS
  UnitValue(MAGNITUDE_PRECISION const&m, BaseUnits const&bu): magnitude(m), baseunits(bu) {}
  UnitValue(MAGNITUDE_PRECISION const&m, BaseUnitsList const&bul): magnitude(m), baseunits(bul) {}
  UnitValue(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, BaseUnits const&bu): magnitude(m,e), baseunits(bu) {}
  UnitValue(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, BaseUnitsList const&bul): magnitude(m,e), baseunits(bul) {}
#endif
  std::string to_string();
  void power(EXPONENT_TYPE &e);
  void operator*=(UnitValue &v);
  void operator/=(UnitValue &v);
};

#endif // PUQ_VALUE_H
