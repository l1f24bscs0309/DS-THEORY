template <class T>
class Queue
{
 public:
  Queue() : count(0) {}
 Queue(const Queue & q) : count(q.count){}
  const Queue & operator = (const Queue & q);
  virtual ~Queue() {}

  virtual bool isEmpty() const = 0;
  virtual bool isFull() const = 0;
  virtual void enqueue(const  int & value) = 0;
  virtual int dequeue() = 0;
  virtual void display(ostream &) const = 0;
protected:
  int count; // keep a count of values in queue
};

template <class T>
const Queue<T> & Queue<T>::operator = (const Queue<T> & q)
{
  if(this != & q)
    {
      count = q.count;
    }
  return *this;
}

