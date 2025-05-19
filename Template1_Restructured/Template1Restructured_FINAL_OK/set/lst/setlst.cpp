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
SetLst<Data>& SetLst<Data>::operator=(SetLst && other) noexcept {
    List<Data>::operator=(std::move(other));
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
        throw std::out_of_range("Non esiste un predecessore.");
    }

    return prev->element;
}

template<typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data & data){
    Node* temp = DetachPredecessor(data);
    Data predecessor = temp->element;
    delete temp;
    return predecessor;
}

template<typename Data>
void SetLst<Data>::RemovePredecessor(const Data & data) {
    Node* predecessor = DetachPredecessor(data);
    delete predecessor;
}

template<typename Data>
const Data & SetLst<Data>::Successor(const Data& data) const {
    Node* curr = head;

    while (curr != nullptr && curr->element <= data) {
        curr = curr->next;
    }

    if (curr == nullptr || head == nullptr) {
        throw std::out_of_range("Non esiste un successore.");
    }

    return curr->element;
}

template<typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    Node* temp = DetachSuccessor(data);
    Data successor = temp->element;
    delete temp; 
    return successor;
}

template<typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
    Node* temp = DetachSuccessor(data);
    delete temp; 
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool SetLst<Data>::Insert(Data && data) {
    if (head == nullptr) {
        head = tail = new Node(std::move(data)); // Costruzione nodo senza next
        ++size;
        return true;
    }

    if (data < head->element) {
        Node* newNode = new Node(std::move(data));  // Nodo senza next nel costruttore
        newNode->next = head;                        // Imposto next manualmente
        head = newNode;
        ++size;
        return true;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->element < data) {
        curr = curr->next;
    }

    if (curr->next != nullptr && curr->next->element == data) {
        return false; // elemento già presente
    }

    Node* newNode = new Node(std::move(data));  // Nodo costruito senza next
    newNode->next = curr->next;                  // imposto next manualmente
    curr->next = newNode;

    if (newNode->next == nullptr) {
        tail = newNode;
    }

    ++size;
    return true;
}


template<typename Data>
bool SetLst<Data>::Insert(const Data & data) {
    if (head == nullptr) {
        head = tail = new Node(data); // Costruzione nodo senza next
        ++size;
        return true;
    }

    if (data < head->element) {
        Node* newNode = new Node(data);  // Nodo senza next nel costruttore
        newNode->next = head;                        // Imposto next manualmente
        head = newNode;
        ++size;
        return true;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->element < data) {
        curr = curr->next;
    }

    if (curr->next != nullptr && curr->next->element == data) {
        return false; // elemento già presente
    }

    Node* newNode = new Node(data);  // Nodo costruito senza next
    newNode->next = curr->next;                  // imposto next manualmente
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
            return false; // Since the list is sorted, we can stop early
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

    while (curr != nullptr && curr->element < data) {
        beforePrev = prev;
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) {
        throw std::out_of_range("No predecessor exists.");
    }

    Node* toDetach = prev;
    if (beforePrev == nullptr) {
        // Predecessor is the head
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        beforePrev->next = prev->next;
        if (prev == tail) {
            tail = beforePrev;
        }
    }

    --size;
    toDetach->next = nullptr;
    return toDetach;
}

template<typename Data>
typename List<Data>::Node* SetLst<Data>::DetachSuccessor(const Data & data) {
    Node* curr = head;

    // Find the node with the given data
    while (curr != nullptr && curr->element != data) {
        curr = curr->next;
    }

    if (curr == nullptr || curr->next == nullptr) {
        throw std::out_of_range("No successor exists.");
    }

    Node* successor = curr->next;
    curr->next = successor->next;
    
    if (successor == tail) {
        tail = curr;
    }

    --size;
    successor->next = nullptr;
    return successor;
}

/* ************************************************************************ */

}