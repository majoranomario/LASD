
namespace lasd {

/* ************************************************************************** */

// Specific constructors (Vector)

// 'inline' is not strictly necessary for constructors.
// While you can use 'inline', it is not typical for constructors, especially when they involve dynamic memory allocation.
// 'inline' is generally used for short functions or those defined in header files to avoid function call overhead.

// In this case, the constructor's logic involves dynamic memory allocation,
// so marking it 'inline' doesn't provide significant performance benefits

template<typename Data>
Vector<Data>::Vector(ulong newsize){
  size = newsize;
  elements = (newsize == 0) ? nullptr : new Data[size] {};
} 

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & container) : Vector{container.Size()} {
  ulong i = 0;
  container.Traverse(
    [this, &i](const Data & data){
      elements[i++] = data;
    }
  );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && container) : Vector(container.Size()) {
  ulong i = 0;
  container.Map(
    [this, &i](Data & data) {
      elements[i++] = std::move(data);
    }
  );
}

/* ************************************************************************** */

// Copy constructor (Vector)

template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vector){
  size = vector.size; //è lo stesso di usare .Size() ?
  elements = new Data[size];
  std::copy(vector.elements,vector.elements + size, elements);
}

// Move constructor (Vector)
template<typename Data>
Vector<Data>::Vector(Vector<Data> && vector) noexcept {
  std::swap(size, vector.size);
  std::swap(elements, vector.elements);
}

/* ************************************************************************** */

// Destructor (Vector)
template<typename Data>
Vector<Data>::~Vector() {
  delete[] elements;
}

/* ************************************************************************** */

//no heap using, no possible memory leaks

// Copy assignment (Vector)

template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & vector) {
  if(this != &vector) {
    Vector<Data> tmp(vector); // copy constructor
    std::swap(*this, tmp);    // efficient swap
  } 
  return *this;
}

// Move assignment (Vector)

template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && vector) noexcept {
  std::swap(size, vector.size);
  std::swap(elements, vector.elements);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (Vector)

template<typename Data>
bool Vector<Data>::operator==(const Vector & vector) const noexcept {
  if(this->size != vector.size) {
    return false;
  }

  for (ulong i = 0; i < size; ++i) {
    if (elements[i] != vector.elements[i]) {
      return false;
    }
  }

  return true;
}

template<typename Data>
bool Vector<Data>::operator!=(const Vector & vector) const noexcept {
  return !(this->operator==(vector));
}

/* ************************************************************************** */

// Specific member functions (inherited from MutableLinearContainer)

template<typename Data>
Data & Vector<Data>::operator[](ulong i) {
  return const_cast<Data &>(
    static_cast<const Vector<Data> &>(*this)[i]
  );
}

template<typename Data>
Data & Vector<Data>::Front(){
  return const_cast<Data &>(
    static_cast<const Vector<Data> &>(*this).Front()
  );
}

template<typename Data>
Data & Vector<Data>::Back(){
  return const_cast<Data &>(
    static_cast<const Vector<Data> &>(*this).Back()
  );
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template<typename Data>
const Data & Vector<Data>::operator[](ulong i) const {
  if(i < size){
    return elements[i];
  }
  else{
    throw std::out_of_range("Access index out of range");
  }
}

template<typename Data>
const Data & Vector<Data>::Front() const {
  if(size != 0){
    return elements[0];
  }
  else{
    throw std::length_error("Access to an empty vector");
  }
}

template<typename Data>
const Data & Vector<Data>::Back() const {
  if(size != 0){
    return elements[size-1];
  }
  else{
    throw std::length_error("Access to an empty vector");
  }
}

/* ************************************************************************ */

// Specific member function (inherited from ResizableContainer)

template<typename Data>
void Vector<Data>::Resize(const ulong newSize) {
  if (newSize == 0) {
    Clear();
    return;
  }

  if (size == newSize) return;

  Data * newElements = new Data[newSize] {};  // Zero-initialized

  ulong minSize = (size < newSize) ? size : newSize;

  for (ulong i = 0; i < minSize; ++i) {
    newElements[i] = std::move(elements[i]);
  }

  delete[] elements;
  elements = newElements;
  size = newSize;
}

/* ************************************************************************ */

// Specific member function (inherited from ClearableContainer)

template<typename Data>
void Vector<Data>::Clear() {
  delete[] elements;
  elements = nullptr;
  size = 0;
}

/* ************************************************************************ */

// Specific constructors (SortableVector)

template<typename Data>
SortableVector<Data>::SortableVector(ulong newSize) : Vector<Data>(newSize) {}

template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & container) : Vector<Data>(container) {}

template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && container) : Vector<Data>(std::move(container)) {}

/* ************************************************************************ */

//Copy constructor

template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector & vector) : Vector<Data>(vector) {}

// Move constructor

template<typename Data>
SortableVector<Data>::SortableVector(SortableVector && vector) : Vector<Data>(std::move(vector)) {}

/* ************************************************************************ */

// Copy assignment (SortableVector)

template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & vector) {
  Vector<Data>::operator=(vector);
  return *this;
}

// Move assignment (SortableVector)

template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vector) noexcept {
  Vector<Data>::operator=(std::move(vector));
  return *this;
}

/* ************************************************************************ */
}