
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer & operator=(const DictionaryContainer &) = delete;

  // Move assignment
  DictionaryContainer & operator=(DictionaryContainer &&) noexcept = delete;


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer &) const noexcept = delete;
  bool operator!=(const DictionaryContainer &) const noexcept = delete;
  
  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data &) = 0; // Copy of the value
  virtual bool Insert(Data &&) = 0; // Move of the value
  virtual bool Remove(const Data &) = 0;
  
  inline virtual bool InsertAll(const TraversableContainer<Data> &); // Copy of the value; From TraversableContainer; True if all are inserted
  inline virtual bool InsertAll(MappableContainer<Data> &&); // Move of the value; From MappableContainer; True if all are inserted
  inline virtual bool RemoveAll(const TraversableContainer<Data> &); // From TraversableContainer; True if all are removed

  inline virtual bool InsertSome(const TraversableContainer<Data> &); // Copy of the value; From TraversableContainer; True if some is inserted
  inline virtual bool InsertSome(MappableContainer<Data> &&); // Move of the value; From MappableContainer; True if some is inserted
  inline virtual bool RemoveSome(const TraversableContainer<Data> &); // From TraversableContainer; True if some is removed

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~OrderedDictionaryContainer()= default;

  /* ************************************************************************ */

  // Copy assignment
  // Copy assignment of abstract types is not possible.(delete)
  OrderedDictionaryContainer & operator=(const OrderedDictionaryContainer &) = delete;

  // Move assignment (delete)
  // type operator=(argument); // Move assignment of abstract types is not possible.
  OrderedDictionaryContainer & operator=(OrderedDictionaryContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  // Comparison of abstract types is not possible.
  bool operator==(const OrderedDictionaryContainer &) = delete;
  bool operator!=(const OrderedDictionaryContainer &) = delete;

  /* ************************************************************************ */

  // Specific member functions

  // MinNRemove/MaxNRemove returns a copy of the element because it is removed from the container.
  // Returning by reference would result in a dangling reference to deallocated memory. 

  virtual const Data & Min() const = 0; // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove() = 0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() = 0; // (concrete function must throw std::length_error when empty)

  virtual const Data & Max() const = 0; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove() = 0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() = 0;// (concrete function must throw std::length_error when empty)

  virtual const Data & Predecessor(const Data &) const = 0; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data &) = 0; // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data &) = 0; // (concrete function must throw std::length_error when not found)

  virtual const Data & Successor(const Data &) const = 0; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data &) = 0; // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data &) = 0; // (concrete function must throw std::length_error when not found)

};

/* ************************************************************************** */

}

#include "dictionary.cpp"
#include <stdexcept>

#endif