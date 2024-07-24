#include <map>
#include <deque>

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

typedef const puq::SystemDataType* SystemPtr;
std::map<std::string, SystemPtr> systems = {
  {"SI",    &puq::SystemData::SI},
  {"ESU",   &puq::SystemData::ESU},
  {"GAUSS", &puq::SystemData::GAUSS},
  {"EMU",   &puq::SystemData::EMU},
  {"IU",    &puq::SystemData::IU},
  {"USCU",  &puq::SystemData::USCU},
  {"AU",    &puq::SystemData::AU},
};

inline std::string get_expression(std::deque<std::string>& convert) {
  std::string expr = convert.front();
  convert.pop_front();
  return expr;
}

inline SystemPtr get_system(std::deque<std::string>& convert) {
  for (auto sys: systems) {
    if (sys.first==convert.front()) {
      convert.pop_front();
      return sys.second;
    }
  }
  return NULL;
}

inline void change_system(puq::UnitSystem& us, std::deque<std::string>& convert) {
  SystemPtr system = get_system(convert);
  if (system != NULL)
    us.change(system);
}

int main(int argc, char * argv[]) {
  InputParser input(argc, argv);
  if(input.cmdOptionExists("-h") || input.cmdEmpty()){
    std::cout << std::endl;
    std::cout << "Physical Units and Quantities (PUQ)" << std::endl << std::endl;
    std::cout << "Example of use:" << std::endl;
    std::cout << "puq -h                              dislay help" << std::endl;
    std::cout << "puq -v                              dislay current version" << std::endl;
    //std::cout << "puq -s                              list available unit systems" << std::endl;
    std::cout << "puq -c [sys] <expr1> [sys] <expr2>  get <expr1> in units of <expr2>" << std::endl;
    std::cout << "puq -l [sys] <list>                 display list: prefix/base/lin/log/temp/const/sys" << std::endl;
    std::cout << "puq -i [sys] <expr>                 get information about an unit" << std::endl;
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
      std::cout << "unit: " << convert[0] << std::endl;
      display_info(convert[0]);
    }
    convert = input.getCmdOption("-c",4);
    if (!convert.empty()) {
      SystemPtr sys1 = get_system(convert);
      std::string expr1 = get_expression(convert);
      SystemPtr sys2 = get_system(convert);
      std::string expr2 = get_expression(convert);
      puq::Quantity q;
      if (sys1 == NULL)
	q = puq::Quantity(expr1);
      else
	q = puq::Quantity(expr1, *sys1);
      if (sys2 == NULL)
	q = q.convert(expr2);
      else
	q = q.convert(expr2, *sys2);
      std::cout << q.to_string() << std::endl;
    }
    convert = input.getCmdOption("-l",2);
    if (!convert.empty()) {
      change_system(us, convert);
      if (convert[0]=="prefix")
	display_prefixes();
      else if (convert[0]=="base")
	display_base_units();
      else if (convert[0]=="lin")
	display_linear_units();
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
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
