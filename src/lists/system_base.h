#ifndef PUQ_SYSTEM_BASE_H
#define PUQ_SYSTEM_BASE_H

const UnitListType _BASE = {
  {"m",        UT_LIN_BAS,      1.0,             { 1, 0, 0, 0, 0, 0, 0, 0},  "m",                      "meter",             true,  {}             },
  {"g",        UT_LIN_BAS,      1.0,             { 0, 1, 0, 0, 0, 0, 0, 0},  "g",                      "gram",              true,  {}             },
  {"s",        UT_LIN_BAS,      1.0,             { 0, 0, 1, 0, 0, 0, 0, 0},  "s",                      "second",            true,  {}             },
  {"K",        UT_LIN_BAS_TMP,  1.0,             { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "Kelvin",            true,  {}             },
  {"A",        UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 1, 0, 0, 0},  "A",                      "Ampere",            true,  {}             },
  {"cd",       UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 1, 0, 0},  "cd",                     "candela",           true,  {}             },
  {"mol",      UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 0, 1, 0},  "mol",                    "mole",              true,  {}             },
  {"rad",      UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 0, 0, 1},  "rad",                    "radian",            true,  {"m"}          },
};

#endif // PUQ_SYSTEM_BASE_H
