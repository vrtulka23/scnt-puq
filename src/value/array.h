#ifndef PUQ_ARRAY_H
#define PUQ_ARRAY_H

#ifdef MAGNITUDE_ARRAYS
class Array {
public:
  MAGNITUDE_PRECISION value;
  Array(): value(1) {};
  Array(MAGNITUDE_PRECISION const&v): value(v) {};
  std::string to_string();
  Array operator+(Array const&a);
  Array operator-(Array const&a);
  Array operator*(Array const&a);
  Array operator/(Array const&a);
  Array operator^(EXPONENT_TYPE &e);
  void operator+=(Array const&a);
  void operator-=(Array const&a);
  void operator*=(Array const&a);
  void operator/=(Array const&a);
  void operator^=(EXPONENT_TYPE &e);
  bool operator==(Array const&a) const;
};
#endif

#endif // PUQ_ARRAY_H
