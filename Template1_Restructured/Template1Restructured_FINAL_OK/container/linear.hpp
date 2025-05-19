
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"
#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
virtual public PostOrderTraversableContainer<Data>{

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  LinearContainer & operator=(const LinearContainer &) = delete;

  // Move assignment
  LinearContainer & operator=(LinearContainer &&) noexcept = delete;

  /* ************************************************************************ */
  
  // Comparison operators

  inline bool operator==(const LinearContainer &) const noexcept;
  inline bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator[](ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data & Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual const Data & Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>,
virtual public PreOrderMappableContainer<Data>,
virtual public PostOrderMappableContainer<Data>{

private:

protected:

  using Container::size;

  // Bring the const version of operator[] from LinearContainer into scope.
  // Without this, the non-const overload defined below would hide the const version,
  // potentially leading to compiler warnings and incorrect overload resolution.

  using LinearContainer<Data>::operator[];
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;

public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  MutableLinearContainer & operator=(const MutableLinearContainer &) = delete;

  // Move assignment
  MutableLinearContainer & operator=(MutableLinearContainer &&) = delete;

  /* ************************************************************************ */

  //Comparison operators Inherited from LinearContainer

  /* ************************************************************************ */

  // Specific member functions

  virtual Data & operator[](ulong) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual Data & Front(); // (mutable version; concrete function must throw std::length_error when empty)

  virtual Data & Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data>{

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy/Movew assignment of abstract types is not possible.

  // Copy assignment
  SortableLinearContainer & operator=(const SortableLinearContainer &) = delete;

  // Move assignment
  SortableLinearContainer & operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators Inherited from LinearContainer
  
  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() noexcept;

protected:

  // Auxiliary member functions

  void QuickSort(ulong p, ulong r) noexcept;
  ulong Partition(ulong p, ulong r) noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"
#include <stdexcept>

#endif