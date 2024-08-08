#ifndef PUQ_SYSTEM_BASE_H
#define PUQ_SYSTEM_BASE_H

template<typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> vr(std::begin(v1), std::end(v1));
  vr.insert(std::end(vr), std::begin(v2), std::end(v2));
  return vr;
}

const std::vector<std::string> BaseUnitOrder = {"m", "g", "s", "K", "A", "cd", "mol", "rad"};

const UnitListType _BASE_UNITS = {
  {"m",        {UT_LIN_BAS,      "m",                      "meter",             true,  {}             }},
  {"g",        {UT_LIN_BAS,      "g",                      "gram",              true,  {}             }},
  {"s",        {UT_LIN_BAS,      "s",                      "second",            true,  {}             }},
  {"K",        {UT_LIN_BAS_TMP,  "K",                      "Kelvin",            true,  {}             }},
  {"A",        {UT_LIN_BAS,      "A",                      "Ampere",            true,  {}             }},
  {"cd",       {UT_LIN_BAS,      "cd",                     "candela",           true,  {}             }},
  {"mol",      {UT_LIN_BAS,      "mol",                    "mole",              true,  {}             }},
  {"rad",      {UT_LIN_BAS,      "rad",                    "radian",            true,  {"m"}          }},
};

#ifdef MAGNITUDE_ERRORS
const DimensionMapType _BASE_MAP = {
  {"m",   {1.0, 0.0, { 1, 0, 0, 0, 0, 0, 0, 0} } },
  {"g",   {1.0, 0.0, { 0, 1, 0, 0, 0, 0, 0, 0} } },
  {"s",   {1.0, 0.0, { 0, 0, 1, 0, 0, 0, 0, 0} } },
  {"K",   {1.0, 0.0, { 0, 0, 0, 1, 0, 0, 0, 0} } },
  {"A",   {1.0, 0.0, { 0, 0, 0, 0, 1, 0, 0, 0} } },
  {"cd",  {1.0, 0.0, { 0, 0, 0, 0, 0, 1, 0, 0} } },
  {"mol", {1.0, 0.0, { 0, 0, 0, 0, 0, 0, 1, 0} } },
  {"rad", {1.0, 0.0, { 0, 0, 0, 0, 0, 0, 0, 1} } },
};
#else
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
#endif

#endif // PUQ_SYSTEM_BASE_H
