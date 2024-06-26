#ifndef PUQ_MAGNITUDE_H
#define PUQ_MAGNITUDE_H

#ifdef MAGNITUDE_ERRORS
class Magnitude {
public:
#ifdef MAGNITUDE_ARRAYS
  Array value;
  Array error;
#else
  MAGNITUDE_PRECISION value;
  MAGNITUDE_PRECISION error;
#endif
  Magnitude(): value(1), error(0) {}
  Magnitude(const MAGNITUDE_PRECISION& m): value(m), error(0) {}
  Magnitude(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e): value(m), error(e) {}
  static MAGNITUDE_PRECISION abs_to_rel(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& a);
  static MAGNITUDE_PRECISION rel_to_abs(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& r);
#ifdef MAGNITUDE_ARRAYS
  Magnitude(const Array& m): value(m), error(0) {}
  Magnitude(const Array& m, const Array& e): value(m), error(e) {}
  static Array abs_to_rel(const Array& v, const Array& a);
  static Array rel_to_abs(const Array& v, const Array& r);
#endif
  std::string to_string() const;
  friend Magnitude operator+(const Magnitude& m1, const Magnitude& m);
  friend Magnitude operator-(const Magnitude& m1, const Magnitude& m);
  friend Magnitude operator*(const Magnitude& m1, const Magnitude& m);
  friend Magnitude operator/(const Magnitude& m1, const Magnitude& m);
  void operator+=(const Magnitude& m);
  void operator-=(const Magnitude& m);
  void operator*=(const Magnitude& m);
  void operator/=(const Magnitude& m);
  friend Magnitude pow(const Magnitude& m, const EXPONENT_TYPE& e);
  void pow(const EXPONENT_TYPE& e);
};
#endif

#endif // PUQ_MAGNITUDE_H
