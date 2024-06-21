#ifndef PUQ_EXPONENT_H
#define PUQ_EXPONENT_H

#ifdef EXPONENT_FRACTIONS
class Exponent {
public:
  EXPONENT_INT_PRECISION numerator;
  EXPONENT_INT_PRECISION denominator;
  Exponent(): numerator(1), denominator(1) {}
  Exponent(EXPONENT_INT_PRECISION const&n): numerator(n), denominator(1) {};
  Exponent(EXPONENT_INT_PRECISION const&n, EXPONENT_INT_PRECISION const&d): numerator(n), denominator(d) {};
  Exponent operator*(Exponent &e);
  void operator+=(Exponent const&e);
  void operator-=(Exponent const&e);
  void operator*=(Exponent const&e);
  bool operator==(Exponent const&d) const;
  bool operator!=(Exponent const&d) const;
  EXPONENT_REAL_PRECISION to_real();
  std::string to_string();
  void rebase();
};
#endif

#endif // PUQ_EXPONENT_H
