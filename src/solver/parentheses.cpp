#include "unit_solver.h"

void OperatorParentheses::parse(exs::Expression &expr) {
  OperatorGroup<UnitAtom, 1>::parse(expr); // perform ordinary parsing
  if (expr.right.length()>0) { // check if there is an exponent after closing parentheses
    std::smatch m;
#ifdef EXPONENT_FRACTIONS
    std::regex rx_exponent("^([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)");
    if (std::regex_search(expr.right, m, rx_exponent)) { // store exponent
      if (m[1]!="") exponent.numerator   = std::stoi(m[1]);
      if (m[3]!="") exponent.denominator = std::stoi(m[3]);
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
#ifdef EXPONENT_FRACTIONS
  if (exponent.numerator!=1 || exponent.denominator!=1) { // apply exponent to parentheses atom
#else
  if (exponent!=1) {
#endif
    exs::Token<UnitAtom> group1 = tokens->get_left();
    group1.atom->math_power(exponent);
    tokens->put_left(group1);
  }
};
