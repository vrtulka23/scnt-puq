#include <sstream>
#include <cmath>
#include <iostream>
#include <format>
#include <algorithm>

#include "value/unit_value.h"

#ifdef MAGNITUDE_ERRORS

/*
 * Convert absolute to relative (in %) error
 */
MAGNITUDE_PRECISION Magnitude::abs_to_rel(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& a) {
  return 100*a/v;
};

#ifdef MAGNITUDE_ARRAYS
Array Magnitude::abs_to_rel(const Array& v, const Array& a) {
  return 100*a/v;
};
#endif

/*
 * Convert relative (in %) error to absolute
 */
MAGNITUDE_PRECISION Magnitude::rel_to_abs(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& r) {
  return v*r/100;
};

#ifdef MAGNITUDE_ARRAYS
Array Magnitude::rel_to_abs(const Array& v, const Array& r) {
  return v*r/100;
};
#endif

/*
 * Return a string representation of a magnitude
 */
std::string Magnitude::to_string() const {
  std::stringstream ss;
  if (error==0) {
#ifdef MAGNITUDE_ARRAYS
    ss << value.to_string();
#else
    ss << value << std::scientific;
#endif
  } else {
#ifdef MAGNITUDE_ARRAYS
    int exp_mag  = std::floor(std::log10(value.value[0]));
    int exp_err  = std::floor(std::log10(error.value[0]));
    int exp_diff = std::abs(exp_mag-exp_err)+1;
    MAGNITUDE_PRECISION val_mag = value.value[0]*std::pow(10,-exp_mag);
    int val_err  = std::round(error.value[0]*std::pow(10,1-exp_err));
#else
    int exp_mag  = std::floor(std::log10(value));
    int exp_err  = std::floor(std::log10(error));
    int exp_diff = std::abs(exp_mag-exp_err)+1;
    MAGNITUDE_PRECISION val_mag = value*std::pow(10,-exp_mag);
    int val_err  = std::round(error*std::pow(10,1-exp_err));
#endif
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
Magnitude operator+(const Magnitude& m1, const Magnitude& m2) {
  return Magnitude(m1.value+m2.value, m1.error+m2.error);
}

void Magnitude::operator+=(const Magnitude& m) {
  value += m.value;
  error += m.error;
}

/*
 * Subtract two magnitudes
 */
Magnitude operator-(const Magnitude& m1, const Magnitude& m2) {
  return Magnitude(m1.value-m2.value, m1.error+m2.error);
}

void Magnitude::operator-=(const Magnitude& m) {
  value -= m.value;
  error += m.error;
}

/*
 * Multiply magnitude by another magnitude
 */
const Magnitude multiply(const Magnitude* m, const Magnitude* n) {
  Magnitude nm(m->value * n->value);
  if (m->error==0 && n->error==0) {
      nm.error = 0;
  } else if (m->error==0 && n->error!=0) {
    nm.error = n->error * m->value;
  } else if (m->error!=0 && n->error==0) {
    nm.error = m->error * n->value;    
  } else {
#ifdef MAGNITUDE_ARRAYS
    Array maxerror = abs((m->value+m->error)*(n->value+n->error) - nm.value);
    Array minerror = abs((m->value-m->error)*(n->value-n->error) - nm.value);
    nm.error = max(maxerror,minerror);
#else
    MAGNITUDE_PRECISION maxerror = std::abs((m->value+m->error)*(n->value+n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs((m->value-m->error)*(n->value-n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);
#endif
  }
  return nm;
}

Magnitude operator*(const Magnitude& m1, const Magnitude& m2) {
  return multiply(&m1, &m2);
}

void Magnitude::operator*=(const Magnitude& m) {
  Magnitude nm = multiply(this, &m);
  value = nm.value;
  error = nm.error;
}

/*
 * Divide magnitude by another magnitude
 */
const Magnitude divide(const Magnitude* m, const Magnitude* n) {
  Magnitude nm(m->value / n->value);
  if (m->error==0 && n->error==0) {
      nm.error = 0;
  } else if (m->error==0 && n->error!=0) {
#ifdef MAGNITUDE_ARRAYS
    Array maxerror = abs(m->value/(n->value+n->error) - nm.value);
    Array minerror = abs(m->value/(n->value-n->error) - nm.value);
    nm.error = max(maxerror,minerror);
#else
    MAGNITUDE_PRECISION maxerror = std::abs(m->value/(n->value+n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs(m->value/(n->value-n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);
#endif
  } else if (m->error!=0 && n->error==0) {
    nm.error = m->error / n->value;    
  } else {
#ifdef MAGNITUDE_ARRAYS
    Array maxerror = abs((m->value+m->error)/(n->value-n->error) - nm.value);
    Array minerror = abs((m->value-m->error)/(n->value+n->error) - nm.value);
    nm.error = max(maxerror,minerror);
#else
    MAGNITUDE_PRECISION maxerror = std::abs((m->value+m->error)/(n->value-n->error) - nm.value);
    MAGNITUDE_PRECISION minerror = std::abs((m->value-m->error)/(n->value+n->error) - nm.value);
    nm.error = std::max(maxerror,minerror);
#endif
  }
  return nm;
}

Magnitude operator/(const Magnitude& m1, const Magnitude& m2) {
  return divide(&m1, &m2);
}

void Magnitude::operator/=(const Magnitude& m) {
  Magnitude nm = divide(this, &m);
  value = nm.value;
  error = nm.error;
}

/*
 *  Rise magnitude to the power of an exponent (not a binary operation!!)
 */
Magnitude pow(const Magnitude& m, const EXPONENT_TYPE& e) {
  Magnitude nm;
#ifdef MAGNITUDE_ARRAYS
  nm.value = pow(m.value, (EXPONENT_REAL_PRECISION)e);
#else
  nm.value = std::pow(m.value, (EXPONENT_REAL_PRECISION)e);
#endif
  return nm;
}

void Magnitude::pow(const EXPONENT_TYPE& e) {
#ifdef MAGNITUDE_ARRAYS
  value.pow((EXPONENT_REAL_PRECISION)e);
#else
  value = std::pow(value, (EXPONENT_REAL_PRECISION)e);
#endif
}

#endif
