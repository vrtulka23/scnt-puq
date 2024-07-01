#import "lists.h"

std::vector<UnitStruct> UnitList = {
  {"m",   1.0, {1,0,0,0,0,0,0,0}, "", "meter",   true, {}    },
  {"g",   1.0, {0,1,0,0,0,0,0,0}, "", "gram",    true, {}    },
  {"s",   1.0, {0,0,1,0,0,0,0,0}, "", "second",  true, {}    },
  {"K",   1.0, {0,0,0,1,0,0,0,0}, "", "Kelvin",  true, {}    },
  {"C",   1.0, {0,0,0,0,1,0,0,0}, "", "Coulomb", true, {}    },
  {"cd",  1.0, {0,0,0,0,0,1,0,0}, "", "candela", true, {}    },
  {"mol", 1.0, {0,0,0,0,0,0,1,0}, "", "mole",    true, {}    },
  {"rad", 1.0, {0,0,0,0,0,0,0,1}, "", "radian",  true, {"m"} },

  // units of length
  {"au",       1.49597870e11,   { 1, 0, 0, 0, 0, 0, 0, 0},  "149597.870691*Mm",       "astr. unit",        false, {}             },
  {"AU",       1.49597870e11,   { 1, 0, 0, 0, 0, 0, 0, 0},  "au",                     "astr. unit",        false, {}             },
  {"ly",       9.460730e15,     { 1, 0, 0, 0, 0, 0, 0, 0},  "[c]*yr_j",               "light-year",        true,  {"k","M","G"}  },
  {"pc",       3.0857e16,       { 1, 0, 0, 0, 0, 0, 0, 0},  "3.0857e16*m",            "parsec",            true,  {"k","M","G","T"}  },
  {"Ao",       1e-10,           { 1, 0, 0, 0, 0, 0, 0, 0},  "1e-10*m",                "Angstrom",          true,  {"m","k"}      },
  {"twip",     1.76388887e-5,   { 1, 0, 0, 0, 0, 0, 0, 0},  "17.6388888*um",          "US twip",           false, {}             },
  {"mil",      2.53999999e-5,   { 1, 0, 0, 0, 0, 0, 0, 0},  "25.4*um",                "US mil",            false, {}             },
  {"p",        0.000352778,     { 1, 0, 0, 0, 0, 0, 0, 0},  "352.778*um",             "US point",          false, {}             },
  {"pi",       0.004233,        { 1, 0, 0, 0, 0, 0, 0, 0},  "4.233*mm",               "US pica",           false, {}             },
  {"in",       0.0254,          { 1, 0, 0, 0, 0, 0, 0, 0},  "25.4*mm",                "US inch",           false, {}             },
  {"ft",       0.3048,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.3048*m",               "US foot",           false, {}             },
  {"yd",       0.9144,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.9144*m",               "US yard",           false, {}             },
  {"mi",       1609.344,        { 1, 0, 0, 0, 0, 0, 0, 0},  "1.609344*km",            "US mile",           false, {}             },
  {"le",       4828.032,        { 1, 0, 0, 0, 0, 0, 0, 0},  "4.828032*km",            "US league",         false, {}             },
  			      
  // units of mass	      
  {"u",        1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "g/[N_0]",                "atomic mass unit",  false, {}             },
  {"amu",      1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "u",                      "atomic mass unit",  false, {}             },
  {"Da",       1.6605391e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "u",                      "Dalton",            false, {}             },
  {"t",        1e6,             { 0, 1, 0, 0, 0, 0, 0, 0},  "1e3*kg",                 "tonne",             true,  {"k","m","G"}  },
  {"oz",       28.349523125,    { 0, 1, 0, 0, 0, 0, 0, 0},  "28.349523125*g",         "US ounce",          false, {}             },
  {"lb",       453.59237,       { 0, 1, 0, 0, 0, 0, 0, 0},  "453.59237*g",            "US pound",          false, {}             },
  {"ton",      907184.74,       { 0, 1, 0, 0, 0, 0, 0, 0},  "907.18474*kg",           "US ton",            false, {}             },
  
  // units of time
  {"min",      6.0e1,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*s",                   "minute",            false, {}             },
  {"h",        3.6e3,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*min",                 "hour",              false, {}             },
  {"day",      8.64e4,          { 0, 0, 1, 0, 0, 0, 0, 0},  "24*h",                   "day",               false, {}             },
  {"yr_t",     3.1556925e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.24219*day",          "tropical year",     true,  {"k","m","G"}  },
  {"yr_j",     3.1557600e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.25*day",             "Julian year",       true,  {"k","m","G"}  },
  {"yr_g",     3.155695e7,      { 0, 0, 1, 0, 0, 0, 0, 0},  "365.2425*day",           "Gregorian year",    true,  {"k","m","G"}  },
  {"yr",       3.155760e7,      { 0, 0, 1, 0, 0, 0, 0, 0},  "yr_j",                   "year",              true,  {"k","m","G"}  },
  			      
  // units of temperature	      
  //{"Cel",      1,               { 0, 0, 0, 1, 0, 0, 0, 0},  TemperatureUnitType,      "degree Celsius",    false, {}             },
  {"degR",     5./9.,           { 0, 0, 0, 1, 0, 0, 0, 0},  "5/9*K",                  "degree Rankine",    false, {}             },
  //{"degF",     1,               { 0, 0, 0, 1, 0, 0, 0, 0},  TemperatureUnitType,      "degree Fahrenheit", false, {}             },
  			      
  // angular units	      
  {"deg",      1.7453292e-2,    { 0, 0, 0, 0, 0, 0, 0, 1},  "2*[pi]*rad/360",         "angle degree",      false, {}             },
  {"'",        2.908882e-4,     { 0, 0, 0, 0, 0, 0, 0, 1},  "deg/60",                 "angle minute",      false, {}             },
  {"''",       4.848137e-6,     { 0, 0, 0, 0, 0, 0, 0, 1},  "'/60",                   "angle second",      false, {}             },
  			      
  // units of surface	      
  {"ar",       1.0e2,           { 2, 0, 0, 0, 0, 0, 0, 0},  "100*m2",                 "are",               true,  {"c","d","da","h"} },
  {"acre",     4046.873,        { 2, 0, 0, 0, 0, 0, 0, 0},  "4046.873*m2",            "US acre",           false, {}             },
  			      
  // units of volume	      
  {"l",        1e-3,            { 3, 0, 0, 0, 0, 0, 0, 0},  "dm3",                    "liter",             true,  {}             },
  {"L",        1e-3,            { 3, 0, 0, 0, 0, 0, 0, 0},  "l",                      "liter",             true,  {}             },
  {"floz",     2.95735295e-05,  { 3, 0, 0, 0, 0, 0, 0, 0},  "29.5735295625*mL",       "US fluid ounce",    false, {}             },
  {"pt",       4.73176473e-04,  { 3, 0, 0, 0, 0, 0, 0, 0},  "473.176473*mL",          "US pint",           false, {}             },
  {"gal",      3.78541178e-03,  { 3, 0, 0, 0, 0, 0, 0, 0},  "3.785411784*L",          "US gallon",         false, {}             },
  {"bbl",      0.158987294928,  { 3, 0, 0, 0, 0, 0, 0, 0},  "158.987294928*L",        "US barrel",         false, {}             },
  			      
  // units of energy	      
  {"J",        1.0e3,           { 2, 1,-2, 0, 0, 0, 0, 0},  "N*m",                    "Joule",             true,  {}             },
  {"eV",       1.602176634e-16, { 2, 1,-2, 0, 0, 0, 0, 0},  "[e]*V",                  "electronvolt",      true,  {}             },
  {"erg",      1.0e-4,          { 2, 1,-2, 0, 0, 0, 0, 0},  "dyn*cm",                 "erg",               false, {}             },
  {"cal",      4184.0,          { 2, 1,-2, 0, 0, 0, 0, 0},  "4.184*J",                "calorie",           true,  {"k","M"}      },
  {"Cal",      4.184e6,         { 2, 1,-2, 0, 0, 0, 0, 0},  "kcal",                   "Calorie",           false, {}             },
  {"Ha",       4.35974472e-15,  { 2, 1,-2, 0, 0, 0, 0, 0},  "4.3597447222071e-18*J",  "Hartree",           true,  {"k","M"}      },
  {"E_h",      4.35974472e-15,  { 2, 1,-2, 0, 0, 0, 0, 0},  "Ha",                     "Hartree",           true,  {"k","M"}      },
  			      
  // units of pressure	      
  {"Pa",       1.0e3,           {-1, 1,-2, 0, 0, 0, 0, 0},  "N/m2",                   "Pascal",            true,  {}             },
  {"atm",      1.013250e8,      {-1, 1,-2, 0, 0, 0, 0, 0},  "101325*Pa",              "atm. pressure",     false, {}             },
  {"bar",      1e8,             {-1, 1,-2, 0, 0, 0, 0, 0},  "100*kPa",                "bar",               true,  {"M","k","d","c","m"}},
  {"Ba",       1e2,             {-1, 1,-2, 0, 0, 0, 0, 0},  "0.1*Pa",                 "Barye",             false, {}             },
  
  // units of force
  {"N",        1.0e3,           { 1, 1,-2, 0, 0, 0, 0, 0},  "kg*m/s2",                "Newton",            true,  {}             },
  {"dyn",      1.0e-2,          { 1, 1,-2, 0, 0, 0, 0, 0},  "g*cm/s2",                "dyne",              true,  {}             },
  
  // units of energy absorption
  {"Gy",       1.0e0,           { 2, 0,-2, 0, 0, 0, 0, 0},  "J/kg",                   "Gray",              false, {}             },
  {"Sv",       1.0e0,           { 2, 0,-2, 0, 0, 0, 0, 0},  "J/kg",                   "Sivert",            false, {}             },
  
  // units of magnetic flux density
  {"T",        1.0e3,           { 0, 1,-1, 0,-1, 0, 0, 0},  "Wb/m2",                  "Tesla",             true,  {}             },
  {"G",        1.0e-1,          { 0, 1,-1, 0,-1, 0, 0, 0},  "1e-4*T",                 "Gauss",             true,  {}             },
  			      
  // units of frequency	      
  {"Hz",       1.0e0,           { 0, 0,-1, 0, 0, 0, 0, 0},  "s-1",                    "Hertz",             true,  {}             },
  {"Bq",       1.0e0,           { 0, 0,-1, 0, 0, 0, 0, 0},  "s-1",                    "Becquerel",         false, {}             },
  			      
  // units of power	      
  {"W",        1.0e3,           { 2, 1,-3, 0, 0, 0, 0, 0},  "J/s",                    "Watt",              true,  {}             },
  {"hp",       745700.0,        { 2, 1,-3, 0, 0, 0, 0, 0},  "745.7*W",                "horse power",       false, {}             },
  			      
  // units of velocity	      
  {"mph",      0.44704,         { 1, 0,-1, 0, 0, 0, 0, 0},  "0.44704*m/s",            "US miles per hour", false, {}             },
  {"kn",       0.514444,        { 1, 0,-1, 0, 0, 0, 0, 0},  "0.514444*m/s",           "knot",              false, {}             },
  			      
  // units of magnetic flux     
  {"Mx",       1.0e-5,          { 2, 1,-1, 0,-1, 0, 0, 0},  "1e-8*Wb",                "Maxwell",           false, {}             },
  {"Wb",       1.0e3,           { 2, 1,-1, 0,-1, 0, 0, 0},  "V*s",                    "Weber",             false, {}             },
  			      
  // other CGS units	      
  {"P",        1.0e2,           {-1, 1,-1, 0, 0, 0, 0, 0},  "g/(cm*s)",               "Poise",             true,  {"c"}          },
  {"St",       1.0e-4,          { 2, 0,-1, 0, 0, 0, 0, 0},  "cm2/s",                  "Stokes",            true,  {"c"}          },
  {"Ka",       1.0e2,           {-1, 0, 0, 0, 0, 0, 0, 0},  "cm-1",                   "Kayser",            false, {}             },
  {"D",        3.33564e-30,     { 1, 0, 0, 0, 1, 0, 0, 0},  "3.33564e-30*C*m",        "Debye",             true,  {}             },
  {"Oe",       79.57747,        {-1, 0,-1, 0, 1, 0, 0, 0},  "1e3*A/(4*[pi]*m)",       "Oersted",           false, {}             },
  {"Gal",      0.01,            { 1, 0,-2, 0, 0, 0, 0, 0},  "cm/s2",                  "Gal",               false, {}             },
  {"Bi",       10,              { 0, 0,-1, 0, 1, 0, 0, 0},  "10*A",                   "Biot",              false, {}             },
  {"Rad",      1e-2,            { 2, 0,-2, 0, 0, 0, 0, 0},  "0.01*Gy",                "radiation dose",    false, {}             },
  			      
  // other derived units	      
  {"sr",       1.0e0,           { 0, 0, 0, 0, 0, 0, 0, 2},  "rad2",                   "steradian",         false, {}             },
  {"lm",       1.0e0,           { 0, 0, 0, 0, 0, 1, 0, 2},  "cd*sr",                  "lumen",             false, {}             },
  {"A",        1.0e0,           { 0, 0,-1, 0, 1, 0, 0, 0},  "C/s",                    "Ampere",            true,  {}             },
  {"H",        1.0e3,           { 2, 1, 0, 0,-2, 0, 0, 0},  "Wb/A",                   "Henry",             true,  {}             },
  {"Ohm",      1.0e3,           { 2, 1,-1, 0,-2, 0, 0, 0},  "V/A",                    "Ohm",               true,  {}             },
  {"V",        1.0e3,           { 2, 1,-2, 0,-1, 0, 0, 0},  "J/C",                    "Volt",              true,  {}             },
  {"lx",       1.0e0,           {-2, 0, 0, 0, 0, 1, 0, 2},  "lm/m2",                  "lux",               false, {}             },
  {"F",        1.0e-3,          {-2,-1, 2, 0, 2, 0, 0, 0},  "C/V",                    "Farad",             true,  {}             },
  {"S",        1.0e-3,          {-2,-1, 1, 0, 2, 0, 0, 0},  "Ohm-1",                  "Siemens",           true,  {}             },
  {"kat",      1,               { 0, 0,-1, 0, 0, 0, 1, 0},  "mol/s",                  "katal",             true,  {}             },
  
  // logarithmic units and ratios
  {"PR",       1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Power ratio",       false, {}             }, 
  {"AR",       1,               { 0, 0, 0, 0, 0, 0, 0, 0},  "1",                      "Amplitude ratio",   false, {}             },
  /*
  {"Np",       1,               { 0, 0, 0, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "Nepers",            true,  {"c","d"}      },
  {"B",        1,               { 0, 0, 0, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "Bel",               true,  {"d"}          },
  {"Bm",       1,               { 2, 1,-3, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-milliwatt",     true,  {"d"}          },
  {"BmW",      1,               { 2, 1,-3, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-milliwatt",     true,  {"d"}          },
  {"BW",       1,               { 2, 1,-3, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-watt",          true,  {"d"}          },
  {"BV",       1,               { 2, 1,-2, 0,-1, 0, 0, 0},  LogarithmicUnitType,      "bel-volt",          true,  {"d"}          },
  {"BuV",      1,               { 2, 1,-2, 0,-1, 0, 0, 0},  LogarithmicUnitType,      "bel-microvolt",     true,  {"d"}          },
  {"BA",       1,               { 0, 0,-1, 0, 1, 0, 0, 0},  LogarithmicUnitType,      "bel-amps",          true,  {"d"}          },
  {"BuA",      1,               { 0, 0,-1, 0, 1, 0, 0, 0},  LogarithmicUnitType,      "bel-microamps",     true,  {"d"}          },
  {"BOhm",     1,               { 2, 1,-1, 0,-2, 0, 0, 0},  LogarithmicUnitType,      "bel-ohms",          true,  {"d"}          },
  {"BSPL",     1,               {-1, 1,-2, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-SPL (Pa)",      true,  {"d"}          },
  {"BSIL",     1,               { 0, 1,-3, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-SIL (W/m2)",    true,  {"d"}          }, 
  {"BSWL",     1,               { 2, 1,-3, 0, 0, 0, 0, 0},  LogarithmicUnitType,      "bel-SWL (W)",       true,  {"d"}          },
  */
  			      
  // percentages		      
  {"%",        1e-2,            { 0, 0, 0, 0, 0, 0, 0, 0},  "1e-2",                   "percent",           false, {}             },
  {"ppth",     1e-3,            { 0, 0, 0, 0, 0, 0, 0, 0},  "1e-3",                   "promile",           false, {}             },
  			      
  // dimensionless constants    
  {"[alpha]",  7.29735256e-3,   { 0, 0, 0, 0, 0, 0, 0, 0},  "7.29735256e-3",          "fine str. const.",  false, {}             },
  {"[euler]",  2.718282,        { 0, 0, 0, 0, 0, 0, 0, 0},  "2.718282",               "Euler's num.",      false, {}             },
  {"[N_0]",    6.02214076e23,   { 0, 0, 0, 0, 0, 0, 0, 0},  "6.02214076e23",          "Avogadro's num.",   false, {}             },
  {"[pi]",     3.1415926,       { 0, 0, 0, 0, 0, 0, 0, 0},  "3.1415926",              "pi num.",           false, {}             },
  			      
  // natural constants          
  {"[a_0]",    5.291772109e-11, { 1, 0, 0, 0, 0, 0, 0, 0},  "5.29177210903e-11*m",    "Bohr radius",       false, {}             },
  {"[c]",      2.99792458e8,    { 1, 0,-1, 0, 0, 0, 0, 0},  "299792458*m/s",          "speed of light",    false, {}             },
  {"[e]",      1.602176634e-19, { 0, 0, 0, 0, 1, 0, 0, 0},  "1.602176634e-19*C",      "elem. charge",      false, {}             },
  {"[eps_0]",  8.854188e-15,    {-3,-1, 2, 0, 2, 0, 0, 0},  "8.854187817e-12*F/m",    "permit. of vac.",   false, {}             },
  {"[G]",      6.672590e-14,    { 3,-1,-2, 0, 0, 0, 0, 0},  "6.67259e-11*m3/(kg*s2)", "grav. const.",      false, {}             },
  {"[g]",      9.806650e0,      { 1, 0,-2, 0, 0, 0, 0, 0},  "9.80665*m/s2",           "grav. accel.",      false, {}             },
  {"[h]",      6.626076e-31,    { 2, 1,-1, 0, 0, 0, 0, 0},  "6.6260755e-34*J*s",      "Planck const.",     false, {}             },
  {"[hbar]",   1.054572748e-31, { 2, 1,-1, 0, 0, 0, 0, 0},  "[h]/(2*[pi])",           "Reduced Pl. con.",  false, {}             },
  {"[H_0]",    2.197232394e-18, { 0, 0,-1, 0, 0, 0, 0, 0},  "67.8*km/(s*Mpc)",        "Hubble const.",     false, {}             },
  {"[k]",      1.380658e-20,    { 2, 1,-2,-1, 0, 0, 0, 0},  "1.380658e-23*J/K",       "Boltzmann const.",  false, {}             },
  {"[k_B]",    1.380658e-20,    { 2, 1,-2,-1, 0, 0, 0, 0},  "[k]",                    "Boltzmann const.",  false, {}             },
  {"[k_e]",    8.9875517923e12, { 3, 1,-2, 0,-2, 0, 0, 0},  "8.9875517923e9*N*m2/C2", "Coulomb const.",    false, {}             },
  {"[L_sol]",  3.826e29,        { 2, 1,-3, 0, 0, 0, 0, 0},  "3.826e33*erg/s",         "Solar luminosity",  false, {}             },
  {"[M_sol]",  1.98847e33,      { 0, 1, 0, 0, 0, 0, 0, 0},  "1.98847e30*kg",          "Solar mass",        false, {}             },
  {"[mu_0]",   1.256637e-3,     { 1, 1, 0, 0,-2, 0, 0, 0},  "4*[pi]*1e-7*N/A2",       "permeab. of vac.",  false, {}             },
  {"[mu_B]",   1.67262e-24,     { 0, 1, 0, 0, 0, 0, 0, 0},  "1.67262e-24*g",          "Bohr magneton",     false, {}             },
  {"[m_e]",    9.109383e-28,    { 0, 1, 0, 0, 0, 0, 0, 0},  "9.1093837015e-31*kg",    "electron mass",     false, {}             },
  {"[m_p]",    1.672623e-24,    { 0, 1, 0, 0, 0, 0, 0, 0},  "1.6726231e-24*g",        "proton mass",       false, {}             },
  {"[m_n]",    1.6749286e-24,   { 0, 1, 0, 0, 0, 0, 0, 0},  "1.6749286e-24*g",        "neutron mass",      false, {}             },
  {"[R_inf]",  1.09737e7,       {-1, 0, 0, 0, 0, 0, 0, 0},  "1.09737e5/cm",           "Rydberg constant",  false, {}             },
  {"[R_sol]",  6.9558e8,        { 1, 0, 0, 0, 0, 0, 0, 0},  "6.9558e10*cm",           "Solar radius",      false, {}             },
  {"[sigma]",  5.67037e-5,      { 0, 1,-3,-4, 0, 0, 0, 0},  "5.67037e-8*W/(m2*K4)",   "Stef.Bolt. const.", false, {}             },
  {"[N_A]",    6.02214076e23,   { 0, 0, 0, 0, 0, 0,-1, 0},  "[N_0]/mol",              "Avogadro's const.", false, {}             },

};

