#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <exception>

#include "../../src/quantity.h"
#include "../../src/nostd.h"
#include "../../src/lists/lists.h"

void display_unit_systems();
void display_prefixes();
void display_base_units();
void display_derived_units();
void display_constants();
void display_quantities();
#ifdef UNITS_TEMPERATURES
void display_temperature_units();
#endif
#ifdef UNITS_LOGARITHMIC
void display_logarithmic_units();
#endif
void display_info(std::string expr);
  
#endif // MAIN_H
