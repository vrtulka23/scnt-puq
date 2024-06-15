#include "../settings.h"
#include "../../external/exs-cpp/src/exs.h"

#include <set>
#include <format>
#include <cmath>

struct UnitPrefixStruct {
  std::string symbol;
  double magnitude;
  int dimensions[NUM_BASEDIM];
  std::string definition;
  std::string name;
};
extern std::vector<UnitPrefixStruct> UnitPrefixList;

struct UnitStruct {
  std::string symbol;
  double magnitude;
  int dimensions[NUM_BASEDIM];
  std::string definition;
  std::string name;
  bool use_prefixes;
  std::set<std::string> allowed_prefixes;
};
extern std::vector<UnitStruct> UnitList;

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

class BaseUnit {
public:
  std::string prefix;
  std::string unit;
  Exponent exponent;
  BaseUnit() {};
  BaseUnit(int n, int d): exponent(n,d) {};
  BaseUnit(std::string p, std::string u, Exponent e): prefix(p), unit(u), exponent(e) {};
  BaseUnit(std::string p, std::string u, int n, int d): prefix(p), unit(u), exponent(n,d) {};
  std::string to_string() {
    std::stringstream ss;
    ss << prefix << unit << exponent.to_string();
    return ss.str();
  }
};

typedef std::vector<BaseUnit> BaseUnitsList;
class BaseUnits {
private:
  BaseUnitsList baseunits;
public:
  BaseUnits() {}
  BaseUnits(BaseUnitsList &bu): baseunits(bu) {}
  void append(BaseUnit bu);
  void append(std::string p, std::string u, Exponent e);
  void append(std::string p, std::string u, int n, int d);
  std::string to_string();
  BaseUnit& operator[] (int index) { return baseunits[index]; }
  void operator+=(BaseUnits &bu);
  void operator-=(BaseUnits &bu);
  void power(Exponent &e);
  BaseUnitsList::iterator begin() { return baseunits.begin(); }
  BaseUnitsList::iterator end()   { return baseunits.end(); }
  std::size_t size() { return baseunits.size(); }
};

class UnitValue {
public:
  NUMBER_DTYPE magnitude;
  BaseUnits baseunits;
  UnitValue() {}
  UnitValue(NUMBER_DTYPE m, BaseUnits bu): magnitude(m), baseunits(bu) {}
  UnitValue(NUMBER_DTYPE m, BaseUnitsList bul): magnitude(m), baseunits(bul) {}
  std::string to_string() {
    std::stringstream ss;
    ss << magnitude << std::scientific;
    if (baseunits.size()>0)
       ss << SYMBOL_MULTIPLY << baseunits.to_string();
    return ss.str();
  }
  void power(Exponent &e) {
    magnitude = std::pow(magnitude, e.numerator/e.denominator);
    baseunits.power(e);
  }
  void operator*=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
    magnitude *= v.magnitude;
    baseunits += v.baseunits;
  } 
  void operator/=(UnitValue &v) { // "UnitValue const& v" lead to an error, TODO implement const_iterator
    magnitude /= v.magnitude;
    baseunits -= v.baseunits;
  } 
};

class UnitAtom: public exs::AtomBase<UnitValue> {
 public:
  UnitAtom(UnitAtom &a): AtomBase(a) {};
  UnitAtom(UnitValue v): AtomBase(v) {}; 
  static UnitValue from_string(std::string s);
  std::string to_string();
  void math_power(Exponent &e);
  void math_multiply(UnitAtom *other);
  void math_divide(UnitAtom *other);
};

class UnitSolver {
public:
  std::unique_ptr<exs::Solver<UnitAtom>> solver;
  UnitSolver();
  UnitAtom solve(std::string expression);
};
