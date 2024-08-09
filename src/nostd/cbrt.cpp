#include "nostd.h"

namespace puq {
  namespace nostd {

    extern MAGNITUDE_PRECISION cbrt(const MAGNITUDE_PRECISION& m) {
      return std::cbrt(m);
    }

#ifdef MAGNITUDE_ARRAYS
    extern Array cbrt(const Array& a) {
      ArrayValue av;
      for (int i=0; i<a.size(); i++)
	av.push_back(std::cbrt(a[i]));
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    extern Magnitude cbrt(const Magnitude& m) {
      // y ± Dz = pow(x ± Dx, 1/3) -> Dy = 1/3 * pow(x, -2/3) * Dx
      constexpr MAGNITUDE_PRECISION third = 1./3.;
      return Magnitude(cbrt(m.value), third*pow(m.value, -2*third)*m.error);  
    }
#endif
    
  }
}
