#include <numeric>
#include <sstream>

#include "value/unit_value.h"

#ifdef EXPONENT_FRACTIONS

void Exponent::operator+=(const Exponent& e) {
  if (denominator==e.denominator) {
    numerator += e.numerator;
  } else {
    numerator = numerator*e.denominator+denominator*e.numerator;
    denominator = denominator*e.denominator;
  }
}

void Exponent::operator-=(const Exponent& e) {
  if (denominator==e.denominator) {
    numerator -= e.numerator;
  } else {
    numerator = numerator*e.denominator-denominator*e.numerator;
    denominator = denominator*e.denominator;
  }
}

Exponent operator*(const Exponent& e1, const Exponent& e2) {
  Exponent ne;
  ne.numerator = e1.numerator * e2.numerator;
  ne.denominator = e1.denominator * e2.denominator;
  ne.rebase();
  return ne;
}
void Exponent::operator*=(const Exponent& e) {
  numerator *= e.numerator;
  denominator *= e.denominator;
}

Exponent Exponent::operator-() const {
  return Exponent(-numerator, denominator);
}

bool Exponent::operator==(const Exponent& e) const {
  return to_real() == e.to_real();
}

bool Exponent::operator!=(const Exponent& e) const {
  return to_real() != e.to_real();
}

bool Exponent::operator==(const EXPONENT_INT_PRECISION& e) const {
  return to_real() == e;
}

bool Exponent::operator!=(const EXPONENT_INT_PRECISION& e) const {
  return to_real() != e;
}

bool Exponent::operator==(const EXPONENT_REAL_PRECISION& e) const {
  return to_real() == e;
}

bool Exponent::operator!=(const EXPONENT_REAL_PRECISION& e) const {
  return to_real() != e;
}

/*
 *  Convert rational exponents to real numbers
 */
EXPONENT_REAL_PRECISION Exponent::to_real() const {
  return (EXPONENT_REAL_PRECISION)numerator/(EXPONENT_REAL_PRECISION)denominator;
}

/*
 *  Create a string representation of an exponent
 */
std::string Exponent::to_string() const {
  Exponent e = rebase();
  std::stringstream ss;
  if (e.denominator!=1)
    ss << std::to_string(e.numerator) << SYMBOL_FRACTION << std::to_string(e.denominator);
  else if (e.numerator!=1)
    ss << std::to_string(e.numerator);
  return ss.str();
}

/*
 *  Reduce fraction to a standard minimal form
 */
Exponent Exponent::rebase() const {
  Exponent e(numerator, denominator);
  if (e.numerator==0) { // zero exponent
    e.numerator = 0;
    e.denominator = 1;
    return e;
  }
  if (e.denominator<0) { // keep minus sign in a numerator
    e.numerator = -e.numerator;
    e.denominator = -e.denominator;
  }
  int gcd = std::gcd(e.numerator,e.denominator);
  if (gcd>1) {
    e.numerator = e.numerator/gcd;
    e.denominator = e.denominator/gcd;
  }
  return e;
}

Exponent::operator EXPONENT_REAL_PRECISION() const {
  return to_real();
}

#endif // EXPONENT_FRACTIONS
