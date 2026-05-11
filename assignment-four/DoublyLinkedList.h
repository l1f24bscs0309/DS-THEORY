template <class T>
class DoublyLinkedList
{
public:
  DoublyLinkedList(){first = nullptr; last = nullptr;}
  DoublyLinkedList(const DoublyLinkedList & ll)
  {
    first = nullptr;
    last = nullptr;
    copyList(ll);
  }
  const DoublyLinkedList & operator = (const DoublyLinkedList & );
  virtual ~DoublyLinkedList(){deleteList();}
  virtual void insertAtLast(T) = 0;
  virtual void insertAtFirst(T) = 0;
  virtual T removeFromFirst() = 0;
  virtual T removeFromLast() = 0;
  virtual bool isEmpty() = 0;
  virtual void display() = 0;
protected:
  Node<T> *first;
  Node<T> *last;
  void deleteList();
  void copyList(const DoublyLinkedList<T> &);
};

template <class T>
const DoublyLinkedList<T> & DoublyLinkedList<T>::operator = (const DoublyLinkedList<T> & ll)
{
  if(this != & ll)
    {
      copyList(ll);
    }
  return *this;
}

template <class T>
void DoublyLinkedList<T>::deleteList()
{
  Node<T> *current = first;
  while(current != nullptr)
    {
      Node<T> *nextNode = current->next;
      delete current;
      current = nextNode;
    }
  first = nullptr;
  last = nullptr;
}

template <class T>
void DoublyLinkedList<T>::copyList(const DoublyLinkedList<T> & ll)
{
  if(this == &ll)
    {
      return;
    }

  deleteList();
  Node<T> *current = ll.first;

  while(current != nullptr)
    {
      Node<T> *newNode = new Node<T>;
      newNode->data = current->data;
      newNode->next = nullptr;
      newNode->previous = last;

      if(first == nullptr)
        {
          first = newNode;
          last = newNode;
        }
      else
        {
          last->next = newNode;
          last = newNode;
        }

      current = current->next;
    }
}
