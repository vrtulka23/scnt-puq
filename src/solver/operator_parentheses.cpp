#include "solver.h"

namespace puq {

bool OperatorParentheses::check(exs::Expression &expr) {
#ifdef MAGNITUDE_ERRORS
  if (expr.left.size()>0) {
    char c = expr.left.back();
    if (std::isdigit(c) || c=='.') {
      return false;  // ignore parentheses if in the numerical value
    }
  }
#endif
  return expr.right.rfind(symbol, 0) == 0;
}

void OperatorParentheses::parse(exs::Expression &expr) {
  OperatorGroup<UnitAtom, 1>::parse(expr); // perform ordinary parsing
  if (expr.right.length()>0) { // check if there is an exponent after closing parentheses
    std::smatch m;
#ifdef EXPONENT_FRACTIONS
    std::regex rx_exponent("^([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)");
    if (std::regex_search(expr.right, m, rx_exponent)) { // store exponent
      exponent = Exponent((m[1]==""?1:std::stoi(m[1])), (m[3]==""?1:std::stoi(m[3])));
      expr.remove(m[0]); 
    }
#else
    std::regex rx_exponent("^([+-]?[0-9]*)");
    if (std::regex_search(expr.right, m, rx_exponent)) { // store exponent
      if (m[1]!="") exponent   = std::stoi(m[1]);
      expr.remove(m[0]); 
    }      
#endif
  }
};

void OperatorParentheses::operate_group(exs::TokenListBase<UnitAtom> *tokens) {
  if (exponent!=1) {
    exs::Token<UnitAtom> group1 = tokens->get_left();
    group1.atom->math_power(exponent);
    tokens->put_left(group1);
  }
};

}
