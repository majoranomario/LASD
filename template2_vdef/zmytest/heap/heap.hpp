
#ifndef HEAPMYTEST_HPP
#define HEAPMYTEST_HPP

#include "../../heap/heap.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

// Heap member functions!

template <typename Data>
void IsHeap(uint & testnum, uint & testerr, const lasd::Heap<Data> & con, bool chk) {
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") The structure is" << ((tst = con.IsHeap()) ? " " : " not ") << "a heap: ";
  std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void IsHeapSorted(uint & testnum, uint & testerr, const lasd::LinearContainer<Data> & con, bool chk) {
  bool tst;
  testnum++;
  bool sorted = true;
  ulong size = con.Size();

  for (ulong i = 0; i < size - 1; ++i) {
    if (con[i] > con[i + 1]) {
      sorted = false;
      break;
    }
  }

  std::cout << " " << testnum << " (" << testerr << ") The container is" 
            << (sorted ? " " : " not ") << "sorted: ";
  
  tst = (sorted == chk);
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}



/* ************************************************************************** */

#endif
