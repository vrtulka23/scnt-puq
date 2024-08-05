#ifndef PUQ_SYSTEM_BASE_H
#define PUQ_SYSTEM_BASE_H

template<typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> vr(std::begin(v1), std::end(v1));
  vr.insert(std::end(vr), std::begin(v2), std::end(v2));
  return vr;
}

const UnitListType _BASE_UNITS = {
  {"m",        UT_LIN_BAS,      1.0,             { 1, 0, 0, 0, 0, 0, 0, 0},  "m",                      "meter",             true,  {}             },
  {"g",        UT_LIN_BAS,      1.0,             { 0, 1, 0, 0, 0, 0, 0, 0},  "g",                      "gram",              true,  {}             },
  {"s",        UT_LIN_BAS,      1.0,             { 0, 0, 1, 0, 0, 0, 0, 0},  "s",                      "second",            true,  {}             },
  {"K",        UT_LIN_BAS_TMP,  1.0,             { 0, 0, 0, 1, 0, 0, 0, 0},  "K",                      "Kelvin",            true,  {}             },
  {"A",        UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 1, 0, 0, 0},  "A",                      "Ampere",            true,  {}             },
  {"cd",       UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 1, 0, 0},  "cd",                     "candela",           true,  {}             },
  {"mol",      UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 0, 1, 0},  "mol",                    "mole",              true,  {}             },
  {"rad",      UT_LIN_BAS,      1.0,             { 0, 0, 0, 0, 0, 0, 0, 1},  "rad",                    "radian",            true,  {"m"}          },
};

const DimensionMapType _BASE_MAP = {
  {"m",   {1.0, { 1, 0, 0, 0, 0, 0, 0, 0} } },
  {"g",   {1.0, { 0, 1, 0, 0, 0, 0, 0, 0} } },
  {"s",   {1.0, { 0, 0, 1, 0, 0, 0, 0, 0} } },
  {"K",   {1.0, { 0, 0, 0, 1, 0, 0, 0, 0} } },
  {"A",   {1.0, { 0, 0, 0, 0, 1, 0, 0, 0} } },
  {"cd",  {1.0, { 0, 0, 0, 0, 0, 1, 0, 0} } },
  {"mol", {1.0, { 0, 0, 0, 0, 0, 0, 1, 0} } },
  {"rad", {1.0, { 0, 0, 0, 0, 0, 0, 0, 1} } },
};

#endif // PUQ_SYSTEM_BASE_H
