#include <numeric>
#include <sstream>

#include "unit_value.h"

#ifdef EXPONENT_FRACTIONS

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

Exponent Exponent::operator*(Exponent &e) {
  Exponent ne;
  ne.numerator = numerator * e.numerator;
  ne.denominator = denominator * e.denominator;
  return ne;
}
void Exponent::operator*=(Exponent const&e) {
  numerator *= e.numerator;
  denominator *= e.denominator;
}

/*
 *  Convert rational exponents to real numbers
 */
EXPONENT_REAL_PRECISION Exponent::to_real() {
  return (EXPONENT_REAL_PRECISION)numerator/(EXPONENT_REAL_PRECISION)denominator;
}

/*
 *  Create a string representation of an exponent
 */
std::string Exponent::to_string() {
  std::stringstream ss;
  rebase();
  if (denominator!=1)
    ss << std::to_string(numerator) << SYMBOL_FRACTION << std::to_string(denominator);
  else if (numerator!=1)
    ss << std::to_string(numerator);
  return ss.str();
}

/*
 *  Reduce fraction to a standard minimal form
 */
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

#endif // EXPONENT_FRACTIONS
