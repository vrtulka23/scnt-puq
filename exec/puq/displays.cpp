#include "main.h"
#include "../../src/lists.h"
#include "../../src/util/data_table.h"

void display_info(std::string expr) {
  puq::UnitValue uv = puq::Quantity(expr).value;
  puq::BaseUnits bus = uv.baseunits;
  puq::Dimensions dim = bus.dimensions();
  puq::Dimensions dim_m = bus.dimensions();
  dim_m.numerical *= uv.magnitude;
  std::cout << std::endl << "Expression:  " << expr << std::endl << std::endl;
  std::cout << "Unit system: " << puq::UnitSystem::Data->SystemAbbrev << " (" << puq::UnitSystem::Data->SystemName << ")" << std::endl;
  std::cout << "Magnitude:   " << puq::nostd::to_string(uv.magnitude) << std::endl;
  std::cout << "Base units:  " << puq::nostd::to_string(uv.baseunits) << std::endl;
  std::stringstream ss; bool display = false;
  for (auto unit: puq::UnitSystem::Data->DimensionMap) {
    if (puq::Dimensions(1,unit.second.dimensions) != dim) continue;
    ss << (display?", ":"") << unit.first;
    display = true;
  }
  if (display) {
    std::cout << std::endl;
    std::cout << "Conversions: " << ss.str() << std::endl;
  }
  ss.str(std::string()); display = false;
  for (auto quant: puq::UnitSystem::Data->QuantityList) {
    if (puq::BaseUnits(quant.second.definition).dimensions() != dim) continue;
    ss << (display?", ":"") << quant.first;
    display = true;
  }
  if (display) {
    std::cout << std::endl;
    std::cout << "Quantities:  " << ss.str() << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Dimensions:" << std::endl << std::endl;
  puq::DataTable tab({{"Base",6},{"Num*Mag",25},{"Numerical",25},{"Physical",25}});
  tab.append({"MGS", dim_m.to_string(puq::Dformat::NUM), dim.to_string(puq::Dformat::NUM), dim.to_string(puq::Dformat::PHYS)});
  tab.append({
      "MKS",
      dim_m.to_string(puq::Dformat::NUM|puq::Dformat::MKS),
      dim.to_string(puq::Dformat::NUM|puq::Dformat::MKS),
      dim.to_string(puq::Dformat::PHYS|puq::Dformat::MKS)
    });
  tab.append({
      "CGS",
      dim_m.to_string(puq::Dformat::NUM|puq::Dformat::CGS),
      dim.to_string(puq::Dformat::NUM|puq::Dformat::CGS),
      dim.to_string(puq::Dformat::PHYS|puq::Dformat::CGS)
    });
  std::cout << tab.to_string();
  std::cout << std::endl;
  if (bus.size() > 0) {
    std::cout << "Base units:" << std::endl << std::endl;
    puq::DataTable tab({{"Prefix",8},{"Symbol",8},{"Exponent",10},{"Name",30},{"Definition",30},{"Dimensions MGS",22},{"Allowed prefixes",22}});
    for (auto unit: puq::UnitSystem::Data->UnitList) {
      for (auto bu: bus) {
	if (bu.unit!=unit.first)
	  continue;
	puq::BaseUnits bu_unit({bu});
	tab.append({
	    bu.prefix,
	    bu.unit,
	    ((puq::nostd::to_string(bu.exponent)=="") ? "1" : puq::nostd::to_string(bu.exponent)),
	    unit.second.name,
	    unit.second.definition,
	    bu_unit.dimensions().to_string(),
	    puq::nostd::to_string(unit.second.use_prefixes, unit.second.allowed_prefixes)
	  });
      }
    }
    for (auto quant: puq::UnitSystem::Data->QuantityList) {
      for (auto bu: bus) {
	if (bu.unit!=SYMBOL_QUANTITY_START+quant.first+SYMBOL_QUANTITY_END)
	  continue;
	puq::BaseUnits bu_unit({bu});
	tab.append({
	    bu.prefix,
	    bu.unit,
	    ((puq::nostd::to_string(bu.exponent)=="") ? "1" : puq::nostd::to_string(bu.exponent)),
	    puq::QuantityNames.at(quant.first),
	    quant.second.definition,
	    bu_unit.dimensions().to_string(),
	    ""
	  });
      }
    }
    std::cout << tab.to_string();
  }
  std::cout << std::endl;
}

void display_lists(std::deque<std::string>& convert) {
  std::stringstream ss;
  ss << std::endl;
  if (convert.size()>0) 
    ss << "List '" << convert[0] << "' does not exist." << std::endl << std::endl;
  ss << "Available lists:" << std::endl << std::endl;
  ss << "prefix  unit prefixes"         << std::endl;
  ss << "base    base units"            << std::endl;
  ss << "deriv   derived units"         << std::endl;
  ss << "log     logarithmic units"     << std::endl;
  ss << "temp    temperature units"     << std::endl;
  ss << "const   constants"             << std::endl;
  ss << "quant   quantities"            << std::endl;
  ss << "sys     unit systems"          << std::endl;
  throw std::runtime_error(ss.str());
}
