#include <iostream>

#include "../../src/quantity.h"

int main(int argc, char * argv[]) {

  if (argc!=3) {
    std::cout << "This program needs two expressions: initial unit and a conversion unit" << std::endl;
    exit(0);
  }
  
  puq::Quantity a(argv[1]);
  a = a.convert(argv[2]);
  std::cout << std::endl;
  std::cout << "Conversion result:" << std::endl;
  std::cout << argv[1] << " -> " << a.to_string() << std::endl;
  std::cout << std::endl;
  
}
