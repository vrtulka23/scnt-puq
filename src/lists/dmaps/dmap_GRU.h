/*
 * Do not modify this file!
 * This file can be updated using 'dmap' executable.
 * 
 * Unit system:  Units for general relativity (GRU)
 * Last update:  Thu Sep 26 23:18:56 2024
 * Code version: v1.1.2
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
{"[eps_0]",     {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // permit. of vac.
{"[k_B]",       {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // Boltzmann const.
{"[#c]",        {299792458,               0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // speed of light
{"[#kap_0]",    {1.1126500562e-13,        0,                       {-3,-1, 4, 0, 2, 0, 0, 0} } },     // permittivity
{"[pi]",        {3.1415926,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // pi num.
{"[#g]",        {9.80665,                 0,                       { 1, 0,-2, 0, 0, 0, 0, 0} } },     // grav. accel.
{"[hbar]",      {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // reduced Pl. con.
{"[#m_p]",      {1.67262192595e-24,       5.2e-34,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // proton mass
{"[#G]",        {6.6743e-14,              1.5e-18,                 { 3,-1,-2, 0, 0, 0, 0, 0} } },     // grav. const.
{"[#k_e]",      {8987551792300,           1400,                    { 3, 1,-4, 0,-2, 0, 0, 0} } },     // Coulomb const.
{"[#pi]",       {3.1415926,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // pi num.
{"[#R_sol]",    {695580000,               0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Solar radius
{"[#e]",        {1.602176634e-19,         0,                       { 0, 0, 1, 0, 1, 0, 0, 0} } },     // elem. charge
{"[#R_inf]",    {10973731.568157,         1.2e-05,                 {-1, 0, 0, 0, 0, 0, 0, 0} } },     // Rydberg constant
{"[#m_n]",      {1.67492750056e-24,       8.5e-34,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // neutron mass
{"[#eps_0]",    {8.8541878188e-15,        1.4e-24,                 {-3,-1, 4, 0, 2, 0, 0, 0} } },     // permit. of vac.
{"[#M_sol]",    {1.9884e+33,              7e+28,                   { 0, 1, 0, 0, 0, 0, 0, 0} } },     // Solar mass
{"[#k]",        {1.380649e-20,            0,                       { 2, 1,-2,-1, 0, 0, 0, 0} } },     // Boltzmann const.
{"[#H_0]",      {2.26205048e-18,          0,                       { 0, 0,-1, 0, 0, 0, 0, 0} } },     // Hubble const.
{"[#m_e]",      {9.1093837139e-28,        2.8e-37,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // electron mass
{"[#h]",        {6.62607015e-31,          0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // Planck const.
{"[c]",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // speed of light
{"[#hbar]",     {1.054571817e-31,         0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // Reduced Pl. con.
{"eV",          {1.602176634e-16,         0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // electronvolt
{"[#euler]",    {2.718282,                0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // Euler's num.
{"[#mu_0]",     {0.00125663706127,        2e-13,                   { 1, 1,-2, 0,-2, 0, 0, 0} } },     // permeab. of vac.
{"[#L_sol]",    {3.828e+29,               0,                       { 2, 1,-3, 0, 0, 0, 0, 0} } },     // Solar luminosity
{"[#mu_B]",     {9.2740100657e-24,        2.9e-33,                 { 2, 0, 0, 0, 1, 0, 0, 0} } },     // Bohr magneton
{"[#N_0]",      {6.02214076e+23,          0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // Avogadro's num.
{"[#alpha]",    {0.00729735256,           0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // fine str. const.
{"[#sigma]",    {5.670374419e-05,         0,                       { 0, 1,-3,-4, 0, 0, 0, 0} } },     // Stef.Bolt. const.
{"[#a_0]",      {5.29177210544e-11,       8.2e-21,                 { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Bohr radius
{"[#k_B]",      {1.380649e-20,            0,                       { 2, 1,-2,-1, 0, 0, 0, 0} } },     // Boltzmann const.
{"[alpha]",     {0.00729735269328366,     0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // fine-str. const.
{"[#N_A]",      {6.02214076e+23,          0,                       { 0, 0, 0, 0, 0, 0,-1, 0} } },     // Avogadro's const.
{"[e]",         {0.302822120861802,       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // elem. charge
{"<rho_E>",     {6.58933480909562e-28,    0,                       { 8, 4,-8, 0, 0, 0, 0, 0} } },     // energy density
{"|rho_E|",     {3.16453139621759e+76,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // energy density SI factor
{"<A>",         {38956435526576.1,        0,                       {-4,-2, 4, 0, 0, 0, 0, 0} } },     // area
{"|A|",         {9.99525152728783e-52,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // area SI factor
{"<F>",         {2.56696996653557e-14,    0,                       { 4, 2,-4, 0, 0, 0, 0, 0} } },     // force
{"|F|",         {3.16302872711942e+25,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // force SI factor
{"<m>",         {1.602176634e-07,         0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // mass
{"|m|",         {1.11265005605362e-17,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // mass SI factor
{"<p_mom>",     {1.602176634e-07,         0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // momentum
{"|p_mom|",     {3.33564095198152e-09,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // momentum SI factor
{"<q>",         {5.29081769006954e-19,    0,                       { 0, 0, 1, 0, 1, 0, 0, 0} } },     // electric charge
{"<v>",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity
{"|v|",         {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity SI factor
{"<E>",         {1.602176634e-07,         0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // energy
{"<t>",         {6241509.07446076,        0,                       {-2,-1, 2, 0, 0, 0, 0, 0} } },     // time
{"|t|",         {1.054571817e-34,         0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // time SI factor
{"<L_ome>",     {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // angular momentum
{"|L_ome|",     {1.054571817e-34,         0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // angular momentum SI factor
{"<l>",         {6241509.07446076,        0,                       {-2,-1, 2, 0, 0, 0, 0, 0} } },     // length
{"|l|",         {3.16152677155956e-26,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // length SI factor
