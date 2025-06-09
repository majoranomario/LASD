
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  MappableContainer & operator=(const MappableContainer &) = delete;

  // Move assignment
  MappableContainer & operator=(MappableContainer &&) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison of abstract types is not possible.

  // Comparison operators
  bool operator==(const MappableContainer &) const noexcept = delete; 
  bool operator!=(const MappableContainer &) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>,
virtual public PreOrderTraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  PreOrderMappableContainer & operator=(const PreOrderMappableContainer &) = delete; 

  // Move assignment
  PreOrderMappableContainer & operator=(PreOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison of abstract types is not possible.

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const noexcept = delete; 
  bool operator!=(const PreOrderMappableContainer &) const noexcept = delete ; 

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>,
virtual public PostOrderTraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  PostOrderMappableContainer & operator=(const PostOrderMappableContainer &) = delete;

  // Move assignment
  PostOrderMappableContainer & operator=(PostOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison of abstract types is not possible

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept = delete;
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
