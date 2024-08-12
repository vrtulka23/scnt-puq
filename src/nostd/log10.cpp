#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION log10(const MAGNITUDE_PRECISION& m) {
      return std::log10(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array log10(const Array& a) {
      ArrayValue av(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::log10(a[i]);
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude log10(const Magnitude& m) {
      // y ± Dy = log(x ± Dx) -> Dy = 1 / ln(10) * Dx / x 
      return Magnitude(log10(m.value), m.error/(m.value*std::log(10)));  
    }
#endif
    
  }
}
