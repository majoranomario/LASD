
namespace lasd {

/* ************************************************************************** */

// Specific constructor (Node)
template<typename Data>
List<Data>::Node::Node(Data && data) noexcept {
  std::swap(element, data);
}

/* ************************************************************************** */

// Move constructor (Node)
template<typename Data>
List<Data>::Node::Node(Node && node) noexcept {
  std::swap(element, node.element);
  std::swap(next, node.next);
}

/* ************************************************************************** */

// Destructor (Node)
template<typename Data>
List<Data>::Node::~Node() {
  delete next;
}

/* ************************************************************************** */

// Comparison operators (Node)

template<typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
  if (element != node.element) {
    return false;
  }
  
  if (next == nullptr && node.next == nullptr) {
    return true; 
  }
  if (next == nullptr || node.next == nullptr) {
    return false; 
  }
  
  return *next == *node.next;
}

template<typename Data>
inline bool List<Data>::Node::operator!=(const Node & node) const noexcept {
  return !(this->operator==(node));
}

/* ************************************************************************** */

// Specific member functions (Node)

template<typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail) {
  if (next == nullptr) {
    return tail;
  } else {
    Node * node = new Node(element);
    node->next = next->Clone(tail);
    return node;
  }
}


/* ************************************************************************** */

// Specific constructors (List)

// Constructs a List by inserting each element at the back to preserve the original order.
// The first constructor copies elements from a TraversableContainer.
// The second constructor moves elements from a MappableContainer (rvalue reference).

template<typename Data>
List<Data>::List(const TraversableContainer<Data> & container) {
  container.Traverse(
    [this](const Data & data) {
      InsertAtBack(data);
    }
  );
}

template<typename Data>
List<Data>::List(MappableContainer<Data> && container) {
  container.Map(
    [this](Data & data) {
      InsertAtBack(std::move(data));
    }
  );
}

/* ************************************************************************** */


// Copy constructor (List)

template<typename Data>
List<Data>::List(const List<Data> & list) {
  if (list.tail != nullptr) {
    tail = new Node(*list.tail);
    head = list.head->Clone(tail);
    tail->next = nullptr;
    size = list.size;
  }
}


// Move constructor (List)

template<typename Data>
List<Data>::List(List<Data> && list) noexcept {
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
}

/* ************************************************************************** */

// Destructor (List)

template<typename Data>
List<Data>::~List() {
  delete head;
  head = tail = nullptr;
}

/* ************************************************************************** */

//rifai

//Copy assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List<Data> & list) {
  if (this == &list) return *this;  // self-assignment protection

  if (size <= list.size) {
    // Case: current list is shorter or equal in size
    if (tail == nullptr) {
      // Current list is empty: create a complete temporary copy and swap
      List<Data> tmp(list);
      std::swap(*this, tmp);
    } else {
      // Overwrite data in existing nodes
      Node* currentThis = head;
      Node* currentLst = list.head;
      while (currentThis != nullptr) {
        currentThis->element = currentLst->element;
        currentThis = currentThis->next;
        currentLst = currentLst->next;
      }
      // If list is longer, create new nodes for the extra part
      if (currentLst != nullptr) {
        Node* newTail = new Node(*list.tail);
        tail->next = currentLst->Clone(newTail);
        tail = newTail;
      }
    }
  } else {
      // Case: current list is longer
    if (list.tail == nullptr) {
      // List to copy is empty: free the entire current list
      delete head;
      head = tail = nullptr;
    } else {
      // Overwrite the first list.size elements
      Node* currentThis = head;
      Node* currentLst = list.head;
      Node* prev = nullptr;
      while (currentLst != nullptr) {
        currentThis->element = currentLst->element;
        prev = currentThis;
        currentThis = currentThis->next;
        currentLst = currentLst->next;
      }
      // Now currentThis points to the extra nodes to delete
      // prev is the last node to keep
      // Delete the extra nodes
      while (currentThis != nullptr) {
        Node* toDelete = currentThis;
        currentThis = currentThis->next;
        toDelete->next = nullptr;
        delete toDelete;
      }
      // Properly terminate the list
      tail = prev;
      if (tail != nullptr){
        tail->next = nullptr;
      } 
    }
  }
  size = list.size;
  return *this;
}

// Move assignment (List)
template<typename Data>
List<Data> & List<Data>::operator=(List<Data> && list) noexcept {
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
inline bool List<Data>::operator==(const List<Data> & list) const noexcept {
  if(size != list.size){
    return false;
  }

  if(head == nullptr && list.head == nullptr){
    return true;
  }else
  {
    return *head == *list.head;
  }
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data> & list) const noexcept {
  return !(this->operator==(list));
}

/* ************************************************************************** */

// Specific member functions (List)

template<typename Data>
void List<Data>::InsertAtFront(const Data & data) {
  AttachAtFront(new Node((data)));
}

template<typename Data>
void List<Data>::InsertAtFront(Data && data) {
  AttachAtFront(new Node(std::move(data)));
}

template<typename Data>
void List<Data>::RemoveFromFront() {
  delete DetachAtFront();
}

template<typename Data>
Data List<Data>::FrontNRemove() {
  Node* node = DetachAtFront();
  Data front = std::move(node->element);  
  delete node;                              
  return front;
}

template<typename Data>
void List<Data>::InsertAtBack(const Data & data) {
  AttachAtBack(new Node(data));
}

template<typename Data>
void List<Data>::InsertAtBack(Data && data) {
  AttachAtBack(new Node(std::move(data)));
}

template<typename Data>
void List<Data>::RemoveFromBack() {
  delete DetachAtBack();
}


template<typename Data>
Data List<Data>::BackNRemove() {
  Node* node = DetachAtBack();
  Data back = std::move(node->element);
  delete node;
  return back;
}


/* ************************************************************************ */

// Specific member functions (inherited from MutableLinearContainer)

template<typename Data>
Data & List<Data>::operator[](ulong i) {
  return const_cast<Data&>(static_cast<const List<Data>&>(*this)[i]);
}

template<typename Data>
Data & List<Data>::Front() {
  return const_cast<Data&>(static_cast<const List<Data>&>(*this).Front());
}

template<typename Data>
Data & List<Data>::Back() {
  return const_cast<Data&>(static_cast<const List<Data>&>(*this).Back());
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template<typename Data>
const Data & List<Data>::operator[](ulong i) const {
  if(i < size){
    Node * temp = head;
    for(ulong j = 0; j < i; ++j){
      temp = temp->next;
    }
    return temp->element;
  }else{
    throw std::out_of_range("Index of out range");
  }
}

template<typename Data>
const Data & List<Data>::Front() const {
  if(head != nullptr){
    return head->element;
  }else{
    throw std::length_error("Access to an empty list");
  }   
}

template<typename Data>
const Data & List<Data>::Back() const {
    if(tail != nullptr){
      return tail->element;
    }else{
      throw std::length_error("Access to an empty list");
    } 
}

/* ************************************************************************ */

// Specific member function (inherited from MappableContainer)

template<typename Data>
inline void List<Data>::Map(MapFun function) {
  PreOrderMap(function, head);
}

/* ************************************************************************ */

// Specific member functions (List) (inherited from PreOrderMappableContainer)

template<typename Data>
inline void List<Data>::PreOrderMap(MapFun function) {
  PreOrderMap(function, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderMappableContainer)

template<typename Data>
inline void List<Data>::PostOrderMap(MapFun function) {
  PostOrderMap(function, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from TraversableContainer)

template<typename Data>
inline void List<Data>::Traverse(TraverseFun function) const {
  PreOrderTraverse(function, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderTraversableContainer)

template<typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

template<typename Data>
void List<Data>::Clear() {
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for TraversableContainer)

template<typename Data>
void List<Data>::PreOrderTraverse(TraverseFun function, const Node * temp) const {
  for (; temp != nullptr; temp = temp->next) {
    function(temp->element);
  }
}

template<typename Data>
void List<Data>::PostOrderTraverse(TraverseFun function, const Node * temp) const {
  if (temp != nullptr) {
    PostOrderTraverse(function, temp->next);
    function(temp->element);
  }
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for MappableContainer)

template<typename Data>
void List<Data>::PreOrderMap(MapFun function, Node * temp) {
  for (; temp != nullptr; temp = temp->next) {
    function(temp->element);
  }
}

template<typename Data>
void List<Data>::PostOrderMap(MapFun function, Node * temp) {
  if (temp != nullptr) {
    PostOrderMap(function, temp->next);
    function(temp->element);
  }
}

/* ************************************************************************** */

// Auxiliary functions

template<typename Data>
void List<Data>::AttachAtFront(Node* node) noexcept {
  if (node == nullptr) return; 
  node->next = nullptr; // 

  if (head == nullptr) {
    head = tail = node;
  } else {
    node->next = head;
    head = node;
  }
  ++size;
}

template<typename Data>
void List<Data>::AttachAtBack(Node* node) noexcept {
  if (node == nullptr) return; 
  node->next = nullptr;        

  if (tail == nullptr) {
    head = tail = node;
  } else {
    tail->next = node;
    tail = node;
  }
  ++size;
}

template<typename Data>
typename List<Data>::Node * List<Data>::DetachAtBack(){
  if (head != nullptr) {
    if (head == tail) {
      Node* temp = head;
      head = tail = nullptr;
      --size;
      return temp;
    } else {
      Node* temp = head;
      while (temp->next != tail) {
        temp = temp->next;
      }
      Node* toDetach = tail;
      tail = temp;
      tail->next = nullptr;
      --size;
      return toDetach;
    }
  } else {
    throw std::length_error("Removing from an empty list");
  }
}


template<typename Data>
typename List<Data>::Node * List<Data>::DetachAtFront(){
  if (head != nullptr) {
    Node* toDetach = head; 
    if (tail == head) { 
      head = tail = nullptr; 
    }else{
      head = head->next;
    }
    --size; 
    toDetach->next = nullptr;
    return toDetach; 
  }
  else{
    throw std::length_error("Removing from an empty list");
  }
}

/* ************************************************************************** */

}



