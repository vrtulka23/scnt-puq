#ifndef PUQ_ARRAY_H
#define PUQ_ARRAY_H

#include <vector>
#include <array>

#include "settings.h"
#include "exponent.h"

#ifdef MAGNITUDE_ARRAYS
typedef std::vector<MAGNITUDE_PRECISION> ArrayValue;
class Array {
private:
  ArrayValue value;
public:
  Array(): value() {};
  Array(const MAGNITUDE_PRECISION& v): value({v}) {value.shrink_to_fit();};
  Array(const ArrayValue& v): value(v) {value.shrink_to_fit();};
  static Array filled(const MAGNITUDE_PRECISION& v, const size_t &s);
  std::string to_string() const;
  size_t size() const;
  void append(const MAGNITUDE_PRECISION& v);
  void append(const ArrayValue& v);
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
  MAGNITUDE_PRECISION operator[](const size_t i) const;
  friend Array log10(const Array &a);
  friend Array floor(const Array &a);
  friend Array abs(const Array &a);
  friend Array max(const Array &a1, const Array& a2);
  ArrayValue::const_iterator begin() const;
  ArrayValue::const_iterator end() const;
};
#endif

#endif // PUQ_ARRAY_H
