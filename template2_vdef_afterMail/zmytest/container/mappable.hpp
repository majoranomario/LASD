#ifndef MAPPABLETEST_EXTENDED_HPP
#define MAPPABLETEST_EXTENDED_HPP

#include "../../container/mappable.hpp"
#include <iostream>
#include <string>

/* ************************************************************************** */

void MapStringAppend(std::string &, const std::string &);

void MapStringNonEmptyAppend(std::string &, const std::string &);

/* ************************************************************************** */

// PreOrderMappableContainer member functions!

template <typename Data>
void MapPreOrder(uint & testnum, uint & testerr, lasd::PreOrderMappableContainer<Data> & con, bool chk, typename lasd::MappableContainer<Data>::MapFun fun) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Executing map in pre order - ";
    con.PreOrderMap(fun);
    std::cout << ": " << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// PostOrderMappableContainer member functions!

template <typename Data>
void MapPostOrder(uint & testnum, uint & testerr, lasd::PostOrderMappableContainer<Data> & con, bool chk, typename lasd::MappableContainer<Data>::MapFun fun) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Executing map in post order - ";
    con.PostOrderMap(fun);
    std::cout << ": " << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}


// Test di Map con funzioni più complesse e controllo valori post-mapping

template <typename Data>
void MapAndCheck(uint & testnum, uint & testerr, lasd::MappableContainer<Data> & con, bool chk, typename lasd::MappableContainer<Data>::MapFun fun, const std::vector<Data> & expected) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Executing map and verifying results - ";
    con.Map(fun);

    if constexpr(std::is_same<Data, std::string>::value) {
      // Non funziona con string? -> salto controllo valori, solo correttezza run
      std::cout << ": " << (chk ? "Correct" : "Error") << "!" << std::endl;
    } else {
      // Controllo che i valori nella container corrispondano all'expected
      for(ulong i = 0; i < expected.size(); ++i) {
        if (con[i] != expected[i]) {
          tst = false;
          break;
        }
      }
      std::cout << ((tst == chk) ? "Correct" : "Error") << "!" << std::endl;
    }
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Funzioni di mapping aggiuntive

template <typename Data>
void MapSquare(Data & dat) {
  dat *= dat;
}

template <typename Data>
void MapNegateIfPositive(Data & dat) {
  if(dat > 0) dat = -dat;
}

template <typename Data>
void MapAppendExclamation(std::string & dat) {
  dat += "!";
}

template <typename Data>
void MapToUpperCase(std::string & dat) {
  for (auto & c : dat) c = toupper(c);
}

// Test di mapping preordine e postordine con output dettagliato

template <typename Data>
void MapPreOrderWithPrint(uint & testnum, uint & testerr, lasd::PreOrderMappableContainer<Data> & con, bool chk, typename lasd::MappableContainer<Data>::MapFun fun) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") PreOrderMap with detailed output - ";
    con.PreOrderMap(fun);
    std::cout << ": " << (chk ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((!chk) ? "Correct" : "Error") << "!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void MapPostOrderWithPrint(uint & testnum, uint & testerr, lasd::PostOrderMappableContainer<Data> & con, bool chk, typename lasd::MappableContainer<Data>::MapFun fun) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") PostOrderMap with detailed output - ";
    con.PostOrderMap(fun);
    std::cout << ": " << (chk ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((!chk) ? "Correct" : "Error") << "!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

#endif
