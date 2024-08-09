#include "nostd.h"

namespace puq {
  namespace nostd {
  
    extern MAGNITUDE_PRECISION abs(const MAGNITUDE_PRECISION& m) {
      return std::abs(m);
    }

#ifdef MAGNITUDE_ARRAYS
    extern Array abs(const Array& a) {
      ArrayValue av;
      for (int i=0; i<a.size(); i++)
	av.push_back(std::abs(a[i]));
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    extern Magnitude abs(const Magnitude& m) {
      return Magnitude(abs(m.value));
    }
#endif

  }
}
