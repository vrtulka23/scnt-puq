#include <sstream>
#include <iostream>
#include <string>

#include "array.h"

#ifdef MAGNITUDE_ARRAYS

class ArraySizeException : public std::exception {
private:
  std::string message;  
public:
  ArraySizeException(std::string m) : message(m) {}
  ArraySizeException(const ArrayValue& v1, const ArrayValue& v2) : message("Arrays have different sizes: "+std::to_string(v1.size())+" != "+std::to_string(v2.size())) {}
  const char * what () const noexcept override {
    return message.c_str();
  }
};

inline void mutating_operation(ArrayValue& v1, const ArrayValue& v2,
			       void (*func)(MAGNITUDE_PRECISION& v1,
					    const MAGNITUDE_PRECISION& v2)) {
  if (v1.size()==v2.size())    // arrays have same sizes
    for (int i=0; i<v1.size(); i++)
      func(v1[i],v2[i]);       
  else if (v1.size()==1)       // first value is a scalar
    for (int i=0; i<v2.size(); i++)
      func(v1[0],v2[i]);
  else if (v2.size()==1)       // second value is a scalar
    for (int i=0; i<v1.size(); i++)
      func(v1[i],v2[0]);       
  else                         // arrays have different sizes
    throw ArraySizeException(v1, v2);
}

inline ArrayValue const_operation(const ArrayValue& v1, const ArrayValue& v2,
				  MAGNITUDE_PRECISION (*func)(const MAGNITUDE_PRECISION& v1,
							      const MAGNITUDE_PRECISION& v2)) {
  ArrayValue av;
  if (v1.size()==v2.size())    // arrays have same sizes
    for (int i=0; i<v1.size(); i++)
      av.push_back(func(v1[i],v2[i]));
  else if (v1.size()==1)       // first value is a scalar
    for (int i=0; i<v2.size(); i++)
      av.push_back(func(v1[0],v2[i]));
  else if (v2.size()==1)       // second value is a scalar
    for (int i=0; i<v1.size(); i++)
      av.push_back(func(v1[i],v2[0]));
  else                         // arrays have different sizes
    throw ArraySizeException(v1, v2);
  return av;
}

Array Array::filled(const MAGNITUDE_PRECISION& v, const size_t &s) {
  Array a;
  for (size_t i = 0; i<s; i++)
    a.append(v);
  return a;
};

std::string Array::to_string() const {
  std::stringstream ss;
  if (value.size()==1) {
    ss << value[0] << std::scientific;
  } else if (value.size()==2) {
    ss << SYMBOL_ARRAY_START << value[0];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << value[1];
    ss << std::scientific << SYMBOL_ARRAY_END;
  } else if (value.size()>2) {
    ss << SYMBOL_ARRAY_START << value[0];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << value[1];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << SYMBOL_ARRAY_MORE;
    ss << std::scientific << SYMBOL_ARRAY_END;
  }
  return ss.str();
}

size_t Array::size() const {
  return value.size();
};

void Array::append(const MAGNITUDE_PRECISION& v) {
  value.push_back(v);
}

void Array::append(const ArrayValue& v) {
  value.insert(value.end(), v.begin(), v.end());
}

MAGNITUDE_PRECISION Array::operator[](const size_t i) const {
  return value[i];
}

void Array::operator+=(const Array& a) {
  auto fn = [](MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    v1 += v2;
  };
  mutating_operation(value, a.value, fn);
}

Array operator+(const Array& a1, const Array& a2) {
  auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    return v1 + v2;
  };
  ArrayValue av = const_operation(a1.value, a2.value, fn);
  return Array(av);
}

void Array::operator-=(const Array& a) {
  auto fn = [](MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    v1 -= v2;
  };
  mutating_operation(value, a.value, fn);
}

Array operator-(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(-a.value[i]);
  return Array(av);
}

Array operator-(const Array& a1, const Array& a2) {
  auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    return v1 - v2;
  };
  ArrayValue av = const_operation(a1.value, a2.value, fn);
  return Array(av);
}

void Array::operator*=(const Array& a) {
  auto fn = [](MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    v1 *= v2;
  };
  mutating_operation(value, a.value, fn);
}

Array operator*(const Array& a1, const Array& a2) {
  auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    return v1 * v2;
  };
  ArrayValue av = const_operation(a1.value, a2.value, fn);
  return Array(av);
}

void Array::operator/=(const Array& a) {
  auto fn = [](MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    v1 /= v2;
  };
  mutating_operation(value, a.value, fn);
}

Array operator/(const Array& a1, const Array& a2) {
  auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    return v1 / v2;
  };
  ArrayValue av = const_operation(a1.value, a2.value, fn);
  return Array(av);
}

void Array::pow(const EXPONENT_TYPE& e) {
  for (int i=0; i<value.size(); i++)
    value[i] = std::pow(value[i], (EXPONENT_REAL_PRECISION)e);
}

Array pow(const Array &a, const EXPONENT_TYPE& e) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::pow(a.value[i], (EXPONENT_REAL_PRECISION)e));
  return Array(av);
}

#ifdef EXPONENT_FRACTIONS
void Array::pow(const EXPONENT_INT_PRECISION& e) {
  for (int i=0; i<value.size(); i++)
    value[i] = std::pow(value[i], e);
}

Array pow(const Array &a, const EXPONENT_INT_PRECISION& e) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::pow(a.value[i], e));
  return Array(av);
}
#endif

bool Array::operator==(const Array& a) const {
  if (value.size()==a.value.size()) {    // arrays have same sizes
    for (int i=0; i<value.size(); i++)
      if (value[i] != a.value[i]) return false;       
  } else if (value.size()==1) {          // first value is a scalar
    for (int i=0; i<a.value.size(); i++)
      if (value[0] != a.value[i]) return false;
  } else if (a.value.size()==1) {        // second value is a scalar
    for (int i=0; i<value.size(); i++)
      if (value[i] != a.value[0]) return false;       
  } else {                               // arrays have different sizes
    throw ArraySizeException(value, a.value);
  }
  return true;
}

bool Array::operator!=(const Array& a) const {
  if (value.size()==a.value.size()) {    // arrays have same sizes
    for (int i=0; i<value.size(); i++)
      if (value[i] != a.value[i]) return true;       
  } else if (value.size()==1) {          // first value is a scalar
    for (int i=0; i<a.value.size(); i++)
      if (value[0] != a.value[i]) return true;
  } else if (a.value.size()==1) {        // second value is a scalar
    for (int i=0; i<value.size(); i++)
      if (value[i] != a.value[0]) return true;       
  } else {                               // arrays have different sizes
    throw ArraySizeException(value, a.value);
  }
  return false;
}

Array log10(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::log10(a.value[i]));
  return Array(av);
}

Array floor(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::floor(a.value[i]));
  return Array(av);
}

Array abs(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::abs(a.value[i]));
  return Array(av);
}

Array max(const Array& a1, const Array& a2) {
  auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
    return std::max(v1, v2);
  };
  ArrayValue av = const_operation(a1.value, a2.value, fn);
  return Array(av);
}

ArrayValue::const_iterator Array::begin() const {
  return value.begin();
}

ArrayValue::const_iterator Array::end() const {
  return value.end();
}

#endif
