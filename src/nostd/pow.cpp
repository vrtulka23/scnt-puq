#include "nostd.h"

namespace puq {
  namespace nostd {

    extern MAGNITUDE_PRECISION pow(const MAGNITUDE_PRECISION& m, const EXPONENT_REAL_PRECISION& e) {
      return std::pow(m, e);
    }

#ifdef MAGNITUDE_ARRAYS
    extern Array pow(const Array &a, const EXPONENT_REAL_PRECISION& e) {
      ArrayValue av;
      for (int i=0; i<a.size(); i++)
	av.push_back(std::pow(a[i], e));
      return Array(av);
    }
    extern Array pow(const Array &a, const Array& e) {
      auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
	return std::pow(v1, v2);
      };
      return Array::const_operation(a, e, fn);
    }
#endif

#ifdef MAGNITUDE_ERRORS
    extern Magnitude pow(const Magnitude& m, const EXPONENT_REAL_PRECISION& e) {
      // z ± Dz = pow(x ± Dx, y) -> Dz = y * pow(x, y-1) * Dx 
      return Magnitude(pow(m.value, e), e*pow(m.value, e-1)*m.error);  
    }
    extern Magnitude pow(const Magnitude& m, const Magnitude& e) {
      MAGNITUDE_VALUE Dzx = e.value*pow(m.value, e.value-1)*m.error;     // Dzx = y * pow(x, y-1) * Dx 
      MAGNITUDE_VALUE Dzy = pow(m.value, e.value)*log(m.value)*e.error;  // Dzy = pow(x, y) * log(x) * Dy
      // Dz = sqrt(pow(Dzx,2)+pow(Dzy,2))
      // z ± Dz = pow(x ± Dx, y ± Dy)
      return Magnitude(pow(m.value, e.value), sqrt(Dzx*Dzx+Dzy*Dzy));
    }
#endif
    
  }
}
