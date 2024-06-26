#ifndef PUQ_ARRAY_H
#define PUQ_ARRAY_H

#include <memory>

#ifdef MAGNITUDE_ARRAYS
typedef std::vector<MAGNITUDE_PRECISION> ArrayValue;
class Array {
public:
  ArrayValue value;
  Array(): value({1}) {value.shrink_to_fit();};
  Array(const MAGNITUDE_PRECISION& v): value({v}) {value.shrink_to_fit();};
  Array(const ArrayValue& v): value(v) {value.shrink_to_fit();};
  std::string to_string() const;
  friend Array operator+(const Array& a1, const Array& a2);
  friend Array operator-(const Array& a);
  friend Array operator-(const Array& a1, const Array& a2);
  friend Array operator*(const Array& a1, const Array& a2);
  friend Array operator/(const Array& a1, const Array& a2);
  void operator+=(const Array& a);
  void operator-=(const Array& a);
  void operator*=(const Array& a);
  void operator/=(const Array& a);
  friend Array pow(const Array &a, const EXPONENT_TYPE& e);
  void pow(const EXPONENT_TYPE& e);
#ifdef EXPONENT_FRACTIONS
  friend Array pow(const Array &a, const EXPONENT_INT_PRECISION& e);
  void pow(const EXPONENT_INT_PRECISION& e);
#endif
  bool operator==(const Array& a) const;
  bool operator!=(const Array& a) const;
  friend Array log10(const Array &a);
  friend Array floor(const Array &a);
  friend Array abs(const Array &a);
  friend Array max(const Array &a1, const Array& a2);
};
#endif

#endif // PUQ_ARRAY_H
