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

void table_header(std::string title, std::vector<std::string> header, std::vector<int> width) {
  std::cout << std::endl;
  std::cout << title << std::endl << std::endl;
  for (size_t i=0; i<header.size(); i++) {
    std::cout << std::setfill(' ') << std::setw(width[i])  << std::left << header[i];
  }
  std::cout << std::endl;
  for (size_t i=0; i<header.size(); i++) {
    std::cout << std::setfill('-') << std::setw(width[i])  << std::right << "  ";
  }
  std::cout << std::endl;  
}

void display_prefixes() {
  table_header("Prefixes:", {"Symbol","Name","Magnitude"}, {8,7,11});
  for (auto prefix: UnitPrefixList) {
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << prefix.symbol;
    std::cout << std::setfill(' ') << std::setw(7)  << std::left << prefix.name;
    std::cout << std::setfill(' ') << std::setw(11) << std::left;
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
  table_header("Base units:", {"Symbol","Name"}, {8,9});
  for (size_t i=0; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if ((unit.utype & Utype::BAS)!=Utype::BAS) continue;
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.name;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_linear_units() {
  table_header("Linear units:", {"Symbol","Name","Magnitude","Dimension","Definition"}, {9,19,13,15,21});
  for (size_t i=0; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if ((unit.utype & Utype::LIN)!=Utype::LIN) continue;
    UnitValue uv(unit.symbol);
    Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(13) << std::left << dim.to_string(Dformat::NUM);
    std::cout << std::setfill(' ') << std::setw(15) << std::left << dim.to_string(Dformat::PHYS);
    std::cout << std::setfill(' ') << std::setw(21) << std::left << unit.definition;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_constants() {
  table_header("Constants:", {"Symbol","Name","Magnitude","Dimension","Definition"}, {9,19,13,15,21});
  for (size_t i=0; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if ((unit.utype & Utype::CST)!=Utype::CST) continue;
    UnitValue uv(unit.symbol);
    Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(13) << std::left << dim.to_string(Dformat::NUM);
    std::cout << std::setfill(' ') << std::setw(15) << std::left << dim.to_string(Dformat::PHYS);
    std::cout << std::setfill(' ') << std::setw(21) << std::left << unit.definition;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_temperature_units() {
  table_header("Temperatures:", {"Symbol","Name"}, {9,19});
  for (size_t i=0; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if ((unit.utype & Utype::TMP)!=Utype::TMP) continue;
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_logarithmic_units() {
  table_header("Logarithmic units:", {"Symbol","Name"}, {9,19});
  for (size_t i=0; i<UnitList.size(); i++) {
    auto unit = UnitList[i];
    if ((unit.utype & Utype::LOG)!=Utype::LOG) continue;
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
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
    Dformat format = Dformat::NUM|Dformat::PHYS;
    convert = input.getCmdOption("-si");
    if (!convert.empty()) {
      format = format | Dformat::SI;
    }
    convert = input.getCmdOption("-cgs");
    if (!convert.empty()) {
      format = format | Dformat::CGS;
    }
    convert = input.getCmdOption("-d");
    if (!convert.empty()) {
      Dimensions dim = Quantity(convert[0]).value.baseunits.dimensions();
      std::cout << dim.to_string(format) << std::endl;
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
      else if (convert[0]=="lin")
	display_linear_units();
      else if (convert[0]=="log")
	display_logarithmic_units();
      else if (convert[0]=="temp")
	display_temperature_units();
      else if (convert[0]=="const")
	display_constants();
    }
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
