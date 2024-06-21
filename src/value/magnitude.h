#ifndef PUQ_MAGNITUDE_H
#define PUQ_MAGNITUDE_H

#ifdef MAGNITUDE_ERRORS
class Magnitude {
public:
  MAGNITUDE_PRECISION value;
  MAGNITUDE_PRECISION error;
  Magnitude(): value(1), error(0) {}
  Magnitude(MAGNITUDE_PRECISION const&m): value(m), error(0) {}
  Magnitude(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e): value(m), error(e) {}
  static MAGNITUDE_PRECISION abs_to_rel(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&a);
  static MAGNITUDE_PRECISION rel_to_abs(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&r);
  std::string to_string();
  Magnitude operator*(Magnitude const&m);
  Magnitude operator/(Magnitude const&m);
  Magnitude operator^(EXPONENT_TYPE &e);
  void operator*=(Magnitude const&m);
  void operator/=(Magnitude const&m);
  void operator^=(EXPONENT_TYPE &e);
};
#endif

#endif // PUQ_MAGNITUDE_H
