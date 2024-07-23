#import "lists.h"

/*
 * English unit systems
 */

#ifdef UNIT_SYSTEM_EUS

namespace puq {

  const UnitListType _EUS  = {
    {"m",        UT_LIN_BAS,     1.0,             { 1, 0, 0, 0, 0, 0, 0, 0},  "m",                      "meter",             false, {}             },
    {"g",        UT_LIN_BAS,     1.0,             { 0, 1, 0, 0, 0, 0, 0, 0},  "g",                      "gramm",             false, {}             },
    {"s",        UT_LIN_BAS,     1.0,             { 0, 0, 1, 0, 0, 0, 0, 0},  "s",                      "second",            false, {}             },
    {"K",        UT_LIN_BAS_TMP, 1.0,             { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "Kelfin",            false, {}             },
    {"x1",       Utype::NUL,     1.0,             { 0, 0, 0, 0, 1, 0, 0, 0},  "",                       "",                  false, {}             },
    {"x2",       Utype::NUL,     1.0,             { 0, 0, 0, 0, 0, 1, 0, 0},  "",                       "",                  false, {}             },
    {"x3",       Utype::NUL,     1.0,             { 0, 0, 0, 0, 0, 0, 1, 0},  "",                       "",                  false, {}             },
    {"x4",       Utype::NUL,     1.0,             { 0, 0, 0, 0, 0, 0, 0, 1},  "",                       "",                  false, {}             },

    // units of length
    {"twip",     Utype::LIN,     17.6388888e-6,   { 1, 0, 0, 0, 0, 0, 0, 0},  "17.6388888e-6*m",        "twip",              false, {}             },    
    {"th",       Utype::LIN,     25.4e-6,         { 1, 0, 0, 0, 0, 0, 0, 0},  "25.4e-6*m",              "thou",              false, {}             },    
    {"mil",      Utype::LIN,     25.4e-6,         { 1, 0, 0, 0, 0, 0, 0, 0},  "th",                     "mil",               false, {}             },
    {"in",       Utype::LIN,     0.0254,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.0254*m",               "inch",              false, {}             },    
    {"''",       Utype::LIN,     0.0254,          { 1, 0, 0, 0, 0, 0, 0, 0},  "in",                     "inch",              false, {}             },    
    {"li",       Utype::LIN,     0.201168,        { 1, 0, 0, 0, 0, 0, 0, 0},  "0.201168*m",             "link",              false, {}             },
    {"ft",       Utype::LIN,     0.3048,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.3048*m",               "foot",              false, {}             },
    {"'",        Utype::LIN,     0.3048,          { 1, 0, 0, 0, 0, 0, 0, 0},  "ft",                     "foot",              false, {}             },    
    {"yd",       Utype::LIN,     0.9144,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.9144*m",               "yard",              false, {}             },    
    {"rd",       Utype::LIN,     5.0292,          { 1, 0, 0, 0, 0, 0, 0, 0},  "5.0292*m",               "rod/pole/perch",    false, {}             },    
    {"ch",       Utype::LIN,     20.1168,         { 1, 0, 0, 0, 0, 0, 0, 0},  "20.1168*m",              "chain",             false, {}             },    
    {"fur",      Utype::LIN,     201.168,         { 1, 0, 0, 0, 0, 0, 0, 0},  "201.168*m",              "furlong",           false, {}             },
    {"mi",       Utype::LIN,     1609.344,        { 1, 0, 0, 0, 0, 0, 0, 0},  "1609.344*m",             "mile",              false, {}             },    
    {"lea",      Utype::LIN,     4828.032,        { 1, 0, 0, 0, 0, 0, 0, 0},  "4828.032*m",             "league",            false, {}             },
    {"le",       Utype::LIN,     4828.032,        { 1, 0, 0, 0, 0, 0, 0, 0},  "lea",                    "league",            false, {}             },

    // international nautical units
    {"ftm",      Utype::LIN,     1.8288,          { 1, 0, 0, 0, 0, 0, 0, 0},  "1.8288*m",               "fathom",            false, {}             },
    {"cb",       Utype::LIN,     219.456,         { 1, 0, 0, 0, 0, 0, 0, 0},  "219.456*m",              "cable",             false, {}             },
    {"nmi",      Utype::LIN,     1852,            { 1, 0, 0, 0, 0, 0, 0, 0},  "1852*m",                 "nautical mile",     false, {}             },
    {"NM",       Utype::LIN,     1852,            { 1, 0, 0, 0, 0, 0, 0, 0},  "nmi",                    "nautical mile",     false, {}             },
    
    // units of area
    {"ac",       Utype::LIN,     4046.8564224,    { 2, 0, 0, 0, 0, 0, 0, 0},  "4046.8564224*m2",        "acre",              false, {}             },
    
    // units of mass
    {"gr",       Utype::LIN,     64.79891e-3,     { 0, 1, 0, 0, 0, 0, 0, 0},  "64.79891e-3*g",          "grain",             false, {}             },
    {"dr",       Utype::LIN,     1.771845195,     { 0, 1, 0, 0, 0, 0, 0, 0},  "1.771845195*g",          "drachm/dram",       false, {}             },
    {"oz",       Utype::LIN,     28.349523125,    { 0, 1, 0, 0, 0, 0, 0, 0},  "28.349523125*g",         "ounce",             false, {}             },
    {"lb",       Utype::LIN,     453.59237,       { 0, 1, 0, 0, 0, 0, 0, 0},  "453.59237*g",            "pund",              false, {}             },
    {"cwt",      Utype::LIN,     50.80234544e3,   { 0, 1, 0, 0, 0, 0, 0, 0},  "50.80234544e3*g",        "long hundredweight",false, {}             },
    {"ton",      Utype::LIN,     1.0160469088e6,  { 0, 1, 0, 0, 0, 0, 0, 0},  "1.0160469088e6*g",       "long ton",          false, {}             },  
    
    // units of time	           
    {"min",      Utype::LIN,     6.0e1,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*s",                   "minute",            false, {}             },
    {"h",        Utype::LIN,     3.6e3,           { 0, 0, 1, 0, 0, 0, 0, 0},  "60*min",                 "hour",              false, {}             },
    {"day",      Utype::LIN,     8.64e4,          { 0, 0, 1, 0, 0, 0, 0, 0},  "24*h",                   "day",               false, {}             },
    {"yr_t",     Utype::LIN,     3.1556925e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.24219*day",          "tropical year",     true,  {"k","m","G"}  },
    {"yr_j",     Utype::LIN,     3.1557600e7,     { 0, 0, 1, 0, 0, 0, 0, 0},  "365.25*day",             "Julian year",       true,  {"k","m","G"}  },
    {"yr_g",     Utype::LIN,     3.155695e7,      { 0, 0, 1, 0, 0, 0, 0, 0},  "365.2425*day",           "Gregorian year",    true,  {"k","m","G"}  },
    {"yr",       Utype::LIN,     3.155760e7,      { 0, 0, 1, 0, 0, 0, 0, 0},  "yr_j",                   "year",              true,  {"k","m","G"}  },
    
    // units of temperature	
    {"degR",     UT_LIN_TMP,      5./9.,          { 0, 0, 0, 1, 0, 0, 0, 0},  "5/9*K",                  "degree Rankine",    false, {}             },
#ifdef UNITS_TEMPERATURES
    {"Cel",      Utype::TMP,      1,              { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "degree Celsius",    false, {}             },
    {"degF",     Utype::TMP,      1,              { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "degree Fahrenheit", false, {}             },
#endif
    
    // units of velocity	           
    {"mph",      Utype::LIN,     0.44704,         { 1, 0,-1, 0, 0, 0, 0, 0},  "mi/h",                   "miles per hour",    false, {}             },
};
  
  /*
   * Imperial units
   */

  const UnitListType UnitSystem::IU = _EUS + UnitListType({

    // units of length
    {"bc",       Utype::LIN,     8.4667e-3,       { 1, 0, 0, 0, 0, 0, 0, 0},  "8.4667e-3*m",            "barleycorn",        false, {}             },    
    {"hh",       Utype::LIN,     0.1016,          { 1, 0, 0, 0, 0, 0, 0, 0},  "0.1016*m",               "hand",              false, {}             },
    
    // units of area
    {"sqrd",     Utype::LIN,     25.29285264,     { 2, 0, 0, 0, 0, 0, 0, 0},  "25.29285264*m2",         "sq. rod/po./per.",  false, {}             },
    {"ro",       Utype::LIN,     1011.7141056,    { 2, 0, 0, 0, 0, 0, 0, 0},  "1011.7141056*m2",        "rood",              false, {}             },
    {"sqmi",     Utype::LIN,     2589988.110336,  { 2, 0, 0, 0, 0, 0, 0, 0},  "2589988.110336*m2",      "square mile",       false, {}             },
        
    // units of volume
    {"min",      Utype::LIN,     59.1938802083e-9,{ 3, 0, 0, 0, 0, 0, 0, 0},  "59.1938802083e-9*m3",    "minim",             false, {}             },
    {"fls",      Utype::LIN,     1.18387760416e-6,{ 3, 0, 0, 0, 0, 0, 0, 0},  "1.18387760416e-6*m3",    "fluid scruple",     false, {}             },
    {"fldr",     Utype::LIN,     3.5516328125e-6, { 3, 0, 0, 0, 0, 0, 0, 0},  "3.5516328125e-6*m3",     "fluid drachm",      false, {}             },
    {"floz",     Utype::LIN,     28.4130625e-6,   { 3, 0, 0, 0, 0, 0, 0, 0},  "28.4130625e-6*m3",       "fluid ounce",       false, {}             },
    {"gi",       Utype::LIN,     142.0653125e-6,  { 3, 0, 0, 0, 0, 0, 0, 0},  "142.0653125e-6*m3",      "gill",              false, {}             },    
    {"pt",       Utype::LIN,     568.26125e-6,    { 3, 0, 0, 0, 0, 0, 0, 0},  "568.26125e-6*m3",        "pint",              false, {}             },    
    {"qt",       Utype::LIN,     1136.5225e-6,    { 3, 0, 0, 0, 0, 0, 0, 0},  "1136.5225e-6*m3",        "quart",             false, {}             },    
    {"gal",      Utype::LIN,     4.54609e-3,      { 3, 0, 0, 0, 0, 0, 0, 0},  "4.54609e-3*m3",          "gallon",            false, {}             },
    {"bblo",     Utype::LIN,     0.16365924,      { 3, 0, 0, 0, 0, 0, 0, 0},  "0.16365924*m3",          "oil barrel",        false, {}             },
    
    // units of mass
    {"st",       Utype::LIN,     6.35029318e3,    { 0, 1, 0, 0, 0, 0, 0, 0},  "6.35029318e3*g",         "stone",             false, {}             },
    {"qr",       Utype::LIN,     12.70058636e3,   { 0, 1, 0, 0, 0, 0, 0, 0},  "12.70058636e3*g",        "quarter",           false, {}             },
    {"slug",     Utype::LIN,     14.59390294e3,   { 0, 1, 0, 0, 0, 0, 0, 0},  "14.59390294e3*g",        "slug",              false, {}             },
    
    });
  
  /*
   * United States customary units
   */

  const UnitListType UnitSystem::USCU = _EUS + UnitListType({

    // units of length
    {"p",        Utype::LIN,     352.778e-6,      { 1, 0, 0, 0, 0, 0, 0, 0},  "352.778e-6*m",           "point",             false, {}             },
    {"P",        Utype::LIN,     4.233e-3,        { 1, 0, 0, 0, 0, 0, 0, 0},  "4.233e-3*m",             "pica",              false, {}             },
    
    // units of area
    {"sqft",     Utype::LIN,     0.09290341,      { 2, 0, 0, 0, 0, 0, 0, 0},  "0.09290341*m2",          "sq. survey foot",   false, {}             },
    {"sqch",     Utype::LIN,     404.68564224,    { 2, 0, 0, 0, 0, 0, 0, 0},  "404.68564224*m2",        "square chain",      false, {}             },
    {"section",  Utype::LIN,     2.589998e6,      { 2, 0, 0, 0, 0, 0, 0, 0},  "2.589998e6*m2",          "section",           false, {}             },
    {"twp",      Utype::LIN,     93.23993e6,      { 2, 0, 0, 0, 0, 0, 0, 0},  "93.23993e6*m2",          "survey township",   false, {}             },
    
    // cubic units of volume
    {"cuin",     Utype::LIN,     16.387064e-6,    { 3, 0, 0, 0, 0, 0, 0, 0},  "16.387064e-6*m3",        "cubic inch",        false, {}             },
    {"cuft",     Utype::LIN,     28.316846592e-3, { 3, 0, 0, 0, 0, 0, 0, 0},  "28.316846592e-3*m3",     "cubic foot",        false, {}             },
    {"cuyd",     Utype::LIN,     0.764554857984,  { 3, 0, 0, 0, 0, 0, 0, 0},  "0.764554857984*m3",      "cubic yard",        false, {}             },
    {"acft",     Utype::LIN,     1233.482,        { 3, 0, 0, 0, 0, 0, 0, 0},  "1233.482*m3",            "acre-foot",         false, {}             },
    // fluid units of volume
    {"min",      Utype::LIN,     61.611519921875e-9, { 3, 0, 0, 0, 0, 0, 0, 0},  "61.611519921875e-9*m3", "minim",           false, {}             },
    {"fldr",     Utype::LIN,     3.6966911953125e-6, { 3, 0, 0, 0, 0, 0, 0, 0},  "3.6966911953125e-6*m3", "fluid drachm",    false, {}             },
    {"tsp",      Utype::LIN,     4.92892159375e-6,   { 3, 0, 0, 0, 0, 0, 0, 0},  "4.92892159375e-6*m3",   "teaspoon",        false, {}             },
    {"tbsp",     Utype::LIN,     14.78676478125e-6,  { 3, 0, 0, 0, 0, 0, 0, 0},  "14.78676478125e-6*m3",  "tablespoon",      false, {}             },
    {"floz",     Utype::LIN,     29.5735295625e-6,   { 3, 0, 0, 0, 0, 0, 0, 0},  "29.5735295625e-6*m3",   "fluid ounce",     false, {}             },
    {"jig",      Utype::LIN,     44.36029434375e-6,  { 3, 0, 0, 0, 0, 0, 0, 0},  "44.36029434375e-6*m3",  "jig",             false, {}             },
    {"gi",       Utype::LIN,     118.29411825e-6,    { 3, 0, 0, 0, 0, 0, 0, 0},  "118.29411825e-6*m3",    "gill",            false, {}             },
    {"c",        Utype::LIN,     236.5882365e-6,     { 3, 0, 0, 0, 0, 0, 0, 0},  "236.5882365e-6*m3",     "cup",             false, {}             },
    {"pt",       Utype::LIN,     0.473176473e-3,     { 3, 0, 0, 0, 0, 0, 0, 0},  "0.473176473e-3*m3",     "pint",            false, {}             },
    {"qt",       Utype::LIN,     0.946352946e-3,     { 3, 0, 0, 0, 0, 0, 0, 0},  "0.946352946e-3*m3",     "quart",           false, {}             },
    {"pot",      Utype::LIN,     1.892705892e-3,     { 3, 0, 0, 0, 0, 0, 0, 0},  "1.892705892e-3*m3",     "pottle",          false, {}             },
    {"gal",      Utype::LIN,     3.785411784e-3,     { 3, 0, 0, 0, 0, 0, 0, 0},  "3.785411784e-3*m3",     "gallon",          false, {}             },
    {"bbl",      Utype::LIN,     119.240471196e-3,   { 3, 0, 0, 0, 0, 0, 0, 0},  "119.240471196e-3*m3",   "liquid barrel",   false, {}             },
    {"bblo",     Utype::LIN,     158.987294928e-3,   { 3, 0, 0, 0, 0, 0, 0, 0},  "158.987294928e-3*m3",   "oil barrel",      false, {}             },
    {"hhd",      Utype::LIN,     238.480942392e-3,   { 3, 0, 0, 0, 0, 0, 0, 0},  "238.480942392e-3*m3",   "hogshead",        false, {}             },
    // dry units of volume
    {"ptd",      Utype::LIN,     0.55061047135749e-3, { 3, 0, 0, 0, 0, 0, 0, 0},  "0.55061047135749e-3*m3",  "dry pint",      false, {}            },
    {"qtd",      Utype::LIN,     1.1012209427149e-3,  { 3, 0, 0, 0, 0, 0, 0, 0},  "1.1012209427149e-3*m3",   "dry quart",     false, {}            },
    {"gald",     Utype::LIN,     4.4048837708599e-3,  { 3, 0, 0, 0, 0, 0, 0, 0},  "4.4048837708599e-3*m3",   "dry gallon",    false, {}            },
    {"pk",       Utype::LIN,     8.8097675417199e-3,  { 3, 0, 0, 0, 0, 0, 0, 0},  "8.8097675417199e-3*m3",   "peck",          false, {}            },
    {"bu",       Utype::LIN,     35.239070166879e-3,  { 3, 0, 0, 0, 0, 0, 0, 0},  "35.239070166879e-3*m3",   "bushel",        false, {}            },
    {"bbl",      Utype::LIN,     115.62712358400e-3,  { 3, 0, 0, 0, 0, 0, 0, 0},  "115.62712358400e-3*m3",   "liquid barrel", false, {}            },
    
    // units of mass
    {"cwts",     Utype::LIN,     45.359237e3,     { 0, 1, 0, 0, 0, 0, 0, 0},  "45.359237e3*g",          "short hundredwe.",  false, {}             },
    {"tons",     Utype::LIN,     907.18474e3,     { 0, 1, 0, 0, 0, 0, 0, 0},  "907.18474e3*g",          "short ton",         false, {}             },  
    {"dwt",      Utype::LIN,     1.55517384,      { 0, 1, 0, 0, 0, 0, 0, 0},  "1.55517384*g",           "pennyweight",       false, {}             },  
    {"ozt",      Utype::LIN,     31.1034768,      { 0, 1, 0, 0, 0, 0, 0, 0},  "31.1034768*g",           "troy ounce",        false, {}             },  
    {"lbt",      Utype::LIN,     373.241721,      { 0, 1, 0, 0, 0, 0, 0, 0},  "373.241721*g",           "troy pound",        false, {}             },
    
    });

}

#endif // UNIT_SYSTEM_EUS
