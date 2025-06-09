
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  TraversableContainer & operator=(const TraversableContainer &) = delete;

  // Move assignment
  TraversableContainer & operator=(TraversableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer &) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const TraversableContainer &) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  // TraverseFun does not require a template because the function signature is fixed:
  // it always takes a 'const Data&' and returns nothing (void).
  // FoldFun, on the other hand, must be a template because it depends on the type
  // of the accumulator, which varies depending on the specific use case.

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>,Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  PreOrderTraversableContainer & operator=(const PreOrderTraversableContainer &) = delete;

  // Move assignment
  PreOrderTraversableContainer & operator=(PreOrderTraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison of abstract types might be possible.

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer &) const noexcept = delete; 
  bool operator!=(const PreOrderTraversableContainer &) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>,Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy/Move assignment of abstract types is not possible.

  // Copy assignment
  PostOrderTraversableContainer & operator=(const PostOrderTraversableContainer &) = delete;

  // Move assignment
  PostOrderTraversableContainer & operator=(PostOrderTraversableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison of abstract types might be possible.

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer &) const noexcept = delete;
  bool operator!=(const PostOrderTraversableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>,Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
