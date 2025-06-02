
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
PQHeap<Data>::PQHeap() : HeapVec<Data>() {}

/* ************************************************************************ */

// Specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer & container) : HeapVec<Data>(container) {}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer && container) : HeapVec<Data>(std::move(container)) {}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& PQHeap) : HeapVec<Data>(PQHeap) {}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& PQHeap) noexcept : HeapVec<Data>(std::move(PQHeap)) {}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data>& PQHeap) {
    HeapVec<Data>::operator=(PQHeap);
    return *this;
}

// Move assignment
template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data>&& PQHeap) noexcept {
    HeapVec<Data>::operator=(std::move(PQHeap));
    return *this;
}

/* ************************************************************************** */

// Specific member functions (inherited from PQ)

template <typename Data>
Data & PQHeap<Data>::Tip() const {
    if (size == 0) {
        throw std::length_error("Priority Queue is empty");
    }
    return HeapVec<Data>::Front(); // Max element is at front in max-heap
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (size == 0) {
        throw std::length_error("Priority Queue is empty");
    }
    
    // Move last element to root and reduce size
    HeapVec<Data>::operator[](0) = std::move(HeapVec<Data>::operator[](size - 1));
    // Reduce the size of the heap by one (effectively removing the last element)
    HeapVec<Data>::Resize(size - 1);
    
    // Restore heap property from root down
    if (size > 0) {
        HeapifyDown(0);
    }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {

    // Check if the priority queue is empty
    if(size == 0){
        throw std::length_error("Priority Queue is empty");
    }

    // Store the element with the highest priority (the root of the heap)
    Data tip = std::move(HeapVec<Data>::operator ); 

    // Move the last element in the heap to the root position
    HeapVec<Data>::operator  = std::move(HeapVec<Data>::operator[](size - 1));

    HeapVec<Data>::Resize(size - 1);
    
    // Restore the heap property by pushing the new root down, if the heap is not empty
    if (size > 0) {
        HeapifyDown(0);
    }

    // Return the original tip element
    return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data &) {
    
}