namespace lasd {

/* ************************************************************************** */

// Constructors

template<typename Data>
SetVec<Data>::SetVec() : Vector<Data>(4) {  // Start with reasonable capacity
    capacity = 4;
    size = 0;
    head = 0;
    tail = 0;
}

template<typename Data>
SetVec<Data>::SetVec(ulong newCapacity) : Vector<Data>(newCapacity) {
    capacity = newCapacity;
    size = 0;
    head = 0;
    tail = 0;
}

/* ************************************************************************ */

// Specific constructors
template<typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec(container.Size()) {
    container.Traverse([this](const Data& data) {
        Insert(data);
    });
}

template<typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) : SetVec(container.Size()) {
    container.Map([this](Data & data) {
        Insert(std::move(data));
    });
}

/* ************************************************************************ */


// Copy Constructor
template<typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& setVector) : Vector<Data>(setVector.capacity) {  // chiama costruttore base con capacità corretta
    size = setVector.size;
    head = setVector.head;
    tail = setVector.tail;
    capacity = setVector.capacity;

    for (ulong i = 0; i < size; ++i) {
        elements[(head + i) % capacity] = setVector.elements[(setVector.head + i) % capacity];
    }
}


// Move Constructor
template<typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& setVector) noexcept 
    : Vector<Data>(std::move(setVector)), capacity(setVector.capacity), 
        head(setVector.head), tail(setVector.tail) {
    // Reset moved object
    setVector.capacity = 0;
    setVector.head = 0;
    setVector.tail = 0;
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& setVec) {
    if (this != &setVec) {
        Vector<Data>::operator=(setVec);
        capacity = setVec.capacity;
        head = setVec.head;
        tail = setVec.tail;
    }
    return *this;
}

// Move assignment
template<typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& setVec) noexcept {
    if (this != &setVec) {
        Vector<Data>::operator=(std::move(setVec));
        capacity = setVec.capacity;
        head = setVec.head;
        tail = setVec.tail;
        
        // Reset moved object
        setVec.capacity = 0;
        setVec.head = 0;
        setVec.tail = 0;
    }
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& setVec) const noexcept {
    if (size != setVec.size) return false;
    
    for (ulong i = 0; i < size; ++i) {
        if ((*this)[i] != setVec[i]) return false;
    }
    return true;
}

template<typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data>& setVec) const noexcept {
    return !(*this == setVec);
}

/* ************************************************************************ */

// OrderedDictionaryContainer functions
template<typename Data>
const Data& SetVec<Data>::Min() const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    return Front();
}

template<typename Data>
Data SetVec<Data>::MinNRemove() {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    
    Data min = std::move(elements[head]);
    head = (head + 1) % capacity;
    --size;
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
    
    return min;
}

template<typename Data>
void SetVec<Data>::RemoveMin() {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    
    head = (head + 1) % capacity;
    --size;
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
}

template<typename Data>
const Data& SetVec<Data>::Max() const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    return Back();
}

template<typename Data>
Data SetVec<Data>::MaxNRemove() {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    
    Data max = std::move(elements[tail]);
    tail = (tail == 0) ? capacity - 1 : tail - 1;
    --size;
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
    
    return max;
}

template<typename Data>
void SetVec<Data>::RemoveMax() {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    
    tail = (tail == 0) ? capacity - 1 : tail - 1;
    --size;
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
}

template<typename Data>
const Data& SetVec<Data>::Predecessor(const Data& data) const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    
    // If exact match found, predecessor is the previous element
    if (pos < size && (*this)[pos] == data) {
        if (pos == 0) {
            throw std::out_of_range("No predecessor exists");
        }
        return (*this)[pos - 1];
    }
    
    // If not found, pos is the insertion point
    // Predecessor is the element before insertion point
    if (pos == 0) {
        throw std::out_of_range("No predecessor exists");
    }
    
    return (*this)[pos - 1];
}

template<typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& data) {
    return DetachPredecessor(data);
}

template<typename Data>
void SetVec<Data>::RemovePredecessor(const Data& data) {
    DetachPredecessor(data);
}

template<typename Data>
const Data& SetVec<Data>::Successor(const Data& data) const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    
    // If exact match found, successor is the next element
    if (pos < size && (*this)[pos] == data) {
        if (pos + 1 >= size) {
            throw std::out_of_range("No successor exists");
        }
        return (*this)[pos + 1];
    }
    
    // If not found, pos is the insertion point (first element > data)
    if (pos >= size) {
        throw std::out_of_range("No successor exists");
    }
    
    return (*this)[pos];
}

template<typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& data) {
    return DetachSuccessor(data);
}

template<typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& data) {
    DetachSuccessor(data);
}

/* ************************************************************************ */

// DictionaryContainer functions
template<typename Data>
bool SetVec<Data>::Insert(const Data& data) {
    // Resize if needed
    if (size == capacity) {
        Resize(capacity * 2);
    }

    if (size == 0) {
        elements[head] = data;
        tail = head;
        ++size;
        return true;
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    
    // Check for duplicates
    if (pos < size && (*this)[pos] == data) {
        return false;
    }

    // Insert at position pos
    InsertAtPosition(pos, data);
    return true;
}

template<typename Data>
bool SetVec<Data>::Insert(Data&& data) {
    // Resize if needed
    if (size == capacity) {
        Resize(capacity * 2);
    }

    if (size == 0) {
        elements[head] = std::move(data);
        tail = head;
        ++size;
        return true;
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    
    // Check for duplicates
    if (pos < size && (*this)[pos] == data) {
        return false;
    }

    // Insert at position pos
    InsertAtPosition(pos, std::move(data));
    return true;
}

template<typename Data>
bool SetVec<Data>::Remove(const Data& data) {
    if (size == 0) {
        return false;
    }

    ulong pos = BinarySearch(data, 0, size - 1);

    if (pos >= size || (*this)[pos] != data) {
        return false;
    }

    RemoveAtPosition(pos);
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
    
    return true;
}

/* ************************************************************************ */

// LinearContainer functions

template<typename Data>
const Data& SetVec<Data>::operator[](ulong i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return elements[(head + i) % capacity];
}

template<typename Data>
const Data& SetVec<Data>::Front() const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    return elements[head];
}

template<typename Data>
const Data& SetVec<Data>::Back() const {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }
    return elements[tail];
}

/* ************************************************************************ */

// MutableLinearContainer functions

template<typename Data>
Data& SetVec<Data>::operator[](ulong i) {
    return const_cast<Data&>(static_cast<const SetVec<Data>&>(*this)[i]);
}

template<typename Data>
Data& SetVec<Data>::Front() {
    return const_cast<Data&>(static_cast<const SetVec<Data>&>(*this).Front());
}

template<typename Data>
Data& SetVec<Data>::Back() {
    return const_cast<Data&>(static_cast<const SetVec<Data>&>(*this).Back());
}

/* ************************************************************************ */

// TestableContainer function
template<typename Data>
bool SetVec<Data>::Exists(const Data& data) const noexcept {
    if (size == 0) {
        return false;
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    return pos < size && (*this)[pos] == data;
}

/* ************************************************************************ */

// ClearableContainer function
template<typename Data>
void SetVec<Data>::Clear() {
    size = 0;
    head = 0;
    tail = 0;
}

/* ************************************************************************ */

// ResizableContainer function
template<typename Data>
void SetVec<Data>::Resize(ulong newCapacity) {
    if (newCapacity < size) {
        throw std::length_error("New capacity cannot be less than current size");
    }

    if (newCapacity == capacity) {
        return;
    }

    Data* newElements = new Data[newCapacity];

    // Copy elements in order
    for (ulong i = 0; i < size; ++i) {
        newElements[i] = std::move((*this)[i]);
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
    head = 0;
    tail = size > 0 ? size - 1 : 0;
}

/* ************************************************************************ */

// Auxiliary functions
template<typename Data>
ulong SetVec<Data>::BinarySearch(const Data& data, ulong left, ulong right) const {
    // Handle empty container
    if (size == 0) return 0;
    
    // Base case: search space exhausted
    if (left > right) {
        return left;  // Return insertion point
    }
    
    ulong mid = left + (right - left) / 2;
    const Data& midValue = (*this)[mid];
    
    if (midValue == data) {
        return mid;  // Found exact match
    } else if (midValue < data) {
        return BinarySearch(data, mid + 1, right);
    } else {
        // Prevent underflow when mid == 0
        if (mid == 0) {
            return 0;
        }
        return BinarySearch(data, left, mid - 1);
    }
}

template<typename Data>
void SetVec<Data>::InsertAtPosition(ulong pos, const Data& data) {
    if (pos == size) {
        // Insert at end
        tail = (tail + 1) % capacity;
        elements[tail] = data;
    } else if (pos == 0) {
        // Insert at beginning
        head = (head == 0) ? capacity - 1 : head - 1;
        elements[head] = data;
    } else {
        // Insert in middle - choose optimal shift direction
        if (pos <= size / 2) {
            // Shift left part backward
            ulong newHead = (head == 0) ? capacity - 1 : head - 1;
            for (ulong i = 0; i < pos; ++i) {
                ulong from = (head + i) % capacity;
                ulong to = (newHead + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            head = newHead;
            elements[(head + pos) % capacity] = data;
        } else {
            // Shift right part forward
            ulong newTail = (tail + 1) % capacity;
            for (ulong i = size; i > pos; --i) {
                ulong from = (head + i - 1) % capacity;
                ulong to = (head + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            tail = newTail;
            elements[(head + pos) % capacity] = data;
        }
    }
    ++size;
}

template<typename Data>
void SetVec<Data>::InsertAtPosition(ulong pos, Data&& data) {
    if (pos == size) {
        // Insert at end
        tail = (tail + 1) % capacity;
        elements[tail] = std::move(data);
    } else if (pos == 0) {
        // Insert at beginning
        head = (head == 0) ? capacity - 1 : head - 1;
        elements[head] = std::move(data);
    } else {
        // Insert in middle - choose optimal shift direction
        if (pos <= size / 2) {
            // Shift left part backward
            ulong newHead = (head == 0) ? capacity - 1 : head - 1;
            for (ulong i = 0; i < pos; ++i) {
                ulong from = (head + i) % capacity;
                ulong to = (newHead + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            head = newHead;
            elements[(head + pos) % capacity] = std::move(data);
        } else {
            // Shift right part forward
            ulong newTail = (tail + 1) % capacity;
            for (ulong i = size; i > pos; --i) {
                ulong from = (head + i - 1) % capacity;
                ulong to = (head + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            tail = newTail;
            elements[(head + pos) % capacity] = std::move(data);
        }
    }
    ++size;
}

template<typename Data>
void SetVec<Data>::RemoveAtPosition(ulong pos) {
    if (pos == 0 && size == 1) {
        // Removing the only element
        size = 0;
        head = 0;
        tail = 0;
        return;
    }
    
    if (pos == 0) {
        // Remove from beginning
        head = (head + 1) % capacity;
    } else if (pos == size - 1) {
        // Remove from end
        tail = (tail == 0) ? capacity - 1 : tail - 1;
    } else {
        // Remove from middle - choose optimal shift direction
        if (pos <= size / 2) {
            // Shift left part forward
            for (ulong i = pos; i > 0; --i) {
                ulong from = (head + i - 1) % capacity;
                ulong to = (head + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            head = (head + 1) % capacity;
        } else {
            // Shift right part backward
            for (ulong i = pos; i < size - 1; ++i) {
                ulong from = (head + i + 1) % capacity;
                ulong to = (head + i) % capacity;
                elements[to] = std::move(elements[from]);
            }
            tail = (tail == 0) ? capacity - 1 : tail - 1;
        }
    }
    --size;
}

template<typename Data>
Data SetVec<Data>::DetachPredecessor(const Data& data) {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    ulong predPos;
    
    // Find predecessor position
    if (pos < size && (*this)[pos] == data) {
        if (pos == 0) {
            throw std::out_of_range("No predecessor exists");
        }
        predPos = pos - 1;
    } else {
        if (pos == 0) {
            throw std::out_of_range("No predecessor exists");
        }
        predPos = pos - 1;
    }

    Data pred = std::move((*this)[predPos]);
    RemoveAtPosition(predPos);
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
    
    return pred;
}

template<typename Data>
Data SetVec<Data>::DetachSuccessor(const Data& data) {
    if (size == 0) {
        throw std::length_error("Set is empty");
    }

    ulong pos = BinarySearch(data, 0, size - 1);
    ulong succPos;
    
    // Find successor position
    if (pos < size && (*this)[pos] == data) {
        if (pos + 1 >= size) {
            throw std::out_of_range("No successor exists");
        }
        succPos = pos + 1;
    } else {
        if (pos >= size) {
            throw std::out_of_range("No successor exists");
        }
        succPos = pos;
    }

    Data succ = std::move((*this)[succPos]);
    RemoveAtPosition(succPos);
    
    // Shrink if needed
    if (capacity > 4 && size <= capacity / 4) {
        Resize(capacity / 2);
    }
    
    return succ;
}

}