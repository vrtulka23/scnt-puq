#import "lists.h"

#ifdef UNIT_SYSTEM_CGS

namespace puq {namespace SystemData {

  const UnitListType _CGS_UNITS = { 
    {"Gal",      Utype::LIN,     "cm/s2",                  "Gal",               false, {}             },
    {"dyn",      Utype::LIN,     "g*cm/s2",                "dyne",              true,  {}             },
    {"Ba",       Utype::LIN,     "dyn/cm2",                "Barye",             false, {}             },
    {"b",        Utype::LIN,     "Ba",                     "Barye",             false, {}             },
    {"erg",      Utype::LIN,     "dyn*cm",                 "erg",               false, {}             },
    {"St",       Utype::LIN,     "cm2/s",                  "Stokes",            true,  {"c"}          },
    {"P",        Utype::LIN,     "g/(cm*s)",               "Poise",             true,  {"c"}          },
    {"Ka",       Utype::LIN,     "cm-1",                   "Kayser",            false, {}             },
    {"Pma",      Utype::LIN,     "1e-4*m2",                "permeability",      false, {}             },
    {"Rayl",     Utype::LIN,     "g/(cm2*s)",              "Rayl",              false, {}             },
    
    {"radd",     Utype::LIN,     "100*erg/g",              "radiation dose",    false, {"d","h","k","M"} },

    {"[m_u]",    Utype::CST,     "1.660539069e-24*g",      "atom. mass const.", false, {}             },    
    {"[a_0]",    Utype::CST,     "5.291772105e-9*cm",      "Bohr radius",       false, {}             },    
    {"[k]",      Utype::CST,     "1.380649e-16*erg/K",     "Boltzmann const.",  false, {}             },    
    {"[m_e]",    Utype::CST,     "9.10938371e-28*g",       "electron mass",     false, {}             },    
    {"[alpha]",  Utype::CST,     "0.007297352564",         "fine-str. const.",  false, {}             },    
    {"[G]",      Utype::CST,     "6.6743e-8*dyn*cm2/g2",   "gravit. const.",    false, {}             },    
    {"[h]",      Utype::CST,     "6.62607015e-27*erg*s",   "Planck const.",     false, {}             },    
    {"[hbar]",   Utype::CST,     "1.054571817e-27*erg*s",  "reduced Pl. con.",  false, {}             },    
    {"[c]",      Utype::CST,     "2.99792458e10*cm/s",     "speed of light",    false, {}             },    
    {"[c_0]",    Utype::CST,     "2.99792458e8",           "num. speed of li.", false, {}             },    
  };

  const UnitListType _GAUSS_ESU_UNITS = {
    {"Fr",       Utype::LIN,     "dyn1:2*cm",           "franklin",             false, {}             },
    {"statC",    Utype::LIN,     "Fr",                  "Statcoulomb",          false, {}             },
    {"esu",      Utype::LIN,     "Fr",                  "elstat. u.o. charge",  false, {}             },
    {"statA",    Utype::LIN,     "Fr/s",                "Statampere",           false, {}             },
    {"statV",    Utype::LIN,     "erg/Fr",              "Statvolt",             false, {}             },
    {"statOhm",  Utype::LIN,     "s/cm",                "Statohm",              false, {}             },
    {"statF",    Utype::LIN,     "cm",                  "Statfarad",            false, {}             },
    {"statH",    Utype::LIN,     "s2/cm",               "Stathenry",            false, {}             },
    
    {"[e]",      Utype::CST,     "4.80320471e-10*Fr",   "elementary charge",    false, {}             },
  };

  const QuantityListType _GAUSS_ESU_QUANTITIES = {
    {"l",       {"cm"                                }},
    {"m",       {"g"                                 }},    
    {"t",       {"s"                                 }},
    {"I",       {"statA",    "A*0.1/([c_0]*statA)"   }},
    {"Iv",      {"cd"                                }},
    {"n",       {"mol"                               }},
    {"the",     {"rad"                               }},
  };

  const UnitListType _GAUSS_EMU_UNITS = {
    {"G",        Utype::LIN,    "cm-1:2*g1:2*s-1",        "Gauss",             false, {}             },
    {"Oe",       Utype::LIN,    "g1:2/(cm1:2*s)",         "Oersted",           false, {}             },
    {"Gb",       Utype::LIN,    "Oe*cm",                  "Gilbert",           false, {}             },
    {"Mx",       Utype::LIN,    "dyn1:2*cm2",             "Maxwell",           false, {}             },
    
    {"[mu_B]",   Utype::CST,    "9.274010066e-21*erg/G",  "Bohr magneton",     false, {}             },
  };
    
  SystemDataType ESU = {
    "ESU", "Electrostatic CGS units", 
    _BASE_UNITS + _CGS_UNITS + _GAUSS_ESU_UNITS + UnitListType({
	{"statT",    Utype::LIN,     "cm-3:2*g1:2",      "Stattesla",               false, {}             },
	{"statWb",   Utype::LIN,     "cm2*g",            "Statweber",               false, {}             },
	
	{"[mu_B]",   Utype::CST,     "2.780278273e-10*statA*cm2 ",  "Bohr magneton", false, {}             },
      }),
    _GAUSS_ESU_QUANTITIES + QuantityListType({
	{"B",     {"statT",    "kg/(s2*A)*[c_0]/(1e4*statT)"}},
      }),
    DimensionMapType({
#include "dmap_ESU.h"
      })
  };
  
  SystemDataType GAUSS = {
    "GAUSS", "Gaussian CGS units", 
    _BASE_UNITS + _CGS_UNITS + _GAUSS_ESU_UNITS + _GAUSS_EMU_UNITS,
    _GAUSS_ESU_QUANTITIES,
    DimensionMapType({
#include "dmap_GAUSS.h"
      })
  };
  
  SystemDataType EMU = {
    "EMU", "Electromagnetic CGS units",
    _BASE_UNITS + _CGS_UNITS + _GAUSS_EMU_UNITS + UnitListType({
      {"Bi",       Utype::LIN,     "dyn1:2",              "biot",                 false, {}             },
      {"abA",      Utype::LIN,     "Bi",                  "Abampere",             false, {}             },
      {"abC",      Utype::LIN,     "Bi*s",                "Abcoulomb",            false, {}             },
      {"aC",       Utype::LIN,     "abC",                 "Abcoulomb",            false, {}             },
      {"abV",      Utype::LIN,     "g1:2*cm3:2*s-2",      "Abvolt",               false, {}             },
      {"abOhm",    Utype::LIN,     "cm*s",                "Abohm",                false, {}             },
      {"abF",      Utype::LIN,     "cm-1*s2",             "Abfarad",              false, {}             },
      {"abH",      Utype::LIN,     "cm",                  "Abhenry",              false, {}             },

      {"[e]",      Utype::CST,     "1.602176634e-20*abC", "elementary charge",    false, {}             },
      }),
    QuantityListType({
      }),
    DimensionMapType({
#include "dmap_EMU.h"
      })
  };
  
}}

#endif // UNIT_SYSTEM_CGS
