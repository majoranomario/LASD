
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>,
protected HeapVec<Data>{

private:

protected:

  using Container::size;

public:

  // Default constructor
  PQHeap();

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data> &); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data> &&); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap<Data> &);

  // Move constructor
  PQHeap(PQHeap<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap & operator=(const PQHeap<Data> &);

  // Move assignment
  PQHeap & operator=(PQHeap<Data> &&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data & Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data &) override; // Override PQ member (Copy of the value)
  void Insert(Data &&) noexcept override; // Override PQ member (Move of the value)

  void Change(ulong,const Data &) override; // Override PQ member (Copy of the value)
  void Change(ulong,Data &&) override; // Override PQ member (Move of the value)

  // Specific member functions (inherited from ClearableContainer (HeapVec))

  using HeapVec<Data>::Clear;

  // Specific member functions (inherited from LinearContainer)

  //non mutable versions

  /*As per the template design, PQHeap inherits from LinearContainer, which provides only the non-mutable implementations of
   the methods Front, Back, and operator[]. 
   These methods have been made public because they serve as interface methods.
  However, for the internal implementation of the PQHeap data structure, a mutable version of operator[] is used, 
  which is inherited from HeapVec. This allows PQHeap to modify elements internally while still exposing the read-only 
  interface inherited from LinearContainer.*/

  using LinearContainer<Data>::operator[]; 
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;


protected:

  // Auxiliary functions

  void HeapifyUp(ulong);
  void HeapifyDown(ulong);


};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
