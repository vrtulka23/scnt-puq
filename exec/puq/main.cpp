#include <map>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <limits>

#include "main.h"

class InputParser{
public:
  InputParser (int &argc, char **argv){
    for (int i=1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
  const std::deque<std::string> getCmdOption(const std::string &option, const int nstr=1) const {
    std::vector<std::string>::const_iterator itr;
    std::deque<std::string> strs;
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    for (int i=0;i<nstr;i++) {
      if (itr != this->tokens.end() && ++itr != this->tokens.end()){
	strs.push_back(*itr);
      }
    }
    return strs;
  }
  bool cmdOptionExists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option)
      != this->tokens.end();
  }
  bool cmdEmpty() const {
    return this->tokens.size()==0;
  }
private:
  std::vector <std::string> tokens;
};

inline std::string get_expression(std::deque<std::string>& convert) {
  if (convert.size()) {
    std::string expr = convert.front();
    convert.pop_front();
    return expr;
  } else {
    return "";
  }
}

inline puq::SystemDataType* get_system(std::deque<std::string>& convert) {
  for (auto sys: puq::SystemData::SystemMap) {
    if (sys.first==convert.front()) {
      convert.pop_front();
      return sys.second;
    }
  }
  return NULL;
}

inline void change_system(puq::UnitSystem& us, std::deque<std::string>& convert) {
  puq::SystemDataType* system = get_system(convert);
  if (system != NULL)
    us.change(system);
}

inline void convert_units(std::deque<std::string>& convert) {
  puq::SystemDataType* sys1 = get_system(convert);
  std::string expr1 = get_expression(convert);
  puq::SystemDataType* sys2 = get_system(convert);
  std::string expr2 = get_expression(convert);
  std::string quant = get_expression(convert);
  puq::Quantity q;
  if (sys1 == NULL)
    q = puq::Quantity(expr1);
  else
    q = puq::Quantity(expr1, *sys1);
  if (quant=="") {
    if (sys2 == NULL)
      q = q.convert(expr2);
    else 
      q = q.convert(expr2, *sys2);
  } else {
    if (sys2 == NULL)
      q = q.convert(expr2, quant);
    else
      q = q.convert(expr2, *sys2, quant);
  }
  std::cout << q.to_string() << std::endl;
}

int main(int argc, char * argv[]) {
  InputParser input(argc, argv);
  if(input.cmdOptionExists("-h") || input.cmdEmpty()){
    std::cout << std::endl;
    std::cout << "Physical Units and Quantities (PUQ)" << std::endl << std::endl;
    std::cout << "Example of use:" << std::endl;
    std::cout << "puq -h                          dislay help" << std::endl;
    std::cout << "puq -v                          dislay current version" << std::endl;
    std::cout << "puq -i [s] <e>                  get information about an expression <e> in a unit system [s]" << std::endl;
    std::cout << "puq -c [s1] <e1> [s2] <e2> [q]  convert expression <e1> in a unit system [s1] into expression <e2> in a system [s2] as a quantity [q]" << std::endl;
    std::cout << "puq -l [s] <l>                  display list <l>=prefix/base/deriv/log/temp/const/quant in a unit system [s], or all available unit systems <l>=sys" << std::endl;
    std::cout << std::endl;
  }
  else if(input.cmdOptionExists("-v")) {
    std::cout << CODE_VERSION << std::endl;
  }
  try {
    std::deque<std::string> convert;
    puq::UnitSystem us(puq::SystemData::SI);
    convert = input.getCmdOption("-i",2);
    if (!convert.empty()) {
      change_system(us, convert);
      display_info(convert[0]);
    }
    convert = input.getCmdOption("-c",5);
    if (!convert.empty()) {
      convert_units(convert);
    }
    convert = input.getCmdOption("-l",2);
    if (!convert.empty()) {
      change_system(us, convert);
      if (convert[0]=="prefix")
	display_prefixes();
      else if (convert[0]=="base")
	display_base_units();
      else if (convert[0]=="deriv")
	display_derived_units();
#ifdef UNITS_LOGARITHMIC
      else if (convert[0]=="log")
	display_logarithmic_units();
#endif
#ifdef UNITS_TEMPERATURES
      else if (convert[0]=="temp")
	display_temperature_units();
#endif
      else if (convert[0]=="const")
	display_constants();
      else if (convert[0]=="quant")
	display_quantities();
      else if (convert[0]=="sys")
	display_unit_systems();
      else {
	display_lists(convert);
      }
    }
    else if (input.cmdOptionExists("-l")) {
      std::deque<std::string> convert;
      display_lists(convert);
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
