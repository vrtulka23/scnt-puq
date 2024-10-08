#ifndef PUQ_LISTS_H
#define PUQ_LISTS_H

#include <vector>
#include <string>

#include "systems.h"

namespace puq {


  std::string table_header(std::string title, std::vector<std::string> header, std::vector<int> width);

  namespace lists { 
    std::string unit_systems();
    std::string prefixes();
    std::string base_units();
    std::string derived_units();
    std::string constants();
    std::string quantities();
#ifdef UNITS_TEMPERATURES
    std::string temperature_units();
#endif
#ifdef UNITS_LOGARITHMIC
    std::string logarithmic_units();
#endif
  }
 
}
 
#endif // PUQ_LISTS_H
