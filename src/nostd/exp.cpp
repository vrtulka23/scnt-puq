#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION exp(const MAGNITUDE_PRECISION& e) {
      return std::exp(e);
    }

#ifdef MAGNITUDE_ARRAYS
    Array exp(const Array& e) {
      ArrayValue av;
      for (int i=0; i<e.size(); i++)
	av.push_back(std::exp(e[i]));
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude exp(const Magnitude& e) {
      // z ± Dz = pow(e, y ± Dy) -> Dz = pow(e, y) * log(e) * Dy
      return Magnitude(exp(e.value), exp(e.value)*e.error);
    }
#endif
    
  }
}
