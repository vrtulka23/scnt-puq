#ifndef PUQ_EXPONENT_H
#define PUQ_EXPONENT_H

#import "settings.h"

namespace puq {

#ifdef EXPONENT_FRACTIONS

class Exponent {
private:
  EXPONENT_INT_PRECISION numerator;
  EXPONENT_INT_PRECISION denominator;
public:
  Exponent(): numerator(1), denominator(1) {}
  Exponent(const EXPONENT_INT_PRECISION& n): numerator(n), denominator(1) {};
  Exponent(const EXPONENT_INT_PRECISION& n, const EXPONENT_INT_PRECISION& d): numerator(n), denominator(d) {};
  friend Exponent operator*(const Exponent& e1, const Exponent& e2);
  Exponent operator-() const;
  void operator+=(const Exponent& e);
  void operator-=(const Exponent& e);
  void operator*=(const Exponent& e);
  bool operator==(const Exponent& e) const;
  bool operator!=(const Exponent& e) const;
  bool operator==(const EXPONENT_INT_PRECISION& e) const;
  bool operator!=(const EXPONENT_INT_PRECISION& e) const;
  bool operator==(const EXPONENT_REAL_PRECISION& e) const;
  bool operator!=(const EXPONENT_REAL_PRECISION& e) const;
  EXPONENT_REAL_PRECISION to_real() const;
  operator EXPONENT_REAL_PRECISION() const;
  std::string to_string() const;
  void reduce();
};

#endif

}
  
#endif // PUQ_EXPONENT_H
