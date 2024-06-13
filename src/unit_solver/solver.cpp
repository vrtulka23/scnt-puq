#include <memory>

#include "solver.h"

UnitSolver::UnitSolver() {

  exs::OperatorList<UnitAtom> operators;
  operators.append(exs::PARENTHESES_OPERATOR,    std::make_shared<exs::OperatorParentheses<UnitAtom>>());
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
