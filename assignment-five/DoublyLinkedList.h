template <class T> class DoublyLinkedList {
public:
  DoublyLinkedList() {
    first = nullptr;
    last = nullptr;
  }
  DoublyLinkedList(const DoublyLinkedList &ll) {
    first = nullptr;
    last = nullptr;
    copyList(ll);
  }
  const DoublyLinkedList &operator=(const DoublyLinkedList &);
  virtual ~DoublyLinkedList() { deleteList(); }
  virtual void insertAtLast(T) = 0;
  virtual void insertAtFirst(T) = 0;
  virtual T removeFromFirst() = 0;
  virtual T removeFromLast() = 0;
  virtual bool isEmpty() = 0;
  virtual void display() = 0;

protected:
  ListNode<T> *first;
  ListNode<T> *last;
  void deleteList();
  void copyList(const DoublyLinkedList<T> &);
};

template <class T>
const DoublyLinkedList<T> &
DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &ll) {
  if (this != &ll) {
    copyList(ll);
  }
  return *this;
}

template <class T> void DoublyLinkedList<T>::deleteList() {
  ListNode<T> *current = first;
  while (current != nullptr) {
    ListNode<T> *nextListNode = current->next;
    delete current;
    current = nextListNode;
  }
  first = nullptr;
  last = nullptr;
}

template <class T>
void DoublyLinkedList<T>::copyList(const DoublyLinkedList<T> &ll) {
  if (this == &ll) {
    return;
  }

  deleteList();
  ListNode<T> *current = ll.first;

  while (current != nullptr) {
    ListNode<T> *newListNode = new ListNode<T>;
    newListNode->data = current->data;
    newListNode->next = nullptr;
    newListNode->previous = last;

    if (first == nullptr) {
      first = newListNode;
      last = newListNode;
    } else {
      last->next = newListNode;
      last = newListNode;
    }

    current = current->next;
  }
}
