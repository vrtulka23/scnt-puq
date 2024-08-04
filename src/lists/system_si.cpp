#import "lists.h"

namespace puq {
  namespace SystemData {
    
    const SystemDataType SI = {
      "SI", "International System of Units", 
      _BASE + UnitListType({
	  // units of length
	  {"au",       Utype::LIN,      1.49597870e11,   { 1, 0, 0, 0, 0, 0, 0, 0},  "149597.870691*Mm",       "astr. unit",        false, {}             },
	  {"AU",       Utype::LIN,      1.49597870e11,   { 1, 0, 0, 0, 0, 0, 0, 0},  "au",                     "astr. unit",        false, {}             },
	  {"ly",       Utype::LIN,      9.460730e15,     { 1, 0, 0, 0, 0, 0, 0, 0},  "[c]*yr_j",               "light-year",        true,  {"k","M","G"}  },
	  {"pc",       Utype::LIN,      3.0857e16,       { 1, 0, 0, 0, 0, 0, 0, 0},  "3.0857e16*m",            "parsec",            true,  {"k","M","G","T"}  },
	  {"Ao",       Utype::LIN,      1e-10,           { 1, 0, 0, 0, 0, 0, 0, 0},  "1e-10*m",                "Angstrom",          true,  {"m","k"}      },
      
	  // units of mass	      
	  {"u",        Utype::LIN,      1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "g/[N_0]",                "atomic mass unit",  false, {}             },
	  {"amu",      Utype::LIN,      1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "u",                      "atomic mass unit",  false, {}             },
	  {"Da",       Utype::LIN,      1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "u",                      "Dalton",            false, {}             },
	  {"t",        Utype::LIN,      1e6,             { 0, 1, 0, 0, 0, 0, 0, 0},  "1e3*kg",                 "tonne",             true,  {"k","m","G"}  },
	  
	  // units of time	           
	  {"min",      Utype::LIN,      6.0e1,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*s",                   "minute",            false, {}             },
	  {"h",        Utype::LIN,      3.6e3,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*min",                 "hour",              false, {}             },
	  {"day",      Utype::LIN,      8.64e4,          { 0, 0, 1, 0, 0, 0, 0, 0},  "24*h",                   "day",               false, {}             },
	  {"yr_t",     Utype::LIN,      3.1556925e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.24219*day",          "tropical year",     true,  {"k","m","G"}  },
	  {"yr_j",     Utype::LIN,      3.1557600e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.25*day",             "Julian year",       true,  {"k","m","G"}  },
	  {"yr_g",     Utype::LIN,      3.1556952e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.2425*day",           "Gregorian year",    true,  {"k","m","G"}  },
	  {"yr",       Utype::LIN,      3.155760e7,      { 0, 0, 1, 0, 0, 0, 0, 0},  "yr_j",                   "year",              true,  {"k","m","G"}  },
	  
	  // units of temperature	
	  {"degR",     UT_LIN_TMP,      5./9.,           { 0, 0, 0, 1, 0, 0, 0, 0},  "5/9*K",                  "degree Rankine",    false, {}             },
#ifdef UNITS_TEMPERATURES
	  {"Cel",      Utype::TMP,      1,               { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "degree Celsius",    false, {}             },
	  {"degF",     Utype::TMP,      1,               { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "degree Fahrenheit", false, {}             },
#endif
	  
	  // angular units	      
	  {"deg",      Utype::LIN,      1.7453292e-2,    { 0, 0, 0, 0, 0, 0, 0, 1},  "2*[pi]*rad/360",         "angle degree",      false, {}             },
	  {"'",        Utype::LIN,      2.908882e-4,     { 0, 0, 0, 0, 0, 0, 0, 1},  "deg/60",                 "angle minute",      false, {}             },
	  {"''",       Utype::LIN,      4.848137e-6,     { 0, 0, 0, 0, 0, 0, 0, 1},  "'/60",                   "angle second",      false, {}             },
	  
	  // units of surface	           
	  {"ar",       Utype::LIN,      1.0e2,           { 2, 0, 0, 0, 0, 0, 0, 0},  "100*m2",                 "are",               true,  {"c","d","da","h"} },
	  
	  // units of volume	           
	  {"l",        Utype::LIN,      1e-3,            { 3, 0, 0, 0, 0, 0, 0, 0},  "dm3",                    "liter",             true,  {}             },
	  {"L",        Utype::LIN,      1e-3,            { 3, 0, 0, 0, 0, 0, 0, 0},  "l",                      "liter",             true,  {}             },
	  
	  // units of energy	           
	  {"J",        Utype::LIN,      1.0e3,           { 2, 1,-2, 0, 0, 0, 0, 0},  "N*m",                    "Joule",             true,  {}             },
	  {"eV",       Utype::LIN,      1.602176634e-16, { 2, 1,-2, 0, 0, 0, 0, 0},  "[e]*V",                  "electronvolt",      true,  {}             },
	  {"erg",      Utype::LIN,      1.0e-4,          { 2, 1,-2, 0, 0, 0, 0, 0},  "dyn*cm",                 "erg",               false, {}             },
	  {"cal",      Utype::LIN,      4184.0,          { 2, 1,-2, 0, 0, 0, 0, 0},  "4.184*J",                "calorie",           true,  {"k","M"}      },
	  {"Cal",      Utype::LIN,      4.184e6,         { 2, 1,-2, 0, 0, 0, 0, 0},  "kcal",                   "Calorie",           false, {}             },
	  {"Ha",       Utype::LIN,      4.35974472e-15,  { 2, 1,-2, 0, 0, 0, 0, 0},  "4.3597447222071e-18*J",  "Hartree",           true,  {"k","M"}      },
	  {"E_h",      Utype::LIN,      4.35974472e-15,  { 2, 1,-2, 0, 0, 0, 0, 0},  "Ha",                     "Hartree",           true,  {"k","M"}      },
	  
	  // units of pressure	           
	  {"Pa",       Utype::LIN,      1.0e3,           {-1, 1,-2, 0, 0, 0, 0, 0},  "N/m2",                   "Pascal",            true,  {}             },
	  {"atm",      Utype::LIN,      1.013250e8,      {-1, 1,-2, 0, 0, 0, 0, 0},  "101325*Pa",              "atm. pressure",     false, {}             },
	  {"bar",      Utype::LIN,      1e8,             {-1, 1,-2, 0, 0, 0, 0, 0},  "100*kPa",                "bar",               true,  {"M","k","d","c","m"}},
	  {"Ba",       Utype::LIN,      1e2,             {-1, 1,-2, 0, 0, 0, 0, 0},  "0.1*Pa",                 "Barye",             false, {}             },
	  
	  // units of force	           
	  {"N",        Utype::LIN,      1.0e3,           { 1, 1,-2, 0, 0, 0, 0, 0},  "kg*m/s2",                "Newton",            true,  {}             },
	  {"dyn",      Utype::LIN,      1.0e-2,          { 1, 1,-2, 0, 0, 0, 0, 0},  "g*cm/s2",                "dyne",              true,  {}             },
	  
	  // units of energy absorption    
	  {"Gy",       Utype::LIN,      1.0e0,           { 2, 0,-2, 0, 0, 0, 0, 0},  "J/kg",                   "Gray",              false, {}             },
	  {"Sv",       Utype::LIN,      1.0e0,           { 2, 0,-2, 0, 0, 0, 0, 0},  "J/kg",                   "Sivert",            false, {}             },
	  
	  // units of magnetic flux density
	  {"T",        Utype::LIN,      1.0e3,           { 0, 1,-2, 0,-1, 0, 0, 0},  "Wb/m2",                  "Tesla",             true,  {}             },
	  {"G",        Utype::LIN,      1.0e-1,          { 0, 1,-2, 0,-1, 0, 0, 0},  "1e-4*T",                 "Gauss",             true,  {}             },
	  
	  // units of frequency	           
	  {"Hz",       Utype::LIN,      1.0e0,           { 0, 0,-1, 0, 0, 0, 0, 0},  "s-1",                    "Hertz",             true,  {}             },
	  {"Bq",       Utype::LIN,      1.0e0,           { 0, 0,-1, 0, 0, 0, 0, 0},  "s-1",                    "Becquerel",         false, {}             },
	  
	  // units of power	           
	  {"W",        Utype::LIN,      1.0e3,           { 2, 1,-3, 0, 0, 0, 0, 0},  "J/s",                    "Watt",              true,  {}             },
	  {"hp",       Utype::LIN,      745700.0,        { 2, 1,-3, 0, 0, 0, 0, 0},  "745.7*W",                "horse power",       false, {}             },
	  
	  // units of velocity	           
	  {"kph",      Utype::LIN,      0.277778,        { 1, 0,-1, 0, 0, 0, 0, 0},  "km/h",                   "kilometer p. hour", false, {}             },
	  {"kn",       Utype::LIN,      0.514444,        { 1, 0,-1, 0, 0, 0, 0, 0},  "0.514444*m/s",           "knot",              false, {}             },
	  
	  // units of magnetic flux         
	  {"Mx",       Utype::LIN,      1.0e-5,          { 2, 1,-2, 0,-1, 0, 0, 0},  "1e-8*Wb",                "Maxwell",           false, {}             },
	  {"Wb",       Utype::LIN,      1.0e3,           { 2, 1,-2, 0,-1, 0, 0, 0},  "V*s",                    "Weber",             false, {}             },
	  
	  // other CGS units	           
	  {"P",        Utype::LIN,      1.0e2,           {-1, 1,-1, 0, 0, 0, 0, 0},  "g/(cm*s)",               "Poise",             true,  {"c"}          },
	  {"St",       Utype::LIN,      1.0e-4,          { 2, 0,-1, 0, 0, 0, 0, 0},  "cm2/s",                  "Stokes",            true,  {"c"}          },
	  {"Ka",       Utype::LIN,      1.0e2,           {-1, 0, 0, 0, 0, 0, 0, 0},  "cm-1",                   "Kayser",            false, {}             },
	  {"D",        Utype::LIN,      3.33564e-30,     { 1, 0, 1, 0, 1, 0, 0, 0},  "3.33564e-30*C*m",        "Debye",             true,  {}             },
	  {"Oe",       Utype::LIN,      79.57747,        {-1, 0, 0, 0, 1, 0, 0, 0},  "1e3*A/(4*[pi]*m)",       "Oersted",           false, {}             },
	  {"Gal",      Utype::LIN,      0.01,            { 1, 0,-2, 0, 0, 0, 0, 0},  "cm/s2",                  "Gal",               false, {}             },
	  {"Bi",       Utype::LIN,      10,              { 0, 0, 0, 0, 1, 0, 0, 0},  "10*A",                   "Biot",              false, {}             },
	  {"Rad",      Utype::LIN,      1e-2,            { 2, 0,-2, 0, 0, 0, 0, 0},  "0.01*Gy",                "radiation dose",    false, {}             },
	  
	  // other derived units           	      
	  {"sr",       Utype::LIN,      1.0e0,           { 0, 0, 0, 0, 0, 0, 0, 2},  "rad2",                   "steradian",         false, {}             },
	  {"lm",       Utype::LIN,      1.0e0,           { 0, 0, 0, 0, 0, 1, 0, 2},  "cd*sr",                  "lumen",             false, {}             },
	  {"C",        Utype::LIN,      1.0e0,           { 0, 0, 1, 0, 1, 0, 0, 0},  "A*s",                    "coulomb",           true,  {}             },
	  {"H",        Utype::LIN,      1.0e3,           { 2, 1,-2, 0,-2, 0, 0, 0},  "Wb/A",                   "Henry",             true,  {}             },
	  {"Ohm",      Utype::LIN,      1.0e3,           { 2, 1,-3, 0,-2, 0, 0, 0},  "V/A",                    "Ohm",               true,  {}             },
	  {"V",        Utype::LIN,      1.0e3,           { 2, 1,-3, 0,-1, 0, 0, 0},  "J/C",                    "Volt",              true,  {}             },
	  {"lx",       Utype::LIN,      1.0e0,           {-2, 0, 0, 0, 0, 1, 0, 2},  "lm/m2",                  "lux",               false, {}             },
	  {"F",        Utype::LIN,      1.0e-3,          {-2,-1, 4, 0, 2, 0, 0, 0},  "C/V",                    "Farad",             true,  {}             },
	  {"S",        Utype::LIN,      1.0e-3,          {-2,-1, 3, 0, 2, 0, 0, 0},  "Ohm-1",                  "Siemens",           true,  {}             },
	  {"kat",      Utype::LIN,      1,               { 0, 0,-1, 0, 0, 0, 1, 0},  "mol/s",                  "katal",             true,  {}             },
	  {"dpt",      Utype::LIN,      1,               {-1, 0, 0, 0, 0, 0, 0, 0},  "1/m",                    "dpt",               true,  {}             },
	  
	  // percentages	           	      
	  {"%",        Utype::LIN,      1e-2,            { 0, 0, 0, 0, 0, 0, 0, 0},  "1e-2",                   "percent",           false, {}             },
	  {"ppth",     Utype::LIN,      1e-3,            { 0, 0, 0, 0, 0, 0, 0, 0},  "1e-3",                   "promile",           false, {}             },
	  
#ifdef UNITS_LOGARITHMIC
	  // logarithmic units and ratios
	  {"PR",       UT_LIN_LOG,      1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Power ratio",       false, {}             }, 
	  {"AR",       UT_LIN_LOG,      1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Amplitude ratio",   false, {}             },
	  {"Np",       Utype::LOG,      1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Nepers",            true,  {"c","d"}      },
	  {"B",        Utype::LOG,      1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Bel",               true,  {"d"}          },
	  {"Bm",       Utype::LOG,      1,               { 2, 1,-3, 0, 0, 0, 0, 0},  "mW",                     "bel-milliwatt",     true,  {"d"}          },
	  {"BmW",      Utype::LOG,      1,               { 2, 1,-3, 0, 0, 0, 0, 0},  "mW",                     "bel-milliwatt",     true,  {"d"}          },
	  {"BW",       Utype::LOG,      1,               { 2, 1,-3, 0, 0, 0, 0, 0},  "W",                      "bel-watt",          true,  {"d"}          },
	  {"BV",       Utype::LOG,      1,               { 2, 1,-3, 0,-1, 0, 0, 0},  "V",                      "bel-volt",          true,  {"d"}          },
	  {"BuV",      Utype::LOG,      1,               { 2, 1,-3, 0,-1, 0, 0, 0},  "uV",                     "bel-microvolt",     true,  {"d"}          },
	  {"BA",       Utype::LOG,      1,               { 0, 0, 0, 0, 1, 0, 0, 0},  "A",                      "bel-amps",          true,  {"d"}          },
	  {"BuA",      Utype::LOG,      1,               { 0, 0, 0, 0, 1, 0, 0, 0},  "uA",                     "bel-microamps",     true,  {"d"}          },
	  {"BOhm",     Utype::LOG,      1,               { 2, 1,-3, 0,-2, 0, 0, 0},  "Ohm",                    "bel-ohms",          true,  {"d"}          },
	  {"BSPL",     Utype::LOG,      1,               {-1, 1,-2, 0, 0, 0, 0, 0},  "Pa",                     "bel-SPL (Pa)",      true,  {"d"}          },
	  {"BSIL",     Utype::LOG,      1,               { 0, 1,-3, 0, 0, 0, 0, 0},  "W/m2",                   "bel-SIL (W/m2)",    true,  {"d"}          }, 
	  {"BSWL",     Utype::LOG,      1,               { 2, 1,-3, 0, 0, 0, 0, 0},  "W",                      "bel-SWL (W)",       true,  {"d"}          },
#endif
	  
	  // dimensionless constants    
	  {"[alpha]",  UT_LIN_CST,      7.29735256e-3,   { 0, 0, 0, 0, 0, 0, 0, 0},  "7.29735256e-3",          "fine str. const.",  false, {}             },
	  {"[euler]",  UT_LIN_CST,      2.718282,        { 0, 0, 0, 0, 0, 0, 0, 0},  "2.718282",               "Euler's num.",      false, {}             },
	  {"[N_0]",    UT_LIN_CST,      6.02214076e23,   { 0, 0, 0, 0, 0, 0, 0, 0},  "6.02214076e23",          "Avogadro's num.",   false, {}             },
	  {"[pi]",     UT_LIN_CST,      3.1415926,       { 0, 0, 0, 0, 0, 0, 0, 0},  "3.1415926",              "pi num.",           false, {}             },
	  
	  // natural constants              
	  {"[a_0]",    UT_LIN_CST,      5.291772109e-11, { 1, 0, 0, 0, 0, 0, 0, 0},  "5.29177210903e-11*m",    "Bohr radius",       false, {}             },
	  {"[c]",      UT_LIN_CST,      2.99792458e8,    { 1, 0,-1, 0, 0, 0, 0, 0},  "299792458*m/s",          "speed of light",    false, {}             },
	  {"[e]",      UT_LIN_CST,      1.602176634e-19, { 0, 0, 1, 0, 1, 0, 0, 0},  "1.602176634e-19*C",      "elem. charge",      false, {}             },
	  {"[eps_0]",  UT_LIN_CST,      8.854188e-15,    {-3,-1, 4, 0, 2, 0, 0, 0},  "8.854187817e-12*F/m",    "permit. of vac.",   false, {}             },
	  {"[G]",      UT_LIN_CST,      6.672590e-14,    { 3,-1,-2, 0, 0, 0, 0, 0},  "6.67259e-11*m3/(kg*s2)", "grav. const.",      false, {}             },
	  {"[g]",      UT_LIN_CST,      9.806650e0,      { 1, 0,-2, 0, 0, 0, 0, 0},  "9.80665*m/s2",           "grav. accel.",      false, {}             },
	  {"[h]",      UT_LIN_CST,      6.626076e-31,    { 2, 1,-1, 0, 0, 0, 0, 0},  "6.6260755e-34*J*s",      "Planck const.",     false, {}             },
	  {"[hbar]",   UT_LIN_CST,      1.054572748e-31, { 2, 1,-1, 0, 0, 0, 0, 0},  "[h]/(2*[pi])",           "Reduced Pl. con.",  false, {}             },
	  {"[H_0]",    UT_LIN_CST,      2.197232394e-18, { 0, 0,-1, 0, 0, 0, 0, 0},  "67.8*km/(s*Mpc)",        "Hubble const.",     false, {}             },
	  {"[k]",      UT_LIN_CST,      1.380658e-20,    { 2, 1,-2,-1, 0, 0, 0, 0},  "1.380658e-23*J/K",       "Boltzmann const.",  false, {}             },
	  {"[k_B]",    UT_LIN_CST,      1.380658e-20,    { 2, 1,-2,-1, 0, 0, 0, 0},  "[k]",                    "Boltzmann const.",  false, {}             },
	  {"[k_e]",    UT_LIN_CST,      8.9875517923e12, { 3, 1,-4, 0,-2, 0, 0, 0},  "8.9875517923e9*N*m2/C2", "Coulomb const.",    false, {}             },
	  {"[L_sol]",  UT_LIN_CST,      3.826e29,        { 2, 1,-3, 0, 0, 0, 0, 0},  "3.826e33*erg/s",         "Solar luminosity",  false, {}             },
	  {"[M_sol]",  UT_LIN_CST,      1.98847e33,      { 0, 1, 0, 0, 0, 0, 0, 0},  "1.98847e30*kg",          "Solar mass",        false, {}             },
	  {"[mu_0]",   UT_LIN_CST,      1.256637e-3,     { 1, 1,-2, 0,-2, 0, 0, 0},  "4*[pi]*1e-7*N/A2",       "permeab. of vac.",  false, {}             },
	  {"[mu_B]",   UT_LIN_CST,      1.67262e-24,     { 0, 1, 0, 0, 0, 0, 0, 0},  "1.67262e-24*g",          "Bohr magneton",     false, {}             },
	  {"[m_e]",    UT_LIN_CST,      9.109383e-28,    { 0, 1, 0, 0, 0, 0, 0, 0},  "9.1093837015e-31*kg",    "electron mass",     false, {}             },
	  {"[m_p]",    UT_LIN_CST,      1.672623e-24,    { 0, 1, 0, 0, 0, 0, 0, 0},  "1.6726231e-24*g",        "proton mass",       false, {}             },
	  {"[m_n]",    UT_LIN_CST,      1.6749286e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "1.6749286e-24*g",        "neutron mass",      false, {}             },
	  {"[R_inf]",  UT_LIN_CST,      1.09737e7,       {-1, 0, 0, 0, 0, 0, 0, 0},  "1.09737e5/cm",           "Rydberg constant",  false, {}             },
	  {"[R_sol]",  UT_LIN_CST,      6.9558e8,        { 1, 0, 0, 0, 0, 0, 0, 0},  "6.9558e10*cm",           "Solar radius",      false, {}             },
	  {"[sigma]",  UT_LIN_CST,      5.67037e-5,      { 0, 1,-3,-4, 0, 0, 0, 0},  "5.67037e-8*W/(m2*K4)",   "Stef.Bolt. const.", false, {}             },
	  {"[N_A]",    UT_LIN_CST,      6.02214076e23,   { 0, 0, 0, 0, 0, 0,-1, 0},  "[N_0]/mol",              "Avogadro's const.", false, {}             },
	  
	}),
      QuantityListType({
	  {"l",       {1,           { 1, 0, 0, 0, 0, 0, 0, 0},  "m"           }},
          {"m",       {1,           { 0, 1, 0, 0, 0, 0, 0, 0},  "g"           }},    
          {"t",       {1,           { 0, 0, 1, 0, 0, 0, 0, 0},  "s"           }},
          {"T",       {1,           { 0, 0, 0, 1, 0, 0, 0, 0},  "K"           }},  
          {"I",       {1,           { 0, 0, 0, 0, 1, 0, 0, 0},  "A"           }},
          {"Iv",      {1,           { 0, 0, 0, 0, 0, 1, 0, 0},  "cd"          }},
          {"n",       {1,           { 0, 0, 0, 0, 0, 0, 1, 0},  "mol"         }},
          {"the",     {1,           { 0, 0, 0, 0, 0, 0, 0, 1},  "rad"         }},
          {"v",       {1,           { 1, 0,-1, 0, 0, 0, 0, 0},  "m/s"         }},
          {"a",       {1,           { 1, 0,-2, 0, 0, 0, 0, 0},  "m/s2"        }},
          {"jerk",    {1,           { 1, 0,-3, 0, 0, 0, 0, 0},  "m/s3"        }},
          {"snap",    {1,           { 1, 0,-4, 0, 0, 0, 0, 0},  "m/s4"        }},
          {"crac",    {1,           { 1, 0,-5, 0, 0, 0, 0, 0},  "m/s5"        }},
          {"pop",     {1,           { 1, 0,-6, 0, 0, 0, 0, 0},  "m/s6"        }},
          {"rho",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg/m3"       }},
          {"rho_A",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg/m2"       }},
          {"rho_l",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg/m1"       }},
          {"rho_E",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/m3"        }},
          {"A",       {1,           { 2, 0, 0, 0, 0, 0, 0, 0},  "m2"          }},
          {"V",       {1,           { 3, 0, 0, 0, 0, 0, 0, 0},  "m3"          }},
          {"p_mom",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg*m/s"      }},
          {"I_mom",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg*m2"       }},
          {"ome",     {1,           { 0, 0,-1, 0, 0, 0, 0, 1},  "rad/s"       }},
          {"a_ome",   {1,           { 0, 0,-2, 0, 0, 0, 0, 1},  "rad/s2"      }},
          {"L_ome",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg*m2/s"     }},
          {"F",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "N"           }},
          {"freq",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Hz"          }},
          {"J_i",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "N*s"         }},
          {"Abs",     {1,           { 1, 0, 1, 0, 0, 0, 0, 0},  "m*s"         }},
          {"nu",      {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Pa*s"        }},
          {"eps_s",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "1"           }},
          {"sig_s",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Pa"          }},
          {"E_Y",     {1000,        {-1, 1,-2, 0, 0, 0, 0, 0},  "Pa"          }},
          {"k_s",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "N/m"         }},
          {"gam",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/m2"        }},
          {"tau",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "N*m"         }},
          {"E",       {1000,        { 2, 1,-2, 0, 0, 0, 0, 0},  "J"           }},
          {"S",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/K"         }},
          {"p",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Pa"          }},
          {"mu_c",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/mol"       }},
          {"W",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J"           }},
          {"P",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W"           }},
          {"E_sp",    {1,           { 2, 0,-2, 0, 0, 0, 0, 0},  "J/kg"        }},
          {"C_sp",    {1,           { 2, 0,-2,-1, 0, 0, 0, 0},  "J/(K*kg)"    }},
          {"V_sp",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "m3/kg"       }},
          {"Q",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J"           }},
          {"C_p",     {1000,        { 2, 1,-2,-1, 0, 0, 0, 0},  "J/K"         }},
          {"phi_Q",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/m2"        }},
          {"C_mol",   {1,           {-3, 0, 0, 0, 0, 0, 1, 0},  "mol/m3"      }},
          {"E_mol",   {1000,        { 2, 1,-2, 0, 0, 0,-1, 0},  "J/mol"       }},
          {"c_mol",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/(K*mol)"   }},
	  {"S_mol",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/(K*mol)"   }},
          {"rr",      {1,           {-3, 0,-1, 0, 0, 0, 1, 0},  "mol/(m3*s)"  }},
          {"kap",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/K"         }},
          {"lam_t",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/(m*K)"     }},
          {"R_t",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "K/W"         }},
          {"R_lam",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "K*m/W"       }},
          {"Q_vol",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "m3/s"        }},
          {"q",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C"           }},
          {"rho_q",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C/m3"        }},
          {"p_e",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C*m"         }},
	  {"p_qe",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C*m2"        }},
	  {"D_e",     {1,           {-2, 0, 1, 0, 1, 0, 0, 0},  "C/m2"        }},
          {"E_e",     {1000,        { 1, 1,-3, 0,-1, 0, 0, 0},  "V/m"         }},
	  {"V_e",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "V/m2"        }},
	  {"alp_e",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C2*m2*J-1"   }},
	  {"alp_he",  {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C3*m3*J-2"   }},
	  {"alp_hhe", {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "C4*m4*J-3"   }},
          {"G_e",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "S"           }},
          {"sig_e",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "S/m"         }},
          {"phi_e",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "V"           }},
          {"R",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Ohm"         }},
          {"rho_e",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Ohm*m"       }},
          {"Mag",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "A/m"         }},
          {"H",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "A/m"         }},
          {"phi_m",   {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Wb"          }},
          {"B",       {1000,        { 0, 1,-2, 0,-1, 0, 0, 0},  "T"           }},
          {"mm",      {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "N*m/T"       }},             
          {"mu",      {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "H/m"         }},
          {"eps",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "F/m"         }},
          {"Ca",      {0.001,       {-2,-1, 0, 2, 4, 0, 0, 0},  "F"           }},
          {"J_c",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "A/m2"        }},
          {"Z",       {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Ohm"         }},
          {"L_i",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "H"           }},
          {"Rel",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "1/H"         }},
          {"P_o",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "dpt"         }},
          {"lam_w",   {1,           { 1, 0, 0, 0, 0, 0, 0, 0},  "m"           }},
          {"k_n",     {1,           {-1, 0, 0, 0, 0, 0, 0, 0},  "1/m"         }},
          {"k_v",     {1,           {-1, 0, 0, 0, 0, 0, 0, 0},  "1/m"         }},
          {"E_il",    {1,           {-2, 0, 0, 0, 0, 1, 0, 2},  "lx"          }},
          {"E_ir",    {1000,        { 1, 0,-3, 0, 0, 0, 0, 0},  "W/m2"        }},
          {"F_l",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "lm"          }},
          {"In",      {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/m2"        }},
          {"L_r",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/(m2*sr)"   }},
          {"I_r",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "W/sr"        }},
          {"D_a",     {1,           { 2, 0,-3, 0, 0, 0, 0, 0},  "Gy/s"        }},
          {"H_de",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "Sv"          }},
          {"D_r",     {1,           { 2, 0,-2, 0, 0, 0, 0, 0},  "Gy"          }},
          {"A_r",     {1,           { 0, 0,-1, 0, 0, 0, 0, 0},  "Bq"          }},
          {"S_a",     {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "J/Hz"        }},
          {"spin",    {1,           { 0, 0, 0, 0, 0, 0, 0, 0},  "kg*m2*s-1"   }},
	  
	})
      
    };
    
  } 
} 
