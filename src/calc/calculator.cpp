#include <memory>
#include <regex>

#include "calc.h"

namespace puq {

  Calculator::Calculator() {
    
    exs::OperatorList<CalculatorAtom> operators;
    operators.append(exs::PARENTHESES_OPERATOR,    std::make_shared<exs::OperatorGroup<CalculatorAtom, 1>>("par","( ",exs::PARENTHESES_OPERATOR,"( "," , "," )"));
    operators.append(exs::ADD_OPERATOR,            std::make_shared<exs::OperatorAdd<CalculatorAtom>>(" + "));
    operators.append(exs::SUBTRACT_OPERATOR,       std::make_shared<exs::OperatorSubtract<CalculatorAtom>>(" - "));
    operators.append(exs::MULTIPLY_OPERATOR,       std::make_shared<exs::OperatorMultiply<CalculatorAtom>>(" * "));
    operators.append(exs::DIVIDE_OPERATOR,         std::make_shared<exs::OperatorDivide<CalculatorAtom>>(" / "));
    
    exs::StepList steps;
    steps.append(exs::GROUP_OPERATION,  {exs::PARENTHESES_OPERATOR});
    steps.append(exs::UNARY_OPERATION,  {exs::ADD_OPERATOR, exs::SUBTRACT_OPERATOR});
    steps.append(exs::BINARY_OPERATION, {exs::MULTIPLY_OPERATOR, exs::DIVIDE_OPERATOR});
    steps.append(exs::BINARY_OPERATION, {exs::ADD_OPERATOR, exs::SUBTRACT_OPERATOR});
    
    solver = std::make_unique<exs::Solver<CalculatorAtom>>(operators, steps);
    
  }
  
  CalculatorAtom Calculator::solve(std::string expression) {
#ifdef DEBUG_CALCULATOR
    std::clog << "CALC:  Solving: " << expression << std::endl;
#endif
    CalculatorAtom ca = solver->solve( (expression=="") ? "1" : expression );
#ifdef DEBUG_CALCULATOR
    std::clog << "CALC:  Result:  " << ca.value.to_string() << std::endl;
#endif
    return ca;
  }

}
