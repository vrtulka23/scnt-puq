/*
 * Do not modify this file!
 * This file can be updated using 'dmap' executable.
 * 
 * Unit system:  Units for special relativity (SRU)
 * Last update:  Tue Sep 24 21:46:03 2024
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
{"[c]",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // speed of light
{"[#kap_0]",    {1.1126500562e-13,        0,                       {-3,-1, 4, 0, 2, 0, 0, 0} } },     // permittivity
{"[#k_B]",      {1.380649e-20,            0,                       { 2, 1,-2,-1, 0, 0, 0, 0} } },     // Boltzmann const.
{"[#c]",        {299792458,               0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // speed of light
{"[#G]",        {6.6743e-14,              1.5e-18,                 { 3,-1,-2, 0, 0, 0, 0, 0} } },     // grav. const.
{"[#hbar]",     {1.054571817e-31,         0,                       { 2, 1,-1, 0, 0, 0, 0, 0} } },     // reduced Pl. con.
{"[#m_e]",      {9.1093837139e-28,        2.8e-37,                 { 0, 1, 0, 0, 0, 0, 0, 0} } },     // electron mass
{"[#e]",        {1.602176634e-19,         0,                       { 0, 0, 1, 0, 1, 0, 0, 0} } },     // elem. charge
{"<rho_E>",     {1000,                    0,                       {-3, 1, 0, 0, 0, 0, 0, 0} } },     // energy density
{"|rho_E|",     {8.98755178736818e+16,    0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // energy density SI factor
{"<a>",         {1,                       0,                       {-1, 0, 0, 0, 0, 0, 0, 0} } },     // acceleration
{"|a|",         {8.98755178736818e+16,    0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // acceleration SI factor
{"<F>",         {1000,                    0,                       {-1, 1, 0, 0, 0, 0, 0, 0} } },     // force
{"|F|",         {8.98755178736818e+16,    0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // force SI factor
{"<m>",         {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // mass
{"<p_mom>",     {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // momentum
{"|p_mom|",     {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // momentum SI factor
{"<v>",         {1,                       0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity
{"|v|",         {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // velocity SI factor
{"<E>",         {1000,                    0,                       { 0, 1, 0, 0, 0, 0, 0, 0} } },     // energy
{"|E|",         {8.98755178736818e+16,    0,                       { 1, 0,-1, 0, 0, 0, 0, 0} } },     // energy SI factor
{"<t>",         {1,                       0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // time
{"|t|",         {3.33564095198152e-09,    0,                       {-2, 0, 2, 0, 0, 0, 0, 0} } },     // time SI factor
{"<L_ome>",     {1000,                    0,                       { 1, 1, 0, 0, 0, 0, 0, 0} } },     // angular momentum
{"|L_ome|",     {299792458,               0,                       { 0, 0, 0, 0, 0, 0, 0, 0} } },     // angular momentum SI factor
{"<l>",         {1,                       0,                       { 1, 0, 0, 0, 0, 0, 0, 0} } },     // length
