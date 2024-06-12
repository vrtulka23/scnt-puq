#include "../settings.h"
#include "../../external/exs-cpp/src/exs.h"

#include <set>
#include <format>

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

class BaseUnit {
public:
  std::string prefix;
  std::string unit;
  int numerator;
  int denominator;
  std::string to_string() {
    std::stringstream ss;
    ss << prefix << unit;
    if (denominator!=1)
      ss << std::to_string(numerator) << std::string(SYMBOL_FRACTION) << std::to_string(denominator);
    else if (numerator!=1)
      ss << std::to_string(numerator);
    return ss.str();
  }
};

class UnitValue {
public:
  NUMBER_DTYPE magnitude;
  std::vector<BaseUnit> baseunits;
  std::string to_string() {
    std::stringstream ss;
    ss << magnitude << std::scientific;
    for (auto unit: baseunits) {
      ss << "*" << unit.to_string();
    }
    return ss.str();
  }
};

class UnitAtom: public exs::AtomBase<UnitValue> {
 public:
  UnitAtom(UnitAtom &a): AtomBase(a) {};
  UnitAtom(UnitValue v): AtomBase(v) {}; 
  static UnitValue from_string(std::string s);
  std::string to_string();
  void math_multiply(UnitAtom *other);
  void math_divide(UnitAtom *other);
};

class UnitSolver {
public:
  std::unique_ptr<exs::Solver<UnitAtom>> solver;
  UnitSolver();
  UnitAtom solve(std::string expression);
};
