
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* for use ulong on all os*/
#include <sys/types.h>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

protected:

  ulong size = 0;

  /* ************************************************************************ */

  // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container & operator=(const Container &) = delete;

  // Move assignment
  Container & operator=(Container &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators

  bool operator==(const Container &) const noexcept = delete;  // Comparison of abstract types is not possible (delete)
  bool operator!=(const Container &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const noexcept{
    return size==0;
  }

  inline virtual ulong Size() const noexcept{
    return size;
  }

};

/* ************************************************************************** */

class ClearableContainer : virtual public Container{

private:

protected:

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer & operator=(const ClearableContainer &) = delete;

  // Move assignment
  ClearableContainer & operator=(ClearableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const ClearableContainer &) const noexcept = delete;  // Comparison of abstract types is not possible (delete)
  bool operator!=(const ClearableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer{

private:

protected:

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer & operator=(const ResizableContainer &) = delete;

  // Move assignment
  ResizableContainer & operator=(ResizableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators

  bool operator==(const ResizableContainer &) const noexcept = delete; // Comparison of abstract types is not possible (delete)
  bool operator!=(const ResizableContainer &) const noexcept = delete;
  
  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(ulong) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  

  inline void Clear() override { // Override ClearableContainer member
    Resize(0);
  }


};

/* ************************************************************************** */

}

#endif
