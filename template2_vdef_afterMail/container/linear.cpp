
namespace lasd {

/* ************************************************************************** */

// Comparison operators (LinearContainer)

template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer & container) const noexcept {
    if(size != container.size){
        return false;
    }

    // Use pre-increment (++i) instead of post-increment (i++) as a general best practice.
    // Although the difference is negligible for primitive types like ulong,
    // pre-increment avoids unnecessary temporary copies and is more efficient
    // for user-defined types such as iterators or custom objects.

    for(ulong i = 0; i < size; ++i){
        if(this->operator[](i) != container.operator[](i)) { 
            return false;
        }
    }

    return true;
}

template<typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & container) const noexcept {
    return !(this->operator==(container)); 
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) 

template<typename Data>
inline const Data & LinearContainer<Data>::Front() const {
    return this->operator[](0);
}

template<typename Data>
inline const Data & LinearContainer<Data>::Back() const {
    return this->operator[](size -1);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from TraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun function) const {
  PreOrderTraverse(function);
}

/* ************************************************************************** */

// Specific member functions (inherited from PreOrderTraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun function) const {
    for(ulong i = 0; i < size; ++i){
        function(this->operator[](i));
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun function) const {
    ulong i = size;
    while (i > 0) {
        function(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member functions (MutableLinearContainer)

template<typename Data>
inline Data & MutableLinearContainer<Data>::Front() {
    return this->operator[](0);
}

template<typename Data>
inline Data & MutableLinearContainer<Data>::Back() {
    return this->operator[](size-1);
}

/* ************************************************************************ */

// Specific member function (inherited from MappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun function){
    PreOrderMap(function);
}

/* ************************************************************************ */

// Specific member function (inherited from PreOrderMappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun function) {
    for(ulong i=0;i < size;++i){
        function(this->operator[](i));
    }
}

/* ************************************************************************ */

// Specific member function (inherited from PostOrderMappableContainer)

template<typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun function) {
    ulong i =  size;
    while(i > 0){
        function(this->operator[](--i));
    }
}

/* ************************************************************************ */

// Comparison operators (SortableLinearContainer) (Inherited from LinearContainer)

// Specific member functions (SortableLinearContainer)

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  QuickSort(0, size - 1);
}

template<typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
  if (p < r) {
    ulong q = Partition(p, r);
    QuickSort(p, q);
    QuickSort(q + 1, r);
  }
}

template<typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
  Data x = this->operator[](p);
  ulong i = p - 1;
  ulong j = r + 1;
  do {
    do { j--; }
    while (x < this->operator[](j));
    do { i++; }
    while (x > this->operator[](i));
    if (i < j) { std::swap(this->operator[](i), this->operator[](j)); }
  }
  while (i < j);
  return j;
}


/* ************************************************************************** */

}
