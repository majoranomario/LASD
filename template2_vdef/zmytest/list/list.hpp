#ifndef LIST_EXTRA_TESTS_HPP
#define LIST_EXTRA_TESTS_HPP

#include "../../list/list.hpp"
#include <iostream>
#include <stdexcept>

/* ************************************************************************** */

template <typename Data>
void InsertAtFront(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insert at the front of the list the value \"" << val << "\": ";
    lst.InsertAtFront(val);
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveFromFront(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Remove from the list of \"" << lst.Front() << "\": ";
    lst.RemoveFromFront();
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
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
void FrontNRemove(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") FrontNRemove from the list of \"" << lst.Front() << "\": ";
    std::cout << ((tst = ((lst.FrontNRemove() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
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
void InsertAtBack(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insert at the back of the list the value \"" << val << "\": ";
    lst.InsertAtBack(val);
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveFromBack(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Remove from the list of \"" << lst.Back() << "\": ";
    lst.RemoveFromBack();
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
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
void BackNRemove(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") BackNRemove from the list of \"" << lst.Back() << "\": ";
    std::cout << ((tst = ((lst.BackNRemove() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
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
void EqualList(uint & testnum, uint & testerr, const lasd::List<Data> & lst1, const lasd::List<Data> & lst2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two lists are " << ((tst = (lst1 == lst2)) ? "" : "not ") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualList(uint & testnum, uint & testerr, const lasd::List<Data> & lst1, const lasd::List<Data> & lst2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two lists are " << ((tst = (lst1 != lst2)) ? "not " : "") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void FrontTest(uint & testnum, uint & testerr, const lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Front element should be \"" << val << "\": ";
    std::cout << ((tst = ((lst.Front() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\nWrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void BackTest(uint & testnum, uint & testerr, const lasd::List<Data> & lst, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Back element should be \"" << val << "\": ";
    std::cout << ((tst = ((lst.Back() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\nWrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void AccessTest(uint & testnum, uint & testerr, const lasd::List<Data> & lst, bool chk, ulong index, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Access element at index " << index << " should be \"" << val << "\": ";
    std::cout << ((tst = ((lst[index] == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::out_of_range & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\nWrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void ClearTest(uint & testnum, uint & testerr, lasd::List<Data> & lst) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Clear the list: ";
    lst.Clear();
    tst = (lst.Empty() && lst.Size() == 0);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  } catch (std::exception & exc) {
    tst = false;
    std::cout << "\nException during Clear: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void SizeTest(uint & testnum, uint & testerr, const lasd::List<Data> & lst, ulong expectedSize) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") List size should be " << expectedSize << ": ";
    tst = (lst.Size() == expectedSize);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  } catch (std::exception & exc) {
    tst = false;
    std::cout << "\nException during Size(): " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void EmptyTest(uint & testnum, uint & testerr, const lasd::List<Data> & lst, bool expectedEmpty) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") List should be " << (expectedEmpty ? "empty" : "not empty") << ": ";
    tst = (lst.Empty() == expectedEmpty);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  } catch (std::exception & exc) {
    tst = false;
    std::cout << "\nException during Empty(): " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

#endif
