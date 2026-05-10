template <class T>
class ArrayQueue: public Queue<T>
{
public:
  ArrayQueue(int s);
  ArrayQueue(const ArrayQueue & q): Queue<T>(q) {copyQueue(q);}
  ~ArrayQueue(){deleteQueue();}
  bool isEmpty() const;
  bool isFull() const;
  void enqueue(const T & value);
  T dequeue();
  void display(ostream &) const;
protected:
  int startOfQIndex;     // corresponds to front
  int topOfQIndex;       // corresponds to rear
  int maxCapacity;       // total size of array
  T * values;
  void deleteQueue();
  void copyQueue(const ArrayQueue &);
};

template <class T>
ArrayQueue<T>::ArrayQueue(int s): Queue<T>(), startOfQIndex(-1), topOfQIndex(-1), maxCapacity(s)
{
  if(s != 0)
    {
      values = new T[this->maxCapacity];
    }
}

// Add (insert element at topOfQIndex)
template <class T>
void ArrayQueue<T>::enqueue(const T & value)
{
  if (this->isFull()) {
    cout << "ArrayQueue is FULL! Cannot add " << value << endl;
    return;
  }
  if (this->isEmpty()) {  // First element insertion
    this->topOfQIndex = 0;
  }
  this->startOfQIndex++;
  values[this->startOfQIndex] = value;
  this->count++;
}

// Remove (remove element from  startOfQIndex)
template <class T>
T ArrayQueue<T>::dequeue() {
  if (this->isEmpty()) {
    cout << "ArrayQueue is EMPTY! Cannot remove." << endl;
    return -1;
  }
  T removedValue = values[this->topOfQIndex];
  this->count--;
  this->topOfQIndex++;
  // If queue becomes empty after remove, reset it
  if (this->isEmpty()) {
    this->startOfQIndex = this->topOfQIndex = -1;
  }
  return removedValue;
}

// Display the queue
template <class T>
void ArrayQueue<T>::display(ostream & W) const
{
  W <<"Queue::startOfQIndex: " << this->startOfQIndex
       <<", topOfQIndex: " << this->topOfQIndex
       <<", this->maxCapacity: " << this->maxCapacity
       <<", count: " << this->count << endl;
  if (this->isEmpty()) {
	cout << "___\n";
	cout << "___\n";
	return;
  }
  int n = this->topOfQIndex;
  W <<"----------------------------\n";
  for(int i = this->startOfQIndex ; i >= n ; i--)
    {
      W << values[i];
      if(i > 0 && i != n)
	{
	  W << " -> ";
	}
    }
  cout << endl;
  W <<"----------------------------\n";
  // <A --> B --> C>
}


  // Check if queue is empty
template <class T>
bool ArrayQueue<T>::isEmpty() const
{
      return (this->count == 0);
}
// Check if queue is full
template <class T>
bool ArrayQueue<T>::isFull() const
{
  return (this->count == maxCapacity );
}

template <class T>
void ArrayQueue<T>::deleteQueue()
{
  if(values != nullptr)
    {
      delete [] values;
      values = nullptr;
    }
}

template <class T>
void ArrayQueue<T>::copyQueue(const ArrayQueue & q)
{
      startOfQIndex = q.startOfQIndex;
      topOfQIndex = q.topOfQIndex;
      maxCapacity = q.maxCapacity;
      this->count = q.count;
      if(this->maxCapacity != 0)
	{
	  values = new T[this->maxCapacity];
	  for(int i = 0; i < this->maxCapacity; i++)
	    {
	      values[i] = q.values[i];
	    }
      }

}


