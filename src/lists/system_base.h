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
  {"m",        {UT_LIN_BAS,      "m",                            "meter",             true,  {}                        }},
  {"g",        {UT_LIN_BAS,      "g",                            "gram",              true,  {}                        }},
  {"s",        {UT_LIN_BAS,      "s",                            "second",            true,  {}                        }},
  {"K",        {UT_LIN_BAS_TMP,  "K",                            "Kelvin",            true,  {}                        }},
  {"A",        {UT_LIN_BAS,      "A",                            "Ampere",            true,  {}                        }},
  {"cd",       {UT_LIN_BAS,      "cd",                           "candela",           true,  {}                        }},
  {"mol",      {UT_LIN_BAS,      "mol",                          "mole",              true,  {}                        }},
  {"rad",      {UT_LIN_BAS,      "rad",                          "radian",            true,  {"m"}                     }},
};

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

const UnitListType _COLLAPSED_CONSTANTS = {
  // dimensionless constants     
  {"[#alpha]",  {UT_LIN_CSC,      "7.29735256e-3",                       "fine str. const.",  false, {}                        }},
  {"[#euler]",  {UT_LIN_CSC,      "2.718282",                            "Euler's num.",      false, {}                        }},
  {"[#N_0]",    {UT_LIN_CSC,      "6.02214076e23",                       "Avogadro's num.",   false, {}                        }},
  {"[#pi]",     {UT_LIN_CSC,      "3.1415926",                           "pi num.",           false, {}                        }},
      								            
  // natural constants              			                 						            
  {"[#a_0]",    {UT_LIN_CSC,      "5.29177210544(82)e-11*m",             "Bohr radius",       false, {}                        }},
  {"[#c]",      {UT_LIN_CSC,      "299792458*m/s",                       "speed of light",    false, {}                        }},
  {"[#e]",      {UT_LIN_CSC,      "1.602176634e-19*A*s",                 "elem. charge",      false, {}                        }},
  {"[#eps_0]",  {UT_LIN_CSC,      "8.8541878188(14)e-12*m-3*kg-1*s4*A2", "permit. of vac.",   false, {}                        }},
  {"[#G]",      {UT_LIN_CSC,      "6.67430(15)e-11*m3/(kg*s2)",          "grav. const.",      false, {}                        }},
  {"[#g]",      {UT_LIN_CSC,      "9.80665*m/s2",                        "grav. accel.",      false, {}                        }},
  {"[#h]",      {UT_LIN_CSC,      "6.62607015e-34*m2*kg*s-1",            "Planck const.",     false, {}                        }},
  {"[#hbar]",   {UT_LIN_CSC,      "1.054571817e-31*m2*g*s-1",            "Reduced Pl. con.",  false, {}                        }},
  {"[#H_0]",    {UT_LIN_CSC,      "69.8*3.24076e-20*s-1",                "Hubble const.",     false, {}                        }},
  {"[#k_B]",    {UT_LIN_CSC,      "1.380649e-23*kg*m2/(K*s2)",           "Boltzmann const.",  false, {}                        }},
  {"[#k_e]",    {UT_LIN_CSC,      "8.9875517923(14)e9*m3*kg*s-4*A-2",    "Coulomb const.",    false, {}                        }},
  {"[#L_sol]",  {UT_LIN_CSC,      "3.828e33*cm2*g*s-3",                  "Solar luminosity",  false, {}                        }},
  {"[#M_sol]",  {UT_LIN_CSC,      "1.98840(7)e30*kg",                    "Solar mass",        false, {}                        }},
  {"[#mu_0]",   {UT_LIN_CSC,      "1.25663706127(20)e-6*m*kg*s-2*A-2",   "permeab. of vac.",  false, {}                        }},
  {"[#mu_B]",   {UT_LIN_CSC,      "9.2740100657(29)e-24*m2*A",           "Bohr magneton",     false, {}                        }},
  {"[#m_e]",    {UT_LIN_CSC,      "9.1093837139(28)e-31*kg",             "electron mass",     false, {}                        }},
  {"[#m_p]",    {UT_LIN_CSC,      "1.67262192595(52)e-27*kg",            "proton mass",       false, {}                        }},
  {"[#m_n]",    {UT_LIN_CSC,      "1.67492750056(85)e-27*kg",            "neutron mass",      false, {}                        }},
  {"[#R_inf]",  {UT_LIN_CSC,      "10973731.568157(12)*m-1",             "Rydberg constant",  false, {}                        }},
  {"[#R_sol]",  {UT_LIN_CSC,      "6.9558e10*cm",                        "Solar radius",      false, {}                        }},
  {"[#sigma]",  {UT_LIN_CSC,      "5.670374419e-8*kg*s-3*K-4",           "Stef.Bolt. const.", false, {}                        }},
  {"[#N_A]",    {UT_LIN_CSC,      "[#N_0]/mol",                          "Avogadro's const.", false, {}                        }},
  {"[#kap_0]",  {UT_LIN_CSC,      "1.11265005620e-13*m-3*g-1*s4*A2",     "permittivity",      false, {}                        }},
};

const UnitListType _BASE_CONSTANTS = {
  // dimensionless constants     
  {"[alpha]",  {UT_LIN_CST,      "7.29735256e-3",                "fine str. const.",  false, {}                        }},
  {"[euler]",  {UT_LIN_CST,      "2.718282",                     "Euler's num.",      false, {}                        }},
  {"[N_0]",    {UT_LIN_CST,      "6.02214076e23",                "Avogadro's num.",   false, {}                        }},
  {"[pi]",     {UT_LIN_CST,      "3.1415926",                    "pi num.",           false, {}                        }},
      								     
  // natural constants              			         						            
  {"[a_0]",    {UT_LIN_CST,      "5.29177210544(82)e-11*m",      "Bohr radius",       false, {}                        }},
  {"[c]",      {UT_LIN_CST,      "299792458*m/s",                "speed of light",    false, {}                        }},
  {"[e]",      {UT_LIN_CST,      "1.602176634e-19*C",            "elem. charge",      false, {}                        }},
  {"[eps_0]",  {UT_LIN_CST,      "8.8541878188(14)e-12*F/m",     "permit. of vac.",   false, {}                        }},
  {"[G]",      {UT_LIN_CST,      "6.67430(15)e-11*m3/(kg*s2)",   "grav. const.",      false, {}                        }},
  {"[g]",      {UT_LIN_CST,      "9.80665*m/s2",                 "grav. accel.",      false, {}                        }},
  {"[h]",      {UT_LIN_CST,      "6.62607015e-34*J*s",           "Planck const.",     false, {}                        }},
  {"[hbar]",   {UT_LIN_CST,      "[h]/(2*[pi])",                 "Reduced Pl. con.",  false, {}                        }},
  {"[H_0]",    {UT_LIN_CST,      "69.8*km/(s*Mpc)",              "Hubble const.",     false, {}                        }},
  {"[k]",      {UT_LIN_CST,      "1.380649e-23*J/K",             "Boltzmann const.",  false, {}                        }},
  {"[k_B]",    {UT_LIN_CST,      "[k]",                          "Boltzmann const.",  false, {}                        }},
  {"[k_e]",    {UT_LIN_CST,      "8.9875517923(14)e9*N*m2/C2",   "Coulomb const.",    false, {}                        }},
  {"[L_sol]",  {UT_LIN_CST,      "3.828e33*erg/s",               "Solar luminosity",  false, {}                        }},
  {"[M_sol]",  {UT_LIN_CST,      "1.98840(7)e30*kg",             "Solar mass",        false, {}                        }},
  {"[mu_0]",   {UT_LIN_CST,      "1.25663706127(20)e-6*N/A2",    "permeab. of vac.",  false, {}                        }},
  {"[mu_B]",   {UT_LIN_CST,      "9.2740100657(29)e-24*J/T",     "Bohr magneton",     false, {}                        }},
  {"[m_e]",    {UT_LIN_CST,      "9.1093837139(28)e-31*kg",      "electron mass",     false, {}                        }},
  {"[m_p]",    {UT_LIN_CST,      "1.67262192595(52)e-27*kg",     "proton mass",       false, {}                        }},
  {"[m_n]",    {UT_LIN_CST,      "1.67492750056(85)e-27*kg",     "neutron mass",      false, {}                        }},
  {"[R_inf]",  {UT_LIN_CST,      "10973731.568157(12)*m-1",      "Rydberg constant",  false, {}                        }},
  {"[R_sol]",  {UT_LIN_CST,      "6.9558e10*cm",                 "Solar radius",      false, {}                        }},
  {"[sigma]",  {UT_LIN_CST,      "5.670374419e-8*W/(m2*K4)",     "Stef.Bolt. const.", false, {}                        }},
  {"[N_A]",    {UT_LIN_CST,      "[N_0]/mol",                    "Avogadro's const.", false, {}                        }},
};
    
#endif // PUQ_SYSTEM_BASE_H
