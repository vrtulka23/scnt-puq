#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <exception>

#include "../../src/quantity.h"
#include "../../src/nostd/nostd.h"
#include "../../src/systems/systems.h"
#include "../../src/calc/calc.h"

void display_info(std::string expr);
void display_lists(std::deque<std::string>& convert);
  
#endif // MAIN_H
