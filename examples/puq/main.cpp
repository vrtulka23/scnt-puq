#include <iostream>
#include <iomanip>
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

void display_prefixes() {
  std::cout << std::endl;
  std::cout << "Prefixes:" << std::endl << std::endl;
  std::cout << std::setfill(' ') << std::setw(7)  << std::left << "Symbol";
  std::cout << std::setfill(' ') << std::setw(6)  << std::left << "Name";
  std::cout << std::setfill(' ') << std::setw(10) << std::left << "Magnitude";
  std::cout << std::endl;
  std::cout << std::setfill('-') << std::setw(7)  << std::right << " ";
  std::cout << std::setfill('-') << std::setw(6)  << std::right << " ";
  std::cout << std::setfill('-') << std::setw(10) << std::right << " ";
  std::cout << std::endl;
  for (auto prefix: UnitPrefixList) {
    std::cout << std::setfill(' ') << std::setw(7)  << std::left << prefix.symbol;
    std::cout << std::setfill(' ') << std::setw(6)  << std::left << prefix.name;
    std::cout << std::setfill(' ') << std::setw(10) << std::left;
#if defined(MAGNITUDE_ERRORS) || defined(MAGNITUDE_ARRAYS)
    std::cout << prefix.magnitude.to_string();
#else
    std::cout << prefix.magnitude;
#endif
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_base_units() {
  std::cout << std::endl;
  std::cout << "Base units:" << std::endl << std::endl;
  std::cout << std::setfill(' ') << std::setw(7)  << std::left << "Symbol";
  std::cout << std::setfill(' ') << std::setw(8)  << std::left << "Name";
  std::cout << std::endl;
  std::cout << std::setfill('-') << std::setw(7)  << std::right << " ";
  std::cout << std::setfill('-') << std::setw(8)  << std::right << " ";
  std::cout << std::endl;
  for (size_t i=0; i<NUM_BASEDIM; i++) {
    auto unit = UnitList[i];
    std::cout << std::setfill(' ') << std::setw(7)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << unit.name;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_derived_units() {
  std::cout << std::endl;
  std::cout << "Derived units:" << std::endl << std::endl;
  std::cout << std::setfill(' ') << std::setw(8)  << std::left << "Symbol";
  std::cout << std::setfill(' ') << std::setw(18) << std::left << "Name";
  std::cout << std::setfill(' ') << std::setw(12) << std::left << "Magnitude";
  std::cout << std::setfill(' ') << std::setw(14) << std::left << "Dimension";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Definition";
  std::cout << std::endl;
  std::cout << std::setfill('-') << std::setw(8)  << std::right << " ";
  std::cout << std::setfill('-') << std::setw(18) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(12) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(14) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(20) << std::right << " ";
  std::cout << std::endl;
  for (size_t i=NUM_BASEDIM; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if (unit.symbol[0]=='[')
      continue;
    UnitValue uv(unit.symbol);
    Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(18) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(12) << std::left;
    std::cout << std::setfill(' ') << std::setw(12) << std::left << dim.to_string('n');
    std::cout << std::setfill(' ') << std::setw(14) << std::left << dim.to_string('p');
    std::cout << std::setfill(' ') << std::setw(20) << std::left << unit.definition;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_constants() {
  std::cout << std::endl;
  std::cout << "Derived units:" << std::endl << std::endl;
  std::cout << std::setfill(' ') << std::setw(8)  << std::left << "Symbol";
  std::cout << std::setfill(' ') << std::setw(18) << std::left << "Name";
  std::cout << std::setfill(' ') << std::setw(12) << std::left << "Magnitude";
  std::cout << std::setfill(' ') << std::setw(14) << std::left << "Dimension";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Definition";
  std::cout << std::endl;
  std::cout << std::setfill('-') << std::setw(8)  << std::right << " ";
  std::cout << std::setfill('-') << std::setw(18) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(12) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(14) << std::right << " ";
  std::cout << std::setfill('-') << std::setw(20) << std::right << " ";
  std::cout << std::endl;
  for (size_t i=NUM_BASEDIM; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if (unit.symbol[0]!='[')
      continue;
    UnitValue uv(unit.symbol);
    Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(18) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(12) << std::left << dim.to_string('n');
    std::cout << std::setfill(' ') << std::setw(14) << std::left << dim.to_string('p');
    std::cout << std::setfill(' ') << std::setw(20) << std::left << unit.definition;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

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
    std::cout << "puq -l <list>           display list: prefix/base/derived/const" << std::endl;
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
    convert = input.getCmdOption("-l");
    if (!convert.empty()) {
      if (convert[0]=="prefix")
	display_prefixes();
      else if (convert[0]=="base")
	display_base_units();
      else if (convert[0]=="derived")
	display_derived_units();
      else if (convert[0]=="const")
	display_constants();
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
