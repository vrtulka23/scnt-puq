#import "lists.h"

#ifdef UNITS_SYSTEM_AU

namespace puq {

namespace au {

  const UnitListType UnitList = { 
    {"[hbar]",   UT_LIN_BAS_CST, 1.0,             { 1, 0, 0, 0, 0, 0, 0, 0},  "[hbar]",                      "reduced Pl. con.",  false,  {}             },
    {"[e]",      UT_LIN_BAS_CST, 1.0,             { 0, 1, 0, 0, 0, 0, 0, 0},  "[e]",                         "elementary charge", false,  {}             },
    {"[m_e]",    UT_LIN_BAS_CST, 1.0,             { 0, 0, 1, 0, 0, 0, 0, 0},  "[m_e]",                       "electr. rest mass", false,  {}             },
    {"[perm]",   UT_LIN_BAS_CST, 1.0,             { 0, 0, 0, 1, 0, 0, 0, 0},  "4*[pi]*[eps_0]",              "permittivity",      false,  {}             },
    {"x1",       Utype::BAS,     1.0,             { 0, 0, 0, 0, 1, 0, 0, 0},  "",                            "",                  false,  {}             },
    {"x2",       Utype::BAS,     1.0,             { 0, 0, 0, 0, 0, 1, 0, 0},  "",                            "",                  false,  {}             },
    {"x3",       Utype::BAS,     1.0,             { 0, 0, 0, 0, 0, 0, 1, 0},  "",                            "",                  false,  {}             },
    {"x4",       Utype::BAS,     1.0,             { 0, 0, 0, 0, 0, 0, 0, 1},  "",                            "",                  false,  {}             },
    													    
    {"[a_0]",    UT_LIN_CST,     1.0,             { 2,-2,-1, 1, 0, 0, 0, 0},  "[perm]*[hbar]2/([m_e]*[e]2)", "Bohr radius",       false,  {}             },
    {"E_h",      Utype::LIN,     1.0,             {-2, 4, 1,-2, 0, 0, 0, 0},  "[hbar]2/([m_e]*[a_0]2)",      "hartree",           false,  {}             },
    {"[alpha]",  UT_LIN_CST,     0.00729927,      { 0, 0, 0, 0, 0, 0, 0, 0},  "1/137",                       "fine-str. const.",  false,  {}             },
  };

}
  
}

#endif // UNITS_SYSTEM_AU
