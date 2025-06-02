
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>,
protected Vector<Data>{

private:

protected:

  using Container::size;
  using Vector<Data>::elements;

public:

  // Default constructor
  HeapVec();

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data> &); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data> &&) ; // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec<Data> &);

  // Move constructor
  HeapVec(HeapVec<Data>  &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec & operator=(const HeapVec<Data> &);

  // Move assignment
  HeapVec & operator=(HeapVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec<Data> &) const noexcept;
  bool operator!=(const HeapVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override; // Override Heap member
  void Heapify() noexcept override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

  /* ************************************************************************ */


protected:

  // Auxiliary functions, if necessary!

  void Heapify(ulong,ulong) noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
