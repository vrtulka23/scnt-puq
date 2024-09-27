/*
 * Do not modify this file!
 * This file can be updated using 'dmap' executable.
 * 
 * Unit system:  Gaussian CGS units (GU)
 * Last update:  Fri Sep 27 11:35:02 2024
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
{"Rayl",        {10000,                   0,                       {-2, 1,-1, 0, 0, 0, 0, 0} } },     // Rayl
{"Gal",         {0.01,                    0,                       { 1, 0,-2, 0, 0, 0, 0, 0} } },     // Gal
{"statF",       {0.01,                    0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Statfarad
{"Oe",          {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Oersted
{"Gb",          {0.1,                     0,                       {(FRC){1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Gilbert
{"St",          {0.0001,                  0,                       { 2, 0,-1, 0, 0, 0, 0, 0} } },     // Stokes
{"[a_0]",       {5.291772105e-11,         0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // Bohr radius
{"[alpha]",     {0.007297352564,          0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // fine-str. const.
{"Ka",          {100,                     0,                       {-1, 0, 0, 0, 0, 0, 0, 0} } },     // Kayser
{"[m_u]",       {1.660539069e-24,         0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // atom. mass const.
{"[c]",         {299792458,               0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // speed of light
{"[m_e]",       {9.10938371e-28,          0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // electron mass
{"Pma",         {0.0001,                  0,                       { 2, 0, 0, 0, 0, 0, 0, 0} } },     // permeability
{"dyn",         {0.01,                    0,                       { 1, 1,-2, 0, 0, 0, 0, 0} } },     // dyne
{"P",           {100,                     0,                       {-1, 1,-1, 0, 0, 0, 0, 0} } },     // Poise
{"G",           {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Gauss
{"[pi]",        {3.1415926,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // pi num.
{"statOhm",     {100,                     0,                       {-1, 0, 1, 0, 0, 0, 0, 0} } },     // Statohm
{"statH",       {100,                     0,                       {-1, 0, 2, 0, 0, 0, 0, 0} } },     // Stathenry
{"Fr",          {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // franklin
{"Ba",          {100,                     0,                       {-1, 1,-2, 0, 0, 0, 0, 0} } },     // Barye
{"Mx",          {1e-05,                   0,                       {(FRC){5,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Maxwell
{"[G]",         {6.6743e-14,              0,                       { 3,-1,-2, 0, 0, 0, 0, 0} } },     // gravit. const.
{"statC",       {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Statcoulomb
{"erg",         {0.0001,                  0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // erg
{"[hbar]",      {1.054571817e-31,         0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // reduced Pl. con.
{"[e]",         {4.80320471e-13,          0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // elementary charge
{"statA",       {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-2, 0, 0, 0, 0, 0} } },     // Statampere
{"b",           {100,                     0,                       {-1, 1,-2, 0, 0, 0, 0, 0} } },     // Barye
{"esu",         {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // elstat. u.o. charge
{"[mu_B]",      {9.274010066e-26,         0,                       {(FRC){5,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Bohr magneton
{"radd",        {0.01,                    0,                       { 2, 0,-2, 0, 0, 0, 0, 0} } },     // radiation dose
{"[k]",         {1.380649e-20,            0,                       { 2, 1,-2,-1, 0, 0, 0, 0} } },     // Boltzmann const.
{"statV",       {0.1,                     0,                       {(FRC){1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // Statvolt
{"[h]",         {6.62607015e-31,          0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // Planck const.
{"<Phi_M>",     {1e-05,                   0,                       {(FRC){5,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // magnetic flux
{"|Phi_M|",     {1e-08,                   0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // magnetic flux SI factor
{"<k_n>",       {100,                     0,                       {-1, 0, 0, 0, 0, 0, 0, 0} } },     // wave number
{"<I>",         {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-2, 0, 0, 0, 0, 0} } },     // current
{"|I|",         {3.33564095198152e-10,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // current SI factor
{"<P>",         {0.0001,                  0,                       { 2, 1,-3, 0, 0, 0, 0, 0} } },     // power
{"<Iv>",        {1,                       0,                       { 0, 0, 0, 0, 0, 1, 0, 0} } },     // luminous intensity
{"<D_e>",       {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric displacement field
{"|D_e|",       {2.65441877471758e-07,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric displacement field SI factor
{"<Phi_E>",     {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric flux
{"|Phi_E|",     {2.65441877471758e-11,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric flux SI factor
{"<a>",         {0.01,                    0,                       { 1, 0,-2, 0, 0, 0, 0, 0} } },     // acceleration
{"<B>",         {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // magnetic flux density
{"|B|",         {0.0001,                  0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // magnetic flux density SI factor
{"<rho_e>",     {1,                       0,                       { 0, 0, 1, 0, 0, 0, 0, 0} } },     // electrical resistivity
{"|rho_e|",     {8987551787.36818,        0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electrical resistivity SI factor
{"<the>",       {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 1} } },     // angular displacement
{"<nu_v>",      {0.0001,                  0,                       { 2, 0,-1, 0, 0, 0, 0, 0} } },     // kinematic viscosity
{"<p>",         {100,                     0,                       {-1, 1,-2, 0, 0, 0, 0, 0} } },     // pressure
{"<l>",         {0.01,                    0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // length
{"<v>",         {0.01,                    0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // velocity
{"<H>",         {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // magnetic field strenght
{"|H|",         {79.577472903393,         0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // magnetic field strenght SI factor
{"<E>",         {0.0001,                  0,                       { 2, 1,-2, 0, 0, 0, 0, 0} } },     // energy
{"<mu_v>",      {100,                     0,                       {-1, 1,-1, 0, 0, 0, 0, 0} } },     // dynamic viscosity
{"<n>",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 1, 0} } },     // amount of substance
{"<E_e>",       {10,                      0,                       {(FRC){-1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric field strength
{"|E_e|",       {29979.2458,              0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric field strength SI factor
{"<t>",         {1,                       0,                       { 0, 0, 1, 0, 0, 0, 0, 0} } },     // time
{"<q>",         {0.001,                   0,                       {(FRC){3,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric charge
{"|q|",         {3.33564095198152e-10,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric charge SI factor
{"<F>",         {0.01,                    0,                       { 1, 1,-2, 0, 0, 0, 0, 0} } },     // force
{"<m>",         {1,                       0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // mass
{"<R>",         {100,                     0,                       {-1, 0, 1, 0, 0, 0, 0, 0} } },     // electrical resistance
{"|R|",         {898755178736.818,        0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electrical resistance SI factor
{"<eps>",       {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // permittivity
{"|eps|",       {8.85418796865655e-12,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // permittivity SI factor
{"<C>",         {0.01,                    0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // capacitance
{"|C|",         {1.11265005605362e-12,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // capacitance SI factor
{"<mm>",        {1e-05,                   0,                       {(FRC){5,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // magnetic dipole moment
{"|mm|",        {0.001,                   0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // magnetic dipole moment SI factor
{"<L>",         {100,                     0,                       {-1, 0, 2, 0, 0, 0, 0, 0} } },     // inductance
{"|L|",         {898755178736.818,        0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // inductance SI factor
{"<mu>",        {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // permeability
{"|mu|",        {1.25663704e-06,          0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // permeability SI factor
{"<p_e>",       {1e-05,                   0,                       {(FRC){5,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric dipole moment
{"|p_e|",       {3.33564095198152e-12,    0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric dipole moment SI factor
{"<phi_e>",     {0.1,                     0,                       {(FRC){1,2},(FRC){1,2},-1, 0, 0, 0, 0, 0} } },     // electric potential
{"|phi_e|",     {299.792458,              0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // electric potential SI factor
