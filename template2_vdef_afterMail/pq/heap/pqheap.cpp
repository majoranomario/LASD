
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
PQHeap<Data>::PQHeap() : HeapVec<Data>() {}

/* ************************************************************************ */

// Specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>(container) {}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container) : HeapVec<Data>(container) {}

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
const Data & PQHeap<Data>::Tip() const {
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
    // Only one element in the heap: remove it and resize to zero
    if (size == 1) {
        HeapVec<Data>::Resize(0);  
        return;                    
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

    // Only one element: move it out, clear the heap, and return it
    if (size == 1) {
        Data tip = std::move(HeapVec<Data>::operator[](0)); 
        HeapVec<Data>::Resize(0);                           
        return tip;                                         
    }

    // Store the element with the highest priority (the root of the heap)
    Data tip = std::move(HeapVec<Data>::operator[](0));
    
    std::cout << tip;

    HeapVec<Data>::operator[](0) = std::move(HeapVec<Data>::operator[](size - 1));
    // Reduce the size of the heap by one (effectively removing the last element)
    HeapVec<Data>::Resize(size - 1);
    
    // Restore heap property from root down
    if (size > 0) {
        HeapifyDown(0);
    }

    return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
    HeapVec<Data>::Resize(size + 1);
    //Insert in Queue 
    HeapVec<Data>::operator[](size - 1) = value;
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) noexcept {
    HeapVec<Data>::Resize(size + 1);
    //Insert in Queue 
    HeapVec<Data>::operator[](size - 1) = std::move(value);
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Data& current = HeapVec<Data>::operator[](index);
    if (value > current) {
        current = value;
        HeapifyUp(index);
    } else if (value < current) {
        current = value;
        HeapifyDown(index);
    }
    // If equal, do nothing
}

template <typename Data>
void PQHeap<Data>::Change(ulong index,Data && value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    Data& current = HeapVec<Data>::operator[](index);
    if (value > current) {
        current = std::move(value);  // move assignment
        HeapifyUp(index);
    } else if (value < current) {
        current = std::move(value);  // move assignment
        HeapifyDown(index);
    }
    // If equal, do nothing
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void PQHeap<Data>::HeapifyUp(ulong index) {
    while (index > 0) {
        ulong parent = (index - 1) / 2;
        
        // If heap property is satisfied, stop
        if (HeapVec<Data>::operator[](parent) >= HeapVec<Data>::operator[](index)) {
            return;
        }
        
        // Swap with parent and continue
        std::swap(HeapVec<Data>::operator[](parent), HeapVec<Data>::operator[](index));
        index = parent;
    }
}

template <typename Data>
void PQHeap<Data>::HeapifyDown(ulong index) {
    //Stub function - calls Standard Heapify(ulong,ulong) from index, inherited from HeapVec
    HeapVec<Data>::Heapify(size,index);
}

}