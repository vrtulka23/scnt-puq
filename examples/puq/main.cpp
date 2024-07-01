#include <iostream>
#include <exception>
#include "../../src/quantity.h"

class InputParser{
public:
  InputParser (int &argc, char **argv){
    for (int i=1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
  /// @author iain
  const std::vector<std::string> getCmdOption(const std::string &option, const int nstr=1) const {
    std::vector<std::string>::const_iterator itr;
    std::vector<std::string> strs;
    strs.reserve(nstr);
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    for (int i=0;i<nstr;i++) {
      if (itr != this->tokens.end() && ++itr != this->tokens.end()){
	strs.push_back(*itr);
      }
    }
    return strs;
  }
  /// @author iain
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

int main(int argc, char * argv[]) {
  InputParser input(argc, argv);
  if(input.cmdOptionExists("-h") || input.cmdEmpty()){
    std::cout << std::endl;
    std::cout << "Physical Units and Quantities (PUQ)" << std::endl << std::endl;
    std::cout << "Example of use:" << std::endl;
    std::cout << "puq -h                  dislay help" << std::endl;
    std::cout << "puq -v                  dislay current version" << std::endl;
    std::cout << "puq -d <expr>           get unit dimensions" << std::endl;
    std::cout << "puq -b <expr>           get base units" << std::endl;
    std::cout << "puq -c <expr1> <expr2>  get <expr1> in units of <expr2>" << std::endl;
    std::cout << std::endl;
  }
  else if(input.cmdOptionExists("-v")) {
    std::cout << CODE_VERSION << std::endl;
  }
  std::vector<std::string> convert;
  try {
    convert = input.getCmdOption("-d");
    if (!convert.empty()) {
      std::cout << Quantity(convert[0]).value.baseunits.dimensions().to_string('p') << std::endl;
    }
    convert = input.getCmdOption("-b");
    if (!convert.empty()) {
      std::cout << Quantity(convert[0]).value.baseunits.to_string() << std::endl;
    }
    convert = input.getCmdOption("-c",2);
    if (!convert.empty()) {
      std::cout << Quantity(convert[0]).convert(convert[1]).to_string() << std::endl;
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
