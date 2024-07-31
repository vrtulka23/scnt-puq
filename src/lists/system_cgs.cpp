#import "lists.h"

#ifdef UNIT_SYSTEM_CGS

namespace puq {namespace SystemData {

  const UnitListType _CGS = { 
    {"Gal",      Utype::LIN,     0.01,            { 1, 0,-2, 0, 0, 0, 0, 0},  "cm/s2",                  "Gal",               false, {}             },
    {"dyn",      Utype::LIN,     0.01,            { 1, 1,-2, 0, 0, 0, 0, 0},  "g*cm/s2",                "dyne",              true,  {}             },
    {"Ba",       Utype::LIN,     100,             {-1, 1,-2, 0, 0, 0, 0, 0},  "dyn/cm2",                "Barye",             false, {}             },
    {"b",        Utype::LIN,     100,             {-1, 1,-2, 0, 0, 0, 0, 0},  "Ba",                     "Barye",             false, {}             },
    {"erg",      Utype::LIN,     0.0001,          { 2, 1,-2, 0, 0, 0, 0, 0},  "dyn*cm",                 "erg",               false, {}             },
    {"St",       Utype::LIN,     0.0001,          { 2, 0,-1, 0, 0, 0, 0, 0},  "cm2/s",                  "Stokes",            true,  {"c"}          },
    {"P",        Utype::LIN,     100,             {-1, 1,-1, 0, 0, 0, 0, 0},  "g/(cm*s)",               "Poise",             true,  {"c"}          },
    {"Ka",       Utype::LIN,     100,             {-1, 0, 0, 0, 0, 0, 0, 0},  "cm-1",                   "Kayser",            false, {}             },
    {"Pma",      Utype::LIN,     0.0001,          { 2, 0, 0, 0, 0, 0, 0, 0},  "1e-4*m2",                "permeability",      false, {}             },
    {"Rayl",     Utype::LIN,     10000,           {-2, 1,-1, 0, 0, 0, 0, 0},  "g/(cm2*s)",              "Rayl",              false, {}             },
    
    {"radd",     Utype::LIN,     0.01,            { 2, 0,-2, 0, 0, 0, 0, 0},  "100*erg/g",              "radiation dose",    false, {"d","h","k","M"} },

    {"[m_u]",    Utype::CST,     1.66054e-24,     { 0, 1, 0, 0, 0, 0, 0, 0},  "1.660539069e-24*g",      "atom. mass const.", false, {}             },    
    {"[a_0]",    Utype::CST,     5.29177e-11,     { 1, 0, 0, 0, 0, 0, 0, 0},  "5.291772105e-9*cm",      "Bohr radius",       false, {}             },    
    {"[k]",      Utype::CST,     1.38065e-20,     { 2, 1,-2,-1, 0, 0, 0, 0},  "1.380649e-16*erg/K",     "Boltzmann const.",  false, {}             },    
    {"[m_e]",    Utype::CST,     9.10938e-28,     { 0, 1, 0, 0, 0, 0, 0, 0},  "9.10938371e-28*g",       "electron mass",     false, {}             },    
    {"[alpha]",  Utype::CST,     0.00729735,      { 0, 0, 0, 0, 0, 0, 0, 0},  "0.007297352564",         "fine-str. const.",  false, {}             },    
    {"[G]",      Utype::CST,     6.6743e-14,      { 3,-1,-2, 0, 0, 0, 0, 0},  "6.6743e-8*dyn*cm2/g2",   "gravit. const.",    false, {}             },    
    {"[h]",      Utype::CST,     6.62607e-31,     { 2, 1,-1, 0, 0, 0, 0, 0},  "6.62607015e-27*erg*s",   "Planck const.",     false, {}             },    
    {"[hbar]",   Utype::CST,     1.05457e-31,     { 2, 1,-1, 0, 0, 0, 0, 0},  "1.054571817e-27*erg*s",  "reduced Pl. con.",  false, {}             },    
    {"[c]",      Utype::CST,     2.997922458e+08, { 1, 0,-1, 0, 0, 0, 0, 0},  "2.99792458e10*cm/s",     "speed of light",    false, {}             },    
    {"[c_0]",    Utype::CST,     2.997922458e+08, { 0, 0, 0, 0, 0, 0, 0, 0},  "2.99792458e8",           "num. speed of li.", false, {}             },    
  };

  const UnitListType _GAUSS_ESU = {
    {"Fr",       Utype::LIN,         0.001,           {(FRC){3,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "dyn1:2*cm",           "franklin",             false, {}             },
    {"statC",    Utype::LIN,         0.001,           {(FRC){3,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "Fr",                  "Statcoulomb",          false, {}             },
    {"esu",      Utype::LIN,         0.001,           {(FRC){3,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "Fr",                  "elstat. u.o. charge",  false, {}             },
    {"statA",    Utype::LIN,         0.001,           {(FRC){3,2},  (FRC){1,2}, -2, 0, 0, 0, 0, 0},  "Fr/s",                "Statampere",           false, {}             },
    {"statV",    Utype::LIN,         0.1,             {(FRC){1,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "erg/Fr",              "Statvolt",             false, {}             },
    {"statOhm",  Utype::LIN,         100,             {-1,          0,           1, 0, 0, 0, 0, 0},  "s/cm",                "Statohm",              false, {}             },
    {"statF",    Utype::LIN,         0.01,            {1,           0,           0, 0, 0, 0, 0, 0},  "cm",                  "Statfarad",            false, {}             },
    {"statH",    Utype::LIN,         100,             {-1,          0,           2, 0, 0, 0, 0, 0},  "s2/cm",               "Stathenry",            false, {}             },
    
    {"[e]",      Utype::CST,         4.8032e-13,      {(FRC){3,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "4.80320471e-10*Fr",   "elementary charge",    false, {}             },
  };

  const UnitListType _GAUSS_EMU = {
    {"G",        Utype::LIN,         10,              {(FRC){-1,2}, (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "cm-1:2*g1:2*s-1",        "Gauss",             false, {}             },
    {"Oe",       Utype::LIN,         10,              {(FRC){-1,2}, (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "g1:2/(cm1:2*s)",         "Oersted",           false, {}             },
    {"Gb",       Utype::LIN,         0.1,             {(FRC){1,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "Oe*cm",                  "Gilbert",           false, {}             },
    {"Mx",       Utype::LIN,         1e-05,           {(FRC){5,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "dyn1:2*cm2",             "Maxwell",           false, {}             },
    
    {"[mu_B]",   Utype::CST,         9.27401e-26,     {(FRC){5,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "9.274010066e-21*erg/G",  "Bohr magneton",     false, {}             },
  };
    
  const SystemDataType ESU = {
    "Electrostatic CGS units",
    _BASE + _CGS + _GAUSS_ESU + UnitListType({
	{"statT",    Utype::LIN,         1000,          {(FRC){-3,2}, (FRC){1,2},  0, 0, 0, 0, 0, 0},  "cm-3:2*g1:2",      "Stattesla",               false, {}             },
	{"statWb",   Utype::LIN,         0.0001,        {2,           1,           0, 0, 0, 0, 0, 0},  "cm2*g",            "Statweber",               false, {}             },
	
	{"[mu_B]",   Utype::CST,         2.78028e-17,   {(FRC){7,2},  (FRC){1,2}, -2, 0, 0, 0, 0, 0},  "2.780278273e-10*statA*cm2 ",  "Bohr magneton", false, {}             },
      }),
    QuantityListType({
	{"l",       {"cm"                                          }},
	{"m",       {"g"                                           }},    
	{"t",       {"s"                                           }},
	{"I",       {"statA",              "A*0.1/([c_0]*statA)"   }},
	{"Iv",      {"cd"                                          }},
	{"n",       {"mol"                                         }},
	{"the",     {"rad"                                         }},
      })
  };
  
  const SystemDataType GAUSS = {
    "Gaussian CGS units",
    _BASE + _CGS + _GAUSS_ESU + _GAUSS_EMU
  };
  
  const SystemDataType EMU = {
    "Electromagnetic CGS units",
    _BASE + _CGS + _GAUSS_EMU + UnitListType({
      {"Bi",       Utype::LIN,         0.1,           {(FRC){1,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "dyn1:2",              "biot",                 false, {}             },
      {"abA",      Utype::LIN,         0.1,           {(FRC){1,2},  (FRC){1,2}, -1, 0, 0, 0, 0, 0},  "Bi",                  "Abampere",             false, {}             },
      {"abC",      Utype::LIN,         0.1,           {(FRC){1,2},  (FRC){1,2},  0, 0, 0, 0, 0, 0},  "Bi*s",                "Abcoulomb",            false, {}             },
      {"aC",       Utype::LIN,         0.1,           {(FRC){1,2},  (FRC){1,2},  0, 0, 0, 0, 0, 0},  "abC",                 "Abcoulomb",            false, {}             },
      {"abV",      Utype::LIN,         0.001,         {(FRC){3,2},  (FRC){1,2}, -2, 0, 0, 0, 0, 0},  "g1:2*cm3:2*s-2",      "Abvolt",               false, {}             },
      {"abOhm",    Utype::LIN,         0.01,          {1,           0,           1, 0, 0, 0, 0, 0},  "cm*s",                "Abohm",                false, {}             },
      {"abF",      Utype::LIN,         100,           {-1,          0,           2, 0, 0, 0, 0, 0},  "cm-1*s2",             "Abfarad",              false, {}             },
      {"abH",      Utype::LIN,         0.01,          {1,           0,           0, 0, 0, 0, 0, 0},  "cm",                  "Abhenry",              false, {}             },

      {"[e]",      Utype::CST,         1.60218e-21,   {(FRC){1,2},  (FRC){1,2},  0, 0, 0, 0, 0, 0},  "1.602176634e-20*abC", "elementary charge",    false, {}             },
      })
  };
  
}}

#endif // UNIT_SYSTEM_CGS
