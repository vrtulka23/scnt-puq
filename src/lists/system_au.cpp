#import "lists.h"

#ifdef UNIT_SYSTEM_AU

namespace puq {namespace SystemData {

  const SystemDataType AU = {
    "Atomic units",
    _BASE + UnitListType({
      {"E_h",      Utype::LIN,     4.35975e-15,      { 2, 1,-2, 0, 0, 0, 0, 0},  "[hbar]2/([m_e]*[a_0]2)",          "hartree",           false,  {}             },
      
      {"[hbar]",   UT_LIN_CST,     1.054571817e-31,  { 2, 1,-1, 0, 0, 0, 0, 0},  "1.054571817e-31*m2*g*s-1",        "reduced Pl. con.",  false,  {}             },
      {"[e]",      UT_LIN_CST,     1.602176634e-19,  { 0, 0, 1, 0, 1, 0, 0, 0},  "1.602176634e-19*s*A",             "elementary charge", false,  {}             },
      {"[m_e]",    UT_LIN_CST,     9.1093837139e-28, { 0, 1, 0, 0, 0, 0, 0, 0},  "9.1093837139e-31*kg",             "electr. rest mass", false,  {}             },
      {"[perm]",   UT_LIN_CST,     1.11265005620e-13,{-3,-1, 4, 0, 2, 0, 0, 0},  "1.11265005620e-13*m-3*g-1*s4*A2", "permittivity",      false,  {}             },
      {"[a_0]",    UT_LIN_CST,     5.29177e-11,      { 1, 0, 0, 0, 0, 0, 0, 0},  "[perm]*[hbar]2/([m_e]*[e]2)",     "Bohr radius",       false,  {}             },
      {"[alpha]",  UT_LIN_CST,     0.00729927,       { 0, 0, 0, 0, 0, 0, 0, 0},  "1/137",                           "fine-str. const.",  false,  {}             },
      {"[c]",      UT_LIN_CST,     2.99714e+08,      { 1, 0,-1, 0, 0, 0, 0, 0},  "[alpha]-1*[a_0]*E_h/[hbar]",      "speed of light",    false,  {}             },
      {"[r_e]",    UT_LIN_CST,     2.81942e-15,      { 1, 0, 0, 0, 0, 0, 0, 0},  "[alpha]2*[a_0]",                  "class. e. radius",  false,  {}             },
      {"[lbar]",   UT_LIN_CST,     3.86261e-13,      { 1, 0, 0, 0, 0, 0, 0, 0},  "[alpha]*[a_0]",                   "red. Com. wavele.", false,  {}             },
      {"[m_p]",    UT_LIN_CST,     1.67248e-24,      { 0, 1, 0, 0, 0, 0, 0, 0},  "1836*[m_e]",                      "proton mass",       false,  {}             },
    })
  };

}}

#endif // UNIT_SYSTEM_AU
