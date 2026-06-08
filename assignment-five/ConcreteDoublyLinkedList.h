template <class T> class ConcreteDoublyLinkedList : public DoublyLinkedList<T> {
public:
  ConcreteDoublyLinkedList() : DoublyLinkedList<T>() {}
  ConcreteDoublyLinkedList(const ConcreteDoublyLinkedList<T> &mll)
      : DoublyLinkedList<T>(mll) {}
  const ConcreteDoublyLinkedList &
  operator=(const ConcreteDoublyLinkedList<T> &mll);
  void insertAtLast(T);
  void insertAtFirst(T);
  void display();
  T removeFromFirst();
  T removeFromLast();
  bool isEmpty();
};

template <class T>
const ConcreteDoublyLinkedList<T> &
ConcreteDoublyLinkedList<T>::operator=(const ConcreteDoublyLinkedList<T> &dll) {
  if (this != &dll) {
    DoublyLinkedList<T>::operator=(dll);
  }
  return *this;
}

template <class T> void ConcreteDoublyLinkedList<T>::insertAtLast(T value) {
  ListNode<T> *newListNode = new ListNode<T>;
  newListNode->data = value;
  newListNode->next = nullptr;
  newListNode->previous = this->last;

  if (this->first == nullptr) {
    this->first = newListNode;
    this->last = newListNode;
    return;
  }

  this->last->next = newListNode;
  this->last = newListNode;
}

template <class T> void ConcreteDoublyLinkedList<T>::insertAtFirst(T value) {
  ListNode<T> *newListNode = new ListNode<T>;
  newListNode->data = value;
  newListNode->previous = nullptr;
  newListNode->next = this->first;

  if (this->first == nullptr) {
    this->first = newListNode;
    this->last = newListNode;
    return;
  }

  this->first->previous = newListNode;
  this->first = newListNode;
}

template <class T> T ConcreteDoublyLinkedList<T>::removeFromFirst() {
  if (isEmpty()) {
    std::cout << "DoublyLinkedList is empty\n";
    return T();
  }

  ListNode<T> *nodeToRemove = this->first;
  T value = nodeToRemove->data;
  this->first = this->first->next;

  if (this->first != nullptr) {
    this->first->previous = nullptr;
  } else {
    this->last = nullptr;
  }

  delete nodeToRemove;
  return value;
}

template <class T> T ConcreteDoublyLinkedList<T>::removeFromLast() {
  if (isEmpty()) {
    std::cout << "DoublyLinkedList is empty\n";
    return T();
  }

  ListNode<T> *nodeToRemove = this->last;
  T value = nodeToRemove->data;
  this->last = this->last->previous;

  if (this->last != nullptr) {
    this->last->next = nullptr;
  } else {
    this->first = nullptr;
  }

  delete nodeToRemove;
  return value;
}

template <class T> bool ConcreteDoublyLinkedList<T>::isEmpty() {
  return this->first == nullptr;
}

template <class T> void ConcreteDoublyLinkedList<T>::display() {
  if (isEmpty()) {
    std::cout << "List is empty\n";
    return;
  }

  ListNode<T> *current = this->first;
  while (current != nullptr) {
    std::cout << current->data;
    if (current->next != nullptr) {
      std::cout << " <-> ";
    }
    current = current->next;
  }
  std::cout << std::endl;
}
