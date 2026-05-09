template <class T>
class AbstractStack
{
 public:
  AbstractStack():count(-1){}
  AbstractStack(const AbstractStack & s): count(s.count){}
  const AbstractStack & operator = (const AbstractStack & s);
  bool operator == (const AbstractStack & s);
  virtual ~AbstractStack(){}
  virtual void push(T v) = 0; // pushed v on Stack
  virtual bool pop(T & value) = 0; // returns top-value in value (and removes)  if not empty, returns sucess or not
  virtual bool top(T & value) = 0; // returns top-value in value if not empty, returns sucess or not
  virtual void display(ostream &) = 0; 
  bool isEmpty( ){return (count == -1);}
 protected:
  int count; // keep tracks of number of values in the Stack
};

template <class T>
const AbstractStack<T> & AbstractStack<T>::operator = (const AbstractStack<T> & s)
{
  if(this != & s)
    {
      count = s.count;
    }
  return *this;
}

template <class T>
bool AbstractStack<T>::operator == (const AbstractStack<T> & s)
{
  return (count== s.count);
}
