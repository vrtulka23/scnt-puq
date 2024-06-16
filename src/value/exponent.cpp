#include <numeric>
#include <sstream>

#include "value.h"

#ifdef FRACTIONAL_EXPONENTS

void Exponent::operator+=(Exponent const&e) {
  if (denominator==e.denominator) {
    numerator += e.numerator;
  } else {
    numerator = numerator*e.denominator+denominator*e.numerator;
    denominator = denominator*e.denominator;
  }
}

void Exponent::operator-=(Exponent const&e) {
  if (denominator==e.denominator) {
    numerator -= e.numerator;
  } else {
    numerator = numerator*e.denominator-denominator*e.numerator;
    denominator = denominator*e.denominator;
  }
}

void Exponent::operator*=(Exponent const&e) {
  numerator *= e.numerator;
  denominator *= e.denominator;
}

std::string Exponent::to_string() {
  std::stringstream ss;
  rebase();
  if (denominator!=1)
    ss << std::to_string(numerator) << SYMBOL_FRACTION << std::to_string(denominator);
  else if (numerator!=1)
    ss << std::to_string(numerator);
  return ss.str();
}

void Exponent::rebase() {
  if (numerator==0) { // zero exponent
    numerator = 0;
    denominator = 1;
    return;
  }
  if (denominator<0) { // keep minus sign in a numerator
    numerator = -numerator;
    denominator = -denominator;
  }
  int gcd = std::gcd(numerator,denominator);
  if (gcd>1) {
    numerator = numerator/gcd;
    denominator = denominator/gcd;
  }
}

#endif // FRACTIONAL_EXPONENTS
