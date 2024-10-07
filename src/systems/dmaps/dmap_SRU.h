/*
 * Do not modify this file!
 * This file can be updated using 'dmap' executable.
 * 
 * Unit system:  Units for special relativity (SRU)
 * Last update:  Mon Oct  7 14:17:44 2024
 * Code version: 1.2.8
 * 
 * Symbol legend:
 * ..    units
 * [..]  constants
 * [#..] collapsed constants
 * <..>  quantities
 * |..|  quantity SI conversion factors
 */
{"rad",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 1} } },     // radian
{"cd",          {1,                       0,                       { 0, 0, 0, 0, 0, 1, 0, 0} } },     // candela
{"K",           {1,                       0,                       { 0, 0, 0, 1, 0, 0, 0, 0} } },     // Kelvin
{"A",           {1,                       0,                       { 0, 0, 0, 0, 1, 0, 0, 0} } },     // Ampere
{"s",           {1,                       0,                       { 0, 0, 1, 0, 0, 0, 0, 0} } },     // second
{"g",           {1,                       0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // gram
{"mol",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 1, 0} } },     // mole
{"m",           {1,                       0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // meter
{"[#k_B]",      {1.380649e-20,            0,                       { 2, 1,-2,-1, 0, 0, 0, 0} } },     // Boltzmann const.
{"[#c]",        {299792458,               0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // speed of light
{"[#g]",        {9.80665,                 0,                       { 1, 0,-2, 0, 0, 0, 0, 0} } },     // grav. accel.
{"[#m_p]",      {1.67262192595e-24,       5.2e-34,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // proton mass
{"[#G]",        {6.6743e-14,              1.5e-18,                 { 3,-1,-2, 0, 0, 0, 0, 0} } },     // grav. const.
{"[#k_e]",      {8987551792300,           1400,                    { 3, 1,-4, 0,-2, 0, 0, 0} } },     // Coulomb const.
{"[#pi]",       {3.1415926535,            0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // pi num.
{"[#M_sol]",    {1.988475e+33,            9.2e+28,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // Solar mass
{"[#H_0]",      {2.182975936e-18,         1.7500104e-20,           { 0, 0,-1, 0, 0, 0, 0, 0} } },     // Hubble const.
{"[#euler]",    {2.718281828459,          0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // Euler's num.
{"[#N_A]",      {6.02214076e+23,          0,                       { 0, 0, 0, 0, 0, 0,-1, 0} } },     // Avogadro's const.
{"[#kap_0]",    {1.1126500562e-13,        0,                       {-3,-1, 4, 0, 2, 0, 0, 0} } },     // permittivity
{"[#R_inf]",    {10973731.568157,         1.2e-05,                 {-1, 0, 0, 0, 0, 0, 0, 0} } },     // Rydberg constant
{"[#m_n]",      {1.67492749804e-24,       9.5e-34,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // neutron mass
{"[#eps_0]",    {8.8541878188e-15,        1.4e-24,                 {-3,-1, 4, 0, 2, 0, 0, 0} } },     // permit. of vac.
{"[#m_e]",      {9.1093837139e-28,        2.8e-37,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // electron mass
{"[#h]",        {6.62607015e-31,          0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // Planck const.
{"[c]",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // speed of light
{"[#hbar]",     {1.054571817e-31,         0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // Reduced Pl. con.
{"[#mu_B]",     {9.2740100657e-24,        2.9e-33,                 { 2, 0, 0, 0, 1, 0, 0, 0} } },     // Bohr magneton
{"[#N_0]",      {6.02214076e+23,          0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // Avogadro's num.
{"[#sigma]",    {5.670374419e-05,         0,                       { 0, 1,-3,-4, 0, 0, 0, 0} } },     // Stef.Bolt. const.
{"[#a_0]",      {5.29177210544e-11,       8.2e-21,                 { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Bohr radius
{"[#alpha]",    {0.0072973525643,         1.1e-12,                 { 0, 0, 0, 0, 0, 0, 0, 0} } },     // fine str. const.
{"[#R_sol]",    {695660000,               140000,                  { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Solar radius
{"[#e]",        {1.602176634e-19,         0,                       { 0, 0, 1, 0, 1, 0, 0, 0} } },     // elem. charge
{"[#L_sol]",    {3.828e+29,               0,                       { 2, 1,-3, 0, 0, 0, 0, 0} } },     // Solar luminosity
{"[#mu_0]",     {0.00125663706127,        2e-13,                   { 1, 1,-2, 0,-2, 0, 0, 0} } },     // permeab. of vac.
{"<rho_E>",     {1000,                    0,                       {-3, 1, 0, 0, 0, 0, 0, 0} } },     // energy density
{"|rho_E|",     {8.98755178736818e+16,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // energy density SI factor
{"<a>",         {1,                       0,                       {-1, 0, 0, 0, 0, 0, 0, 0} } },     // acceleration
{"|a|",         {8.98755178736818e+16,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // acceleration SI factor
{"<F>",         {1000,                    0,                       {-1, 1, 0, 0, 0, 0, 0, 0} } },     // force
{"|F|",         {8.98755178736818e+16,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // force SI factor
{"<m>",         {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // mass
{"<p_mom>",     {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // momentum
{"|p_mom|",     {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // momentum SI factor
{"<v>",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity
{"|v|",         {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity SI factor
{"<E>",         {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // energy
{"|E|",         {8.98755178736818e+16,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // energy SI factor
{"<t>",         {1,                       0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // time
{"|t|",         {3.33564095198152e-09,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // time SI factor
{"<L_ome>",     {1000,                    0,                       { 1, 1, 0, 0, 0, 0, 0, 0} } },     // angular momentum
{"|L_ome|",     {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // angular momentum SI factor
{"<l>",         {1,                       0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // length