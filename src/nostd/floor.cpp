#include "nostd.h"

namespace puq {
  namespace nostd {

    extern MAGNITUDE_PRECISION floor(const MAGNITUDE_PRECISION& m) {
      return std::floor(m);
    }

#ifdef MAGNITUDE_ARRAYS
    extern Array floor(const Array& a) {
      ArrayValue av;
      for (int i=0; i<a.size(); i++)
	av.push_back(std::floor(a[i]));
      return Array(av);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    extern Magnitude floor(const Magnitude& m) {
      return Magnitude(floor(m.value));
    }
#endif

  }
}
