#ifndef PUQ_VALUE_H
#define PUQ_VALUE_H

#include <vector>

#include "../settings.h"
#include "../lists/lists.h"

#include "exponent.h"
#include "array.h"
#include "magnitude.h"

typedef std::array<EXPONENT_TYPE, NUM_BASEDIM> PhysicalDimensions;

class Dimensions {
public:
  MAGNITUDE_TYPE numerical; 
  PhysicalDimensions physical;
  Dimensions();
  Dimensions(MAGNITUDE_TYPE const&n);
  Dimensions(MAGNITUDE_TYPE const&n, PhysicalDimensions const&p): numerical(n), physical(p) {};
#ifdef MAGNITUDE_ERRORS
  Dimensions(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e);
  Dimensions(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, PhysicalDimensions const&p): numerical(m,e), physical(p) {};
#endif
  std::string to_string();
  bool operator==(Dimensions const&d) const;
  bool operator!=(Dimensions const&d) const;
};

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
  BaseUnits operator+(BaseUnits &bu);
  BaseUnits operator-(BaseUnits &bu);
  void operator+=(BaseUnits &bu);
  void operator-=(BaseUnits &bu);
  void operator*=(EXPONENT_TYPE const&e);
  BaseUnitsList::iterator begin();
  BaseUnitsList::const_iterator cbegin();
  BaseUnitsList::iterator end();
  BaseUnitsList::const_iterator cend();
  std::size_t size();
  void rebase();
  Dimensions dimensions();
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
  UnitValue(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e): magnitude(m,e) {}
  UnitValue(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, BaseUnits const&bu): magnitude(m,e), baseunits(bu) {}
  UnitValue(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, BaseUnitsList const&bul): magnitude(m,e), baseunits(bul) {}
#endif
  std::string to_string();
  void power(EXPONENT_TYPE &e);
  UnitValue operator+(UnitValue &v);
  UnitValue operator-(UnitValue &v);
  UnitValue operator*(UnitValue &v);
  UnitValue operator/(UnitValue &v);
  void operator+=(UnitValue &v);
  void operator-=(UnitValue &v);
  void operator*=(UnitValue &v);
  void operator/=(UnitValue &v);
};

#endif // PUQ_VALUE_H
