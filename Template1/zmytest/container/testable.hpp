#ifndef TESTABLETEST_EXTENDED_HPP
#define TESTABLETEST_EXTENDED_HPP

#include "../../container/testable.hpp"
#include <iostream>
#include <string>

/* ************************************************************************** */

// TestableContainer member functions!

template <typename Data>
void Exists(uint & testnum, uint & testerr, const lasd::TestableContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Data \"" << val << "\" " << ((tst = con.Exists(val)) ? "does" : "does not") << " exist: ";
  std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}


// Test per la funzione Exists con output dettagliato

template <typename Data>
void ExistsDetailed(uint & testnum, uint & testerr, const lasd::TestableContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Checking existence of \"" << val << "\"... ";
  try {
    tst = con.Exists(val);
    std::cout << (tst ? "Found" : "Not Found") << ": ";
    std::cout << ((tst == chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "Exception: \"" << exc.what() << "\" - ";
    std::cout << ((chk == false) ? "Correct" : "Error") << "!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)(tst == chk));
}

/* ************************************************************************** */

#endif
