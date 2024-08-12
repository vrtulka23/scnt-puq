#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION log(const MAGNITUDE_PRECISION& m) {
      return std::log(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array log(const Array& a) {
      ArrayValue av(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::log(a[i]);
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude log(const Magnitude& m) {
      // y ± Dy = log10(x ± Dx) -> Dy = Dx / x
      return Magnitude(log(m.value), m.error/m.value);  
    }
#endif
    
  }
}
