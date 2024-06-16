#ifndef PUQ_SOLVER_H
#define PUQ_SOLVER_H

#include <set>
#include <format>
#include <cmath>

#include "../settings.h"
#include "../../external/exs-cpp/src/exs.h"
#include "../value/value.h"

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

class UnitAtom: public exs::AtomBase<UnitValue> {
 public:
  UnitAtom(UnitAtom &a): AtomBase(a) {};
  UnitAtom(UnitValue v): AtomBase(v) {}; 
  static UnitValue from_string(std::string s);
  std::string to_string();
  void math_power(EXPONENT_TYPE &e);
  void math_multiply(UnitAtom *other);
  void math_divide(UnitAtom *other);
};

class OperatorParentheses: public exs::OperatorGroup<UnitAtom, 1> {
public:
#ifdef FRACTIONAL_EXPONENTS
  EXPONENT_TYPE exponent;
#else
  EXPONENT_TYPE exponent = 1;
#endif
  OperatorParentheses(): OperatorGroup<UnitAtom, 1>("par","(",exs::PARENTHESES_OPERATOR) {}
  virtual void parse(exs::Expression &expr);
  void operate_group(exs::TokenListBase<UnitAtom> *tokens);
};

class UnitSolver {
public:
  std::unique_ptr<exs::Solver<UnitAtom>> solver;
  UnitSolver();
  UnitAtom solve(std::string expression);
};

#endif // PUQ_SOLVER_H
