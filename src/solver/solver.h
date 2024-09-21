#ifndef PUQ_SOLVER_H
#define PUQ_SOLVER_H

#include <set>
#include <format>
#include <cmath>
#include <scnt-exs/exs.h>

#include "../settings.h"
#include "../value/value.h"
#include "../lists/lists.h"

namespace puq {

class AtomParsingExcept: public std::exception {
private:
  std::string message;  
public:
  AtomParsingExcept(const std::string& m) : message(m) {}
  const char * what () const noexcept override {
    return message.c_str();
  }
};
  
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
  std::vector<EXPONENT_TYPE> exponent;
  OperatorParentheses(): OperatorGroup<UnitAtom, 1>("par","(",exs::PARENTHESES_OPERATOR) {}
  virtual bool check(exs::Expression &expr); 
  virtual void parse(exs::Expression &expr);
  void operate_group(exs::TokenListBase<UnitAtom> *tokens);
};

#ifdef MAGNITUDE_ARRAYS

enum CustomOperatorType {
  ARRAY_OPERATOR = exs::NUM_OPERATOR_TYPES
};

class OperatorArray: public exs::OperatorGroup<UnitAtom> {
public:
  OperatorArray():
    OperatorGroup<UnitAtom>("arr", SYMBOL_ARRAY_START, ARRAY_OPERATOR,
			    SYMBOL_ARRAY_START, SYMBOL_ARRAY_SEPARATOR, SYMBOL_ARRAY_END) {}
  void operate_group(exs::TokenListBase<UnitAtom> *tokens);
};

#endif

class UnitSolver {
public:
  std::unique_ptr<exs::Solver<UnitAtom>> solver;
  UnitSolver();
  UnitAtom solve(std::string expression);
};

}
  
#endif // PUQ_SOLVER_H
