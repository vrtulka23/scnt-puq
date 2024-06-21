#include <sstream>
#include <cmath>
#include <iostream>
#include <format>
#include<algorithm>

#include "unit_value.h"

#ifdef MAGNITUDE_ERRORS

/*
 * Convert absolute to relative (in %) error
 */
MAGNITUDE_PRECISION Magnitude::abs_to_rel(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&a) {
  return 100*a/v;
};

/*
 * Convert relative (in %) error to absolute
 */
MAGNITUDE_PRECISION Magnitude::rel_to_abs(MAGNITUDE_PRECISION const&v, MAGNITUDE_PRECISION const&r) {
  return v*r/100;
};

/*
 * Return a string representation of a magnitude
 */
std::string Magnitude::to_string() {
  std::stringstream ss;
  if (error==0) {
    ss << value << std::scientific;
  } else {
    int exp_mag  = std::floor(std::log10(value));
    int exp_err  = std::floor(std::log10(error));
    int exp_diff = std::abs(exp_mag-exp_err)+1;
    MAGNITUDE_PRECISION val_mag = value*std::pow(10,-exp_mag);
    int val_err  = std::round(error*std::pow(10,1-exp_err));
    ss << std::vformat("{:.0"+std::to_string(exp_diff)+"f}", std::make_format_args(val_mag));
    ss << std::format("({:2d})", val_err);
    if (exp_mag!=0)
      ss << (exp_mag>=0 ? "e+" : "e-") << std::format("{:-02d}", std::abs(exp_mag));
  }
  return ss.str();
}

/*
 * Add two magnitudes
 */
Magnitude Magnitude::operator+(Magnitude const&m) {
  return Magnitude(value+m.value, error+m.error);
}
void Magnitude::operator+=(Magnitude const&m) {
  value += m.value;
  error += m.error;
}

/*
 * Subtract two magnitudes
 */
Magnitude Magnitude::operator-(Magnitude const&m) {
  return Magnitude(value-m.value, error+m.error);
}
void Magnitude::operator-=(Magnitude const&m) {
  value -= m.value;
  error += m.error;
}

/*
 * Multiply magnitude by another magnitude
 */
const Magnitude multiply(Magnitude const*m, Magnitude const*n) {
  Magnitude nm(m->value * n->value);
  if (m->error==0 && n->error==0) {
      nm.error = 0;
  } else if (m->error==0 && n->error!=0) {
    nm.error = n->error * m->value;
  } else if (m->error!=0 && n->error==0) {
    nm.error = m->error * n->value;    
  } else {
    MAGNITUDE_PRECISION maxerror = std::abs((m->value+m->error)*(n->value+n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs((m->value-m->error)*(n->value-n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);
  }
  return nm;
}
Magnitude Magnitude::operator*(Magnitude const&m) {
  return multiply(this, &m);
}
void Magnitude::operator*=(Magnitude const&m) {
  Magnitude nm = multiply(this, &m);
  value = nm.value;
  error = nm.error;
}

/*
 * Divide magnitude by another magnitude
 */
const Magnitude divide(Magnitude const*m, Magnitude const*n) {
  Magnitude nm(m->value / n->value);
  if (m->error==0 && n->error==0) {
      nm.error = 0;
  } else if (m->error==0 && n->error!=0) {
    MAGNITUDE_PRECISION maxerror = std::abs(m->value/(n->value+n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs(m->value/(n->value-n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);    
  } else if (m->error!=0 && n->error==0) {
    nm.error = m->error / n->value;    
  } else {
    MAGNITUDE_PRECISION maxerror = std::abs((m->value+m->error)/(n->value-n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs((m->value-m->error)/(n->value+n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);
  }
  return nm;
}
Magnitude Magnitude::operator/(Magnitude const&m) {
  return divide(this, &m);
}
void Magnitude::operator/=(Magnitude const&m) {
  Magnitude nm = divide(this, &m);
  value = nm.value;
  error = nm.error;
}

/*
 *  Rise magnitude to the power of an exponent (not a binary operation!!)
 */
Magnitude Magnitude::operator^(EXPONENT_TYPE &e) {
  Magnitude nm;
#ifdef EXPONENT_FRACTIONS
  nm.value = std::pow(value, e.to_real());
#else
  nm.value = std::pow(value, e);
#endif
  return nm;
}
void Magnitude::operator^=(EXPONENT_TYPE &e) {
#ifdef EXPONENT_FRACTIONS
  value = std::pow(value, e.to_real());
#else
  value = std::pow(value, e);
#endif
}

#endif
