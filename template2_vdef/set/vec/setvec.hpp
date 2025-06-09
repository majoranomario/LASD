
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
virtual public ResizableContainer, protected Vector<Data> {

private:

protected:

  using Container::size;
  using Vector<Data>::elements;
  ulong capacity;
  ulong head;
  ulong tail;
  
  using Vector<Data>::operator[];
  using Vector<Data>::Front;
  using Vector<Data>::Back;


public:

  // Default constructor
  SetVec();

  /* ************************************************************************ */

  // Specific constructors

  SetVec(ulong); 
  SetVec(const TraversableContainer<Data> & );
  SetVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec<Data> &);

  // Move constructor
  SetVec(SetVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetVec<Data> & operator=(const SetVec &);

  // Move assignment
  SetVec<Data> & operator=(SetVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec<Data> &) const noexcept;
  bool operator!=(const SetVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  const Data & Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data & Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data & Predecessor(const Data &) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  const Data & Successor(const Data &) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void  RemoveSuccessor(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)
  
  const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  
  const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

protected:

  // Auxiliary functions
  ulong BinarySearch(const Data&, ulong, ulong) const;
  
  void InsertAtPosition(ulong, const Data& );
  void InsertAtPosition(ulong, Data&&);
  void RemoveAtPosition(ulong);

  Data DetachPredecessor(const Data &);
  Data DetachSuccessor(const Data &);

};

/* ************************************************************************** */

}

#include "setvec.cpp"
#include <stdexcept>

#endif