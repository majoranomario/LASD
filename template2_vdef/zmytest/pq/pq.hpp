
#ifndef PQTEST_HPP
#define PQTEST_HPP

#include "../../pq/pq.hpp"
#include "../../pq/heap/pqheap.hpp"

/* ************************************************************************** */

// PQ member functions!

template <typename Data>
void Tip(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, bool chk, const Data & val) {
  testnum++;
  bool tst;
  try {
    std::cout << " " << testnum << " Tip of the priority queue with value \"" << pq.Tip() << "\": ";
    std::cout << ((tst = ((pq.Tip() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveTip(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, bool chk) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Remove tip from the priority queue: ";
    pq.RemoveTip();
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void TipNRemove(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, bool chk, const Data & val) {
  testnum++;
  bool tst;
  try {
    std::cout << " " << testnum << " TipNRemove from the priority queue with value \"" << pq.Tip() << "\": ";
    std::cout << ((tst = ((pq.TipNRemove() == val) == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Insert(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, const Data & val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Insert on the priority queue of the value \"" << val << "\": ";
    pq.Insert(val);
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Change(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, bool chk, ulong idx, const Data & val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index << \"" << idx << "\" to the value \"" << val << "\" in the priority queue: ";
    pq.Change(idx, val);
    std::cout << (chk ? "Correct" : "Error") << "!" << std::endl;
    tst = chk;
  }
  catch (std::exception & exc) {
    std::cout << exc.what() << "\": " << (!chk ? "Correct" : "Error") << "!" << std::endl;
    tst = !chk;
  }
  testerr += (1 - (uint) tst);
}

// Test Insert with rvalue
template <typename Data>
void InsertMove(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, Data && val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Move insert on the priority queue of the value \"" << val << "\": ";
    pq.Insert(std::move(val));
    std::cout << "Correct!" << std::endl;
  } catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

// Test Change with rvalue
template <typename Data>
void ChangeMove(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, ulong idx, Data && val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Move change the value at index \"" << idx << "\" to the value \"" << val << "\": ";
    pq.Change(idx, std::move(val));
    std::cout << "Correct!" << std::endl;
  } catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

// Test Empty
template <typename Data>
void EmptyTest(uint & testnum, uint & testerr, const lasd::PQ<Data> & pq, bool expected) {
  testnum++;
  bool tst;
  std::cout << " " << testnum << " Check if priority queue is empty: ";
  tst = (pq.Empty() == expected);
  std::cout << (tst ? "Correct!" : "Error!") << std::endl;
  testerr += (1 - (uint)tst);
}

// Test copy constructor
template <typename Data>
void CopyConstructorTest(uint & testnum, uint & testerr, const lasd::PQ<Data> & pq) {
  testnum++;
  bool tst = true;
  try {
    lasd::PQHeap<Data> copy(pq);
    std::cout << " " << testnum << " Copy constructor: Correct!" << std::endl;
  } catch (std::exception & exc) {
    std::cout << " " << testnum << " Copy constructor error: \"" << exc.what() << "\"" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

// Test move constructor
template <typename Data>
void MoveConstructorTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq) {
  testnum++;
  bool tst = true;
  try {
    lasd::PQHeap<Data> copy(std::move(pq));
    std::cout << " " << testnum << " Move constructor: Correct!" << std::endl;
  } catch (std::exception & exc) {
    std::cout << " " << testnum << " Move constructor error: \"" << exc.what() << "\"" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

// Test constructor from TraversableContainer
template <typename Data>
void ConstructFromContainerTest(uint & testnum, uint & testerr, const lasd::TraversableContainer<Data> & cont) {
  testnum++;
  bool tst = true;
  try {
    lasd::PQHeap<Data> pq(cont);
    std::cout << " " << testnum << " Construct from container: Correct!" << std::endl;
  } catch (std::exception & exc) {
    std::cout << " " << testnum << " Constructor error: \"" << exc.what() << "\"" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void TipEmptyTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq) {
  testnum++;
  try {
    pq.Tip();
    std::cout << " " << testnum << " Tip on empty PQ: Error!" << std::endl;
    testerr++;
  } catch (std::length_error&) {
    std::cout << " " << testnum << " Tip on empty PQ: Correct!" << std::endl;
  }
}

template <typename Data>
void RemoveTipEmptyTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq) {
  testnum++;
  try {
    pq.RemoveTip();
    std::cout << " " << testnum << " RemoveTip on empty PQ: Error!" << std::endl;
    testerr++;
  } catch (std::length_error&) {
    std::cout << " " << testnum << " RemoveTip on empty PQ: Correct!" << std::endl;
  }
}

template <typename Data>
void TipNRemoveEmptyTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq) {
  testnum++;
  try {
    pq.TipNRemove();
    std::cout << " " << testnum << " TipNRemove on empty PQ: Error!" << std::endl;
    testerr++;
  } catch (std::length_error&) {
    std::cout << " " << testnum << " TipNRemove on empty PQ: Correct!" << std::endl;
  }
}

template <typename Data>
void SizeTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, ulong expected) {
  testnum++;
  bool correct = (pq.Size() == expected);
  std::cout << " " << testnum << " Size == " << expected << ": " << (correct ? "Correct!" : "Error!") << std::endl;
  testerr += !correct;
}

template <typename Data>
void ChangeInvalidIndexTest(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, ulong idx, const Data & val) {
  testnum++;
  try {
    pq.Change(idx, val);
    std::cout << " " << testnum << " Change on invalid index: Error!" << std::endl;
    testerr++;
  } catch (std::out_of_range&) {
    std::cout << " " << testnum << " Change on invalid index: Correct!" << std::endl;
  }
}





/* ************************************************************************** */

#endif
