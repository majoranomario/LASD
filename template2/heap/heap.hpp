
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,
virtual public ClearableContainer{

private:

protected:

public:

  //Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap & operator=(const Heap &); // Copy assignment of abstract types is not possible.

  // Move assignment
  Heap & operator=(Heap &&); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  bool IsHeap(Heap) specifiers;

  bool Heapify(argument) specifiers;

};

/* ************************************************************************** */

}

#endif
