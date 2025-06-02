
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
HeapVec<Data>::HeapVec() : Vector<Data>() {}

//Specific constructors

template<typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data> & container) : Vector<Data>(container){
    if (!(IsHeap())){
        Heapify();
    }
}

template<typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data> && container) : Vector<Data>(container){
    if (!(IsHeap())){
        Heapify();
    }
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data> & heap) : Vector<Data>(heap) {}

// Move constructor
template<typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data> && heap) noexcept : Vector<Data>(std::move(heap)) {}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(const HeapVec<Data> & heap) {
    if (this != &heap) {
        Vector<Data>::operator=(heap);
    }
    return *this;
}

// Move assignment
template<typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(HeapVec<Data> && heap) noexcept {
    if (this != &heap) {
        Vector<Data>::operator=(std::move(heap));
    }
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template<typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data> & heap) const noexcept {
    return Vector<Data>::operator==(heap);
}

template<typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data> & heap) const noexcept {
    return Vector<Data>::operator!=(heap);
}

/* ************************************************************************** */

// Specific member functions (inherited from Heap)

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept{
    if (size <= 1) return true;
    
    for (ulong i = 0; i < size / 2; ++i) {
        ulong leftChild = 2 * i + 1;
        ulong rightChild = 2 * i + 2;
        
        // Check left child
        if (leftChild < size && elements[i] < elements[leftChild]) {
            return false;
        }
        
        // Check right child
        if (rightChild < size && elements[i] < elements[rightChild]) {
            return false;
        }
    }
    
    return true;
}


template<typename Data>
void HeapVec<Data>::Heapify() noexcept {
    for(ulong i = size/2; i > 0; --i){
        Heapify(size,i);
    }
}

template<typename Data>
void HeapVec<Data>::Heapify(ulong n,ulong i) noexcept {
    ulong m = i;
    ulong l = 2 * i + 1;
    ulong s = 2 * i + 2;

    if((l < n) && (elements[m] < elements[l])){
        m = l;
    }
    
    if((s < n) && (elements[m] < elements[s])){
        m = s;
    }

    if(m != i){
        std::swap(elements[i],elements[m]);
        Heapify(n,m);
    }
}

/* ************************************************************************ */

// Specific member function (inherited from SortableLinearContainer)

template<typename Data>
void HeapVec<Data>::Sort() noexcept {
    Heapify();
    for(ulong i=size-1;i>=1;--i){
        std::swap(elements[0],elements[i]);
        Heapify(i,0);
    }

}

/* ************************************************************************ */

// Auxiliary functions





}
