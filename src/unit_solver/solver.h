#include "../settings.h"
#include "../../external/exs-cpp/src/exs.h"

#include <set>

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

struct BaseUnit {
  std::string prefix;
  std::string unit;
  int numerator;
  int denominator;
};

struct UnitValue {
  NUMBER_DTYPE magnitude;
  std::vector<BaseUnit> baseunits;
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
