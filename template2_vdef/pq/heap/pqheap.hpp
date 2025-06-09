
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

protected:

  // Auxiliary functions

  void HeapifyUp(ulong);
  void HeapifyDown(ulong);

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
