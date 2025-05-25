#ifndef LINEARTEST_EXTENDED_HPP
#define LINEARTEST_EXTENDED_HPP

#include "../../container/linear.hpp"
#include <iostream>
#include <stdexcept>

/* ************************************************************************** */

template <typename Data>
void EqualLinear(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con1, const lasd::LinearContainer<Data> & con2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two linear containers are " << ((tst = (con1 == con2)) ? "" : "not ") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualLinear(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con1, const lasd::LinearContainer<Data> & con2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two linear containers are " << ((tst = (con1 != con2)) ? "not " : "") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void GetAt(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con, bool chk, const ulong & ind, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Get of the linear container at index \"" << ind << "\" with value \"" << con[ind] << "\": ";
    std::cout << ((tst = ((con[ind] == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::out_of_range & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void GetFront(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The front of the linear container is \"" << con.Front() << "\": ";
    std::cout << ((tst = ((con.Front() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void GetBack(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The back of the linear container is \"" << con.Back() << "\": ";
    std::cout << ((tst = ((con.Back() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// MutableLinearContainer member functions!

template <typename Data>
void SetAt(uint & testnum, uint & testerr, lasd::MutableLinearContainer<Data> & con, bool chk, const ulong & ind, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Set of the linear container at index \"" << ind << "\" with value \"" << val << "\": ";
    con[ind] = val;
    std::cout << ((tst = ((con[ind] == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::out_of_range & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void SetFront(uint & testnum, uint & testerr, lasd::MutableLinearContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Setting the front of the linear container to \"" << val << "\": ";
    con.Front() = val;
    std::cout << ((tst = ((con.Front() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void SetBack(uint & testnum, uint & testerr, lasd::MutableLinearContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Setting the back of the linear container to \"" << val << "\": ";
    con.Back() = val;
    std::cout << ((tst = ((con.Back() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

template <typename Data>
void EqualLinearEmpty(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con1, const lasd::LinearContainer<Data> & con2) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Equal operator on empty containers: ";
    tst = (con1 == con2);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (...) {
    std::cout << "Exception caught: Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualLinearDifferentSizes(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con1, const lasd::LinearContainer<Data> & con2) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Non-equal operator on containers with different sizes: ";
    tst = (con1 != con2);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (...) {
    std::cout << "Exception caught: Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// Test dell'accesso agli elementi con indice fuori range

template <typename Data>
void GetAtOutOfRange(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con, ulong ind) {
  bool tst = false;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") GetAt with index " << ind << ": ";
    Data val = con[ind]; // volatile per evitare ottimizzazioni
    std::cout << "Error (no exception)!" << std::endl;
  }
  catch (const std::out_of_range & exc) {
    std::cout << "Correct (caught out_of_range)" << std::endl;
    tst = true;
  }
  catch (...) {
    std::cout << "Error (wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// Test di Front() e Back() su container vuoto

template <typename Data>
void GetFrontEmpty(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con) {
  bool tst = false;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Front() on empty container: ";
    volatile Data val = con.Front();
    std::cout << "Error (no exception)!" << std::endl;
  }
  catch (const std::length_error & exc) {
    std::cout << "Correct (caught length_error)" << std::endl;
    tst = true;
  }
  catch (...) {
    std::cout << "Error (wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void GetBackEmpty(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con) {
  bool tst = false;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Back() on empty container: ";
    volatile Data val = con.Back();
    std::cout << "Error (no exception)!" << std::endl;
  }
  catch (const std::length_error & exc) {
    std::cout << "Correct (caught length_error)" << std::endl;
    tst = true;
  }
  catch (...) {
    std::cout << "Error (wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// Test di modifica degli elementi in MutableLinearContainer con indici validi e invalidi

template <typename Data>
void SetAtValid(uint & testnum, uint & testerr, lasd::MutableLinearContainer<Data> & con, ulong ind, const Data & val) {
  bool tst = false;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetAt valid index " << ind << ": ";
    con[ind] = val;
    tst = (con[ind] == val);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (...) {
    std::cout << "Error (exception caught)!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void SetAtInvalid(uint & testnum, uint & testerr, lasd::MutableLinearContainer<Data> & con, ulong ind, const Data & val) {
  bool tst = false;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetAt invalid index " << ind << ": ";
    con[ind] = val;
    std::cout << "Error (no exception)!" << std::endl;
  }
  catch (const std::out_of_range & exc) {
    std::cout << "Correct (caught out_of_range)" << std::endl;
    tst = true;
  }
  catch (...) {
    std::cout << "Error (wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// Test delle funzioni Map e Traverse (immutabili e mutabili)

template <typename Data>
void TestTraverse(uint & testnum, const lasd::LinearContainer<Data> & con) {
  testnum++;
  std::cout << " " << testnum << " Traverse container elements: ";
  try {
    con.Traverse([](const Data& val) { std::cout << val << " "; });
    std::cout << std::endl << "Correct!" << std::endl;
  }
  catch (...) {
    std::cout << "Error (exception in Traverse)!" << std::endl;
  }
}

template <typename Data>
void TestMap(uint & testnum, lasd::MutableLinearContainer<Data> & con, Data addValue) {
  testnum++;
  std::cout << " " << testnum << " Map adding value to container elements: ";
  try {
    con.Map([addValue](Data & val) { val = val + addValue; });
    std::cout << "Correct!" << std::endl;
  }
  catch (...) {
    std::cout << "Error (exception in Map)!" << std::endl;
  }
}

/* ************************************************************************** */

#endif
