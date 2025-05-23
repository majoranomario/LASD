namespace lasd {

/* ************************************************************************** */

// Specific constructors

template<typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> & container){
    container.Traverse(
        [this](const Data & data) {
            Insert(data);
        }
    );
}

template<typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> && container){
    container.Map(
        [this](Data & data) {
            Insert(std::move(data));
        }
    );
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
SetLst<Data>::SetLst(const SetLst & setlist) : List<Data>::List(setlist) {}

// Move constructor
template<typename Data>
SetLst<Data>::SetLst(SetLst && setlist) : List<Data>(std::move(setlist)) {}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
SetLst<Data> & SetLst<Data>::operator=(const SetLst & setlist){
    List<Data>::operator=(setlist);
    return *this;
}

// Move assignment
template<typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst && setlist) noexcept {
    List<Data>::operator=(std::move(setlist));
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
inline bool SetLst<Data>::operator==(const SetLst<Data> & setlist) const noexcept {
    return List<Data>::operator==(setlist);
}

template<typename Data>
inline bool SetLst<Data>::operator!=(const SetLst<Data> & setlist) const noexcept {
    return List<Data>::operator!=(setlist);
}

/* ************************************************************************** */

// Specific member functions (inherited from OrderedDictionaryContainer)

template<typename Data>
const Data & SetLst<Data>::Min() const {
    return List<Data>::Front();
}

template<typename Data>
Data SetLst<Data>::MinNRemove() {
    return List<Data>::FrontNRemove();
}

template<typename Data>
void SetLst<Data>::RemoveMin() {
    List<Data>::RemoveFromFront();
}

template<typename Data>
const Data & SetLst<Data>::Max() const{
    return List<Data>::Back();
}

template<typename Data>
Data SetLst<Data>::MaxNRemove() {
    return List<Data>::BackNRemove();
}

template<typename Data>
void SetLst<Data>::RemoveMax() {
    List<Data>::RemoveFromBack();
}

template<typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
    Node* curr = head;
    Node* prev = nullptr;

    while (curr != nullptr && curr->element < data) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr || head == nullptr) {
        throw std::out_of_range("Non predecessor exists.");
    }

    return prev->element;
}

template<typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data & data){
    Node* temp = DetachPredecessor(data);
    Data predecessor = temp->element;
    temp->next = nullptr;  //Important: preserves the recursive destructor
    delete temp;
    return predecessor;
}

template<typename Data>
void SetLst<Data>::RemovePredecessor(const Data & data) {
    Node* predecessor = DetachPredecessor(data);
    predecessor->next = nullptr;
    delete predecessor;
}

template<typename Data>
const Data & SetLst<Data>::Successor(const Data& data) const {
    Node* curr = head;

    while (curr != nullptr && curr->element <= data) {
        curr = curr->next;
    }

    if (curr == nullptr || head == nullptr) {
        throw std::out_of_range("No successor exists.");
    }

    return curr->element;
}

template<typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    Node* temp = DetachSuccessor(data);
    Data successor = temp->element;
    temp->next = nullptr;
    delete temp; 
    return successor;
}

template<typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
    Node* successor = DetachSuccessor(data);
    successor->next = nullptr;
    delete successor; 
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)


template<typename Data>
bool SetLst<Data>::Insert(const Data & data) {
    if (head == nullptr) {
        head = tail = new Node(data); 
        ++size;
        return true;
    }

    if (data < head->element) {
        Node* newNode = new Node(data);  
        newNode->next = head;                      
        head = newNode;
        ++size;
        return true;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->element < data) {
        curr = curr->next;
    }

    if (curr->next != nullptr && curr->next->element == data) {
        return false; // already in 
    }

    Node* newNode = new Node(data);  
    newNode->next = curr->next;                  
    curr->next = newNode;

    if (newNode->next == nullptr) {
        tail = newNode;
    }

    ++size;
    return true;
}

template<typename Data>
bool SetLst<Data>::Insert(Data && data) {
    if (head == nullptr) {
        head = tail = new Node(std::move(data)); 
        ++size;
        return true;
    }

    // Insert at front if smaller than head
    if (data < head->element) {
        Node* newNode = new Node(std::move(data));  
        newNode->next = head;                        
        head = newNode;
        ++size;
        return true;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->element < data) {
        curr = curr->next;
    }

    // Traverse until insertion point is found
    if (curr->next != nullptr && curr->next->element == data) {
        return false;     // Do not insert if already present
    }

    // Insert new node
    Node* newNode = new Node(std::move(data)); 
    newNode->next = curr->next;                  
    curr->next = newNode;

    if (newNode->next == nullptr) {
        tail = newNode;
    }

    ++size;
    return true;
}

template<typename Data>
bool SetLst<Data>::Remove(const Data& data) {
    if (head == nullptr) {
        throw std::length_error("removing on an empty set");
    }

    if (head->element == data) {
        Node* toDelete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        toDelete->next = nullptr;
        delete toDelete;
        --size;
        return true;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->element != data) {
        curr = curr->next;
    }

    if (curr->next == nullptr) {
        return false;
    }

    
    Node* toDelete = curr->next;
    curr->next = toDelete->next;
    if (toDelete == tail) {
        tail = curr;
    }
    toDelete->next = nullptr; 
    delete toDelete;
    --size;
    return true;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template<typename Data>
const Data & SetLst<Data>::operator[](ulong i) const {
    if (head == nullptr) {
        throw std::out_of_range("Access to an empty set");
    }

    Node* temp = head;

    while (temp != nullptr && i > 0) {
        temp = temp->next;
        --i;
    }

    if (temp == nullptr) {
        throw std::out_of_range("Index out of range");
    }

    return temp->element;
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)

template<typename Data>
bool SetLst<Data>::Exists(const Data& data) const noexcept {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->element == data) {
            return true;
        }
        if (curr->element > data) {
            return false; // Since the list is sorted, early stop 
        }
        curr = curr->next;
    }
    return false;
}

/* ************************************************************************ */

// Specific member function (inherited from ClearableContainer)

template<typename Data>
void SetLst<Data>::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************ */

// Auxiliary functions

template<typename Data>
typename List<Data>::Node* SetLst<Data>::DetachPredecessor(const Data & data) {
    if (head == nullptr || head->element >= data) {
        throw std::out_of_range("No predecessor exists.");
    }

    Node* curr = head;
    Node* prev = nullptr;
    Node* beforePrev = nullptr;

    // Traverse until we find the first node >= data
    while (curr != nullptr && curr->element < data) {
        beforePrev = prev;
        prev = curr;
        curr = curr->next;
    }

    // Remove prev (last node < data)
    Node* toDetach = prev;

    if (beforePrev == nullptr) {
        // Predecessor is the first node
        head = head->next;
        if (head == nullptr) tail = nullptr;
    } else {
        beforePrev->next = prev->next;
        if (prev == tail) tail = beforePrev;
    }

    --size;
    // To avoid calling the recursive destructor
    toDetach->next = nullptr;
    return toDetach;
}


template<typename Data>
typename List<Data>::Node* SetLst<Data>::DetachSuccessor(const Data & data) {
    if (head == nullptr) {
        throw std::out_of_range("No successor exists.");
    }

    Node* curr = head;
    Node* prev = nullptr;

    // Traverse until we find the first node > data
    while (curr != nullptr && curr->element <= data) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        throw std::out_of_range("No successor exists.");
    }

    // Removes the current node (the logical successor)
    if (prev == nullptr) {
        // Successor is the first node
        head = head->next;
        if (head == nullptr) tail = nullptr;
    } else {
        prev->next = curr->next;
        if (curr == tail) tail = prev;
    }

    --size;
    curr->next = nullptr;
    return curr;
}


/* ************************************************************************ */

}