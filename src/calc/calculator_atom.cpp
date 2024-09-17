#include <regex>
#include <algorithm>

#include "../nostd/nostd.h"
#include "../value/value.h"
#include "calc.h"

namespace puq {
  
Quantity CalculatorAtom::from_string(std::string expr_orig) {
  std::string expr = expr_orig;
  std::smatch m;
  std::regex rx_number("^([^\\s]+)$");
  if (std::regex_match(expr, m, rx_number)) {
    return Quantity(expr);
  } else {
    throw CalculatorExcept("Invalid unit expression: "+expr_orig);
  }
}

std::string CalculatorAtom::to_string() {
  return value.to_string();
}

void CalculatorAtom::math_add(CalculatorAtom *other) {
  value += other->value;
}

void CalculatorAtom::math_subtract(CalculatorAtom *other) {
  value -= other->value;
}

void CalculatorAtom::math_negate() {
  value = -value;
}

void CalculatorAtom::math_multiply(CalculatorAtom *other) {
  value *= other->value;
}

void CalculatorAtom::math_divide(CalculatorAtom *other) {
  value /= other->value;
}

}
