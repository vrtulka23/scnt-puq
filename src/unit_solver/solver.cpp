#include <memory>
#include <regex>

#include "solver.h"

static constexpr int N = 1;
class OperatorParentheses: public exs::OperatorGroup<UnitAtom, N> {
public:
  Exponent exponent;
  OperatorParentheses(): OperatorGroup<UnitAtom, N>("par","(",exs::PARENTHESES_OPERATOR) {}
  virtual void parse(exs::Expression &expr) {
    OperatorGroup<UnitAtom, N>::parse(expr); // perform ordinary parsing
    if (expr.right.length()>0) { // check if there is an exponent after closing parentheses
      std::smatch m;
      std::regex rx_exponent("^([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)");
      if (std::regex_search(expr.right, m, rx_exponent)) { // store exponent
	if (m[1]!="") exponent.numerator   = std::stoi(m[1]);
	if (m[3]!="") exponent.denominator = std::stoi(m[3]);
	expr.remove(m[0]); 
      }
    }
  };
  void operate_group(exs::TokenListBase<UnitAtom> *tokens) {
    if (exponent.numerator!=1 || exponent.denominator!=1) { // apply exponent to parentheses atom
      exs::Token<UnitAtom> group1 = tokens->get_left();
      group1.atom->math_power(exponent);
      tokens->put_left(group1);
    }
  };
};

UnitSolver::UnitSolver() {

  exs::OperatorList<UnitAtom> operators;
  operators.append(exs::PARENTHESES_OPERATOR,    std::make_shared<OperatorParentheses>());
  operators.append(exs::MULTIPLY_OPERATOR,       std::make_shared<exs::OperatorMultiply<UnitAtom>>(SYMBOL_MULTIPLY));
  operators.append(exs::DIVIDE_OPERATOR,         std::make_shared<exs::OperatorDivide<UnitAtom>>(SYMBOL_DIVIDE));

  exs::StepList steps;
  steps.append(exs::GROUP_OPERATION,  {exs::PARENTHESES_OPERATOR});
  steps.append(exs::BINARY_OPERATION, {exs::MULTIPLY_OPERATOR, exs::DIVIDE_OPERATOR});

  solver = std::make_unique<exs::Solver<UnitAtom>>(operators, steps);
  
}

UnitAtom UnitSolver::solve(std::string expression) {
  return solver->solve(expression);
}
