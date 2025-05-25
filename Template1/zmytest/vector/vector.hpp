#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

#include "../../vector/vector.hpp"
#include <iostream>

/* ************************************************************************** */

template <typename Data>
void EqualVector(uint & testnum, uint & testerr, const lasd::Vector<Data> & vec1, const lasd::Vector<Data> & vec2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two vectors are " << ((tst = (vec1 == vec2)) ? "" : "not ") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualVector(uint & testnum, uint & testerr, const lasd::Vector<Data> & vec1, const lasd::Vector<Data> & vec2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two vectors are " << ((tst = (vec1 != vec2)) ? "not " : "") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void AccessOperator(uint & testnum, uint & testerr, const lasd::Vector<Data> & vec, ulong index, bool chk, const Data & expected) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Access operator at index " << index << ": ";
    const Data & val = vec[index];
    std::cout << "value is \"" << val << "\": ";
    std::cout << ((tst = ((val == expected) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void FrontBack(uint & testnum, uint & testerr, const lasd::Vector<Data> & vec, bool chk, const Data & expectedFront, const Data & expectedBack) {
  bool tst = true;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Front element: ";
    const Data & front = vec.Front();
    std::cout << "\"" << front << "\" ";
    tst &= ((front == expectedFront) == chk);
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": ";
    tst &= !chk;
  }
  try {
    std::cout << "Back element: ";
    const Data & back = vec.Back();
    std::cout << "\"" << back << "\": ";
    tst &= ((back == expectedBack) == chk);
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": ";
    tst &= !chk;
  }
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

// Test Resize functionality
template <typename Data>
void ResizeVector(uint & testnum, uint & testerr, lasd::Vector<Data> & vec, ulong newSize, bool chk, const lasd::Vector<Data> & expectedVec) {
  bool tst;
  testnum++;
  try {
    vec.Resize(newSize);
    tst = (vec == expectedVec) == chk;
    std::cout << " " << testnum << " (" << testerr << ") Resize vector to size " << newSize << ": " << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Test Clear functionality
template <typename Data>
void ClearVector(uint & testnum, uint & testerr, lasd::Vector<Data> & vec, bool chk) {
  bool tst;
  testnum++;
  try {
    vec.Clear();
    tst = (vec.Size() == 0) == chk;
    std::cout << " " << testnum << " (" << testerr << ") Clear vector: " << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Test modification of element using non-const operator[]
template <typename Data>
void ModifyElement(uint & testnum, uint & testerr, lasd::Vector<Data> & vec, ulong index, const Data & newValue, bool chk, const Data & expectedValue) {
  bool tst;
  testnum++;
  try {
    vec[index] = newValue;
    tst = (vec[index] == expectedValue) == chk;
    std::cout << " " << testnum << " (" << testerr << ") Modify element at index " << index << ": " << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Test Copy Constructor
template <typename Data>
void CopyConstructorTest(uint & testnum, uint & testerr, const lasd::Vector<Data> & original, bool chk) {
  bool tst;
  testnum++;
  try {
    lasd::Vector<Data> copy(original);
    tst = (copy == original) == chk;
    std::cout << " " << testnum << " (" << testerr << ") Copy constructor creates equal vector: " << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Test Move Constructor
template <typename Data>
void MoveConstructorTest(uint & testnum, uint & testerr, lasd::Vector<Data> && movable, const lasd::Vector<Data> & expectedAfterMove, bool chk) {
  bool tst;
  testnum++;
  try {
    lasd::Vector<Data> moved(std::move(movable));
    tst = (moved == expectedAfterMove) == chk;
    std::cout << " " << testnum << " (" << testerr << ") Move constructor moves correctly: " << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch(std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

// Test access out of range throws exception
template <typename Data>
void AccessOutOfRange(uint & testnum, uint & testerr, const lasd::Vector<Data> & vec, ulong index, bool chk) {
  bool tst;
  testnum++;
  try {
    (void) vec[index]; // access to trigger exception if out of range
    std::cout << " " << testnum << " (" << testerr << ") Access out of range at index " << index << ": ";
    std::cout << ((tst = !chk) ? "Error" : "Correct") << "!" << std::endl; // if no exception and chk=true -> error
  }
  catch (std::out_of_range & exc) {
    std::cout << "Caught std::out_of_range: " << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (...) {
    std::cout << "Caught unexpected exception: Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

#endif
