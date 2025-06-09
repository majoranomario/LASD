#include <iostream>

/* ************************************************************************** */

#include "../../container/container.hpp"

using namespace lasd;

/* ************************************************************************** */

/*  test for Container */

void Empty(uint & testnum, uint & testerr, const Container & con, bool chk) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") The container is "
            << ((tst = con.Empty()) ? "" : "not ") << "empty: ";
  std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void Size(uint & testnum, uint & testerr, const Container & con, bool chk, ulong siz) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") The container has size "
            << con.Size() << ": ";
  std::cout << ((tst = ((con.Size() == siz) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void TestIsConsistent(uint & testnum, uint & testerr, const Container & con) {
  bool tst;
  testnum++;
  bool correct = ((con.Empty() && con.Size() == 0) || (!con.Empty() && con.Size() > 0));
  std::cout << " " << testnum << " (" << testerr << ") Check consistency between Empty() and Size(): ";
  std::cout << ((tst = correct) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */
/* Funzioni di test per ClearableContainer */

void Clear(uint & testnum, uint & testerr, ClearableContainer & con) {
  bool tst;
  testnum++;
  con.Clear();
  std::cout << " " << testnum << " (" << testerr << ") Clear() function called, container is now "
            << ((tst = con.Empty()) ? "" : "not ") << "empty: ";
  std::cout << ((tst = (tst == true)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */
/* Funzioni di test per ResizableContainer */

void Resize(uint & testnum, uint & testerr, ResizableContainer & con, ulong newSize) {
  bool tst;
  testnum++;
  con.Resize(newSize);
  std::cout << " " << testnum << " (" << testerr << ") Resize() called with " << newSize 
            << ", actual size is " << con.Size() << ": ";
  std::cout << ((tst = (con.Size() == newSize)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void ClearAfterResize(uint & testnum, uint & testerr, ResizableContainer & con, ulong initSize) {
  bool tst;
  testnum++;
  con.Resize(initSize);
  con.Clear();
  std::cout << " " << testnum << " (" << testerr << ") Resize(" << initSize << ") followed by Clear(): ";
  std::cout << ((tst = (con.Empty() && con.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void TestDoubleResize(uint & testnum, uint & testerr, ResizableContainer & con, ulong first, ulong second) {
  bool tst;
  testnum++;
  con.Resize(first);
  con.Resize(second);
  std::cout << " " << testnum << " (" << testerr << ") Double Resize to " << first << " then " << second << ": ";
  std::cout << ((tst = (con.Size() == second)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void TestResizeToSameValue(uint & testnum, uint & testerr, ResizableContainer & con, ulong value) {
  bool tst;
  testnum++;
  con.Resize(value);
  ulong before = con.Size();
  con.Resize(value);
  ulong after = con.Size();
  std::cout << " " << testnum << " (" << testerr << ") Resize to same value (" << value << "): ";
  std::cout << ((tst = (before == after)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void TestResizeToZero(uint & testnum, uint & testerr, ResizableContainer & con) {
  bool tst;
  testnum++;
  con.Resize(0);
  std::cout << " " << testnum << " (" << testerr << ") Resize to 0 empties container: ";
  std::cout << ((tst = (con.Empty() && con.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

void TestMultipleOperations(uint & testnum, uint & testerr, ResizableContainer & con) {
  bool tst;
  testnum++;
  con.Resize(10);
  con.Clear();
  con.Resize(3);
  std::cout << " " << testnum << " (" << testerr << ") Resize->Clear->Resize(3): ";
  std::cout << ((tst = (con.Size() == 3 && !con.Empty())) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

