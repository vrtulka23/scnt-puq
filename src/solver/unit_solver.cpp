#include <memory>
#include <regex>

#include "solver.h"

namespace puq {

UnitSolver::UnitSolver() {

  exs::OperatorList<UnitAtom> operators;
  operators.append(exs::PARENTHESES_OPERATOR,    std::make_shared<OperatorParentheses>());
#ifdef MAGNITUDE_ARRAYS
  operators.append(ARRAY_OPERATOR,               std::make_shared<OperatorArray>());
#endif
  operators.append(exs::MULTIPLY_OPERATOR,       std::make_shared<exs::OperatorMultiply<UnitAtom>>(SYMBOL_MULTIPLY));
  operators.append(exs::DIVIDE_OPERATOR,         std::make_shared<exs::OperatorDivide<UnitAtom>>(SYMBOL_DIVIDE));

  exs::StepList steps;
#ifdef MAGNITUDE_ARRAYS
  steps.append(exs::GROUP_OPERATION,  {exs::PARENTHESES_OPERATOR, ARRAY_OPERATOR});
#else
  steps.append(exs::GROUP_OPERATION,  {exs::PARENTHESES_OPERATOR});
#endif
  steps.append(exs::BINARY_OPERATION, {exs::MULTIPLY_OPERATOR, exs::DIVIDE_OPERATOR});

  solver = std::make_unique<exs::Solver<UnitAtom>>(operators, steps);
  
}

UnitAtom UnitSolver::solve(std::string expression) {
  if (expression=="")
    return solver->solve("1");
  else
    return solver->solve(expression);
}

}
