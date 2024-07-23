#include <iostream>
#include <iomanip>
#include <exception>

#include "../../src/quantity.h"
#include "../../src/nostd.h"
#include "../../src/lists/lists.h"

class InputParser{
public:
  InputParser (int &argc, char **argv){
    for (int i=1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
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
  for (auto prefix: puq::UnitPrefixList) {
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
  table_header("Base units:", {"Symbol","Name","Allowed prefixes"}, {8,19,22});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    if ((unit.utype & puq::Utype::BAS)!=puq::Utype::BAS) continue;
    std::cout << std::setfill(' ') << std::setw(8)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(22) << std::left << puq::nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_linear_units() {
  table_header("Linear units:", {"Symbol","Name","Magnitude","Dimension","Definition","Allowed prefixes"}, {9,22,13,30,25,22});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    if ((unit.utype & puq::Utype::LIN)!=puq::Utype::LIN) continue;
    puq::UnitValue uv(unit.symbol);
    puq::Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(22) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(13) << std::left << dim.to_string(puq::Dformat::NUM);
    std::cout << std::setfill(' ') << std::setw(30) << std::left << dim.to_string(puq::Dformat::PHYS);
    std::cout << std::setfill(' ') << std::setw(25) << std::left << unit.definition;
    std::cout << std::setfill(' ') << std::setw(22) << std::left << puq::nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

void display_constants() {
  table_header("Constants:", {"Symbol","Name","Magnitude","Dimension","Definition"}, {9,19,13,15,25});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    if ((unit.utype & puq::Utype::CST)!=puq::Utype::CST) continue;
    puq::UnitValue uv(unit.symbol);
    puq::Dimensions dim = uv.baseunits.dimensions();
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(13) << std::left << dim.to_string(puq::Dformat::NUM);
    std::cout << std::setfill(' ') << std::setw(15) << std::left << dim.to_string(puq::Dformat::PHYS);
    std::cout << std::setfill(' ') << std::setw(25) << std::left << unit.definition;
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}

#ifdef UNITS_TEMPERATURES
void display_temperature_units() {
  table_header("Temperatures:", {"Symbol","Name","Allowed prefixes"}, {9,19,22});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    if ((unit.utype & puq::Utype::TMP)!=puq::Utype::TMP) continue;
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(22) << std::left << puq::nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}
#endif

#ifdef UNITS_LOGARITHMIC
void display_logarithmic_units() {
  table_header("Logarithmic units:", {"Symbol","Name","Allowed prefixes"}, {9,19,22});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    if ((unit.utype & puq::Utype::LOG)!=puq::Utype::LOG) continue;
    std::cout << std::setfill(' ') << std::setw(9)  << std::left << unit.symbol;
    std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
    std::cout << std::setfill(' ') << std::setw(22) << std::left << puq::nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
    std::cout << std::scientific << std::endl;
  }
  std::cout << std::endl;
}
#endif

void display_info(std::string expr) {
  puq::UnitValue uv = puq::Quantity(expr).value;
  puq::BaseUnits bus = uv.baseunits;
  puq::Dimensions dim = bus.dimensions();
  std::cout << std::endl << "Expression information" << std::endl << std::endl;
  std::cout << "Magnitude:   " << puq::nostd::to_string(uv.magnitude) << std::endl;
  std::cout << "Base units:  " << puq::nostd::to_string(uv.baseunits) << std::endl;
  std::cout << std::endl;
  std::cout << "Dimensions:  MGS  " << dim.to_string() << std::endl;
  std::cout << "             SI   " << dim.to_string(puq::Dformat::NUM|puq::Dformat::PHYS|puq::Dformat::SI) << std::endl;
  std::cout << "             CGS  " << dim.to_string(puq::Dformat::NUM|puq::Dformat::PHYS|puq::Dformat::CGS) << std::endl;
  std::stringstream ss; bool conv = false;
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    if (puq::Dimensions(1,unit.dimensions) != dim) continue;
    
    ss << (conv?", ":"") << unit.symbol;
    conv = true;
  }
  if (conv) {
    std::cout << std::endl;
    std::cout << "Conversions: " << ss.str() << std::endl;
  }
  table_header("Components:",
	       {"Prefix","Symbol","Exponent","Name","Definition","Dimensions MGS","Allowed prefixes"},
	       {8,8,10,19,21,22,22});
  for (size_t i=0; i<puq::UnitSystem::Data->UnitList.size(); i++) {
    auto unit = (puq::UnitSystem::Data->UnitList)[i];
    for (auto bu: bus) {
      if (bu.unit!=unit.symbol)
	continue;
      puq::BaseUnits bu_unit({bu});
      std::cout << std::setfill(' ') << std::setw(8) << std::left << bu.prefix;
      std::cout << std::setfill(' ') << std::setw(8) << std::left << bu.unit;
      std::cout << std::setfill(' ') << std::setw(10) << std::left << ((bu.exponent.to_string()=="") ? "1" : bu.exponent.to_string());
      std::cout << std::setfill(' ') << std::setw(19) << std::left << unit.name;
      std::cout << std::setfill(' ') << std::setw(21) << std::left << unit.definition;
      std::cout << std::setfill(' ') << std::setw(22) << std::left << bu_unit.dimensions().to_string();
      std::cout << std::setfill(' ') << std::setw(22) << std::left << puq::nostd::to_string(unit.use_prefixes, unit.allowed_prefixes);
      std::cout << std::scientific << std::endl;
    }
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
    std::cout << "puq -c <expr1> <expr2>  get <expr1> in units of <expr2>" << std::endl;
    std::cout << "puq -l <list>           display list: prefix/base/lin/log/temp/const" << std::endl;
    std::cout << "puq -i <expr>           get information about an unit" << std::endl;
    std::cout << "puq -si/-esu/-emu/-gauss/-au/-iu/-uscu    different unit types" << std::endl;
    std::cout << std::endl;
  }
  else if(input.cmdOptionExists("-v")) {
    std::cout << CODE_VERSION << std::endl;
  }
  const puq::SystemDataType* stype = &puq::SystemData::SI;
  std::vector<std::string> convert;
  try {
    if (input.cmdOptionExists("-esu")) {
      stype = &puq::SystemData::ESU;
    }
    else if (input.cmdOptionExists("-gauss")) {
      stype = &puq::SystemData::GAUSS;
    }
    else if (input.cmdOptionExists("-emu")) {
      stype = &puq::SystemData::EMU;
    }
    else if (input.cmdOptionExists("-iu")) {
      stype = &puq::SystemData::IU;
    }
    else if (input.cmdOptionExists("-uscu")) {
      stype = &puq::SystemData::USCU;
    }
    else if (input.cmdOptionExists("-au")) {
      stype = &puq::SystemData::AU;
    } else {
      stype = &puq::SystemData::SI;
    }
    puq::UnitSystem us(stype);
    convert = input.getCmdOption("-i");
    if (!convert.empty()) {
      display_info(convert[0]);
    }
    convert = input.getCmdOption("-c",2);
    if (!convert.empty()) {
      std::cout << puq::Quantity(convert[0]).convert(convert[1]).to_string() << std::endl;
    }
    convert = input.getCmdOption("-l");
    if (!convert.empty()) {
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
