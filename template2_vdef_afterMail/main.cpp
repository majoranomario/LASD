#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "LASD Libraries 2025" << std::endl;

  int option = 0;

  std::cout << "Choose which test to run:" << std::endl;
  std::cout << "1. Run official test (lasdtest)" << std::endl;
  std::cout << "2. Run personal test (mytest)" << std::endl;
  std::cout << "Option: ";
  std::cin >> option;

  std::cout << std::endl;

  switch (option) {
    case 1:
      lasdtest();
      break;
    case 2:
      mytest();
      break;
    default:
      std::cout << "Invalid option. Exiting program." << std::endl;
      break;
  }

  return 0;
}
