
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : public virtual MutableLinearContainer<Data>,
public virtual ResizableContainer{

private:

protected:

  using Container::size;

  Data * elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors

  Vector(ulong); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);

  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator=(const Vector &);

  // Move assignment
  Vector & operator=(Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  bool operator!=(const Vector &) const noexcept;


  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data & operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data & Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data & Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data & Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data & Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public virtual Vector<Data>, //ereditarietà dubbi
public virtual SortableLinearContainer<Data>{

private:

protected:

  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors

  SortableVector(ulong);// A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  //Copy constructor
  SortableVector(const SortableVector &);   
  
  // Move constructor
  SortableVector(SortableVector &&); 

  /* ************************************************************************ */

  //Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator=(const SortableVector &);

  // Move assignment
  SortableVector & operator=(SortableVector &&) noexcept; 

protected:

};

/* ************************************************************************** */

}

#include "vector.cpp"
#include <stdexcept>

#endif