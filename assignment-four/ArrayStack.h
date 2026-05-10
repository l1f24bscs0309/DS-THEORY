template <class T>
class ArrayStack: public AbstractStack<T>
{
 public:
  ArrayStack(int);
  ArrayStack(const ArrayStack & ma) {copyStack(ma);}
  const ArrayStack & operator = (const ArrayStack & ma);
  bool operator == (const ArrayStack & ma);
  ~ArrayStack(){deleteStack();}
  void push(T v) ; // pushed v on Stack
  bool pop(T & value) ; // returns top-value in value (and removes)  if not empty, returns sucess or not
  bool top(T & value) ; // returns top-value in value if not empty, returns sucess or not
  void display(ostream &) ; 
  bool isFull(){return AbstractStack<T>::count == capacity;}
protected:
  T * values;
  int capacity;
  void copyStack(const ArrayStack<T> &);
  void deleteStack();
};

template <class T>
ArrayStack<T>::ArrayStack(int _capacity): AbstractStack<T>(), capacity(_capacity)
{
  values = new T[capacity];
}

template <class T>
const ArrayStack<T> & ArrayStack<T>::operator = (const ArrayStack<T> & aa)
{
   if(this != & aa)
    {
      copyStack(aa);
    }
     return *this;
}

template <class T>
bool ArrayStack<T>::operator == (const ArrayStack<T> & aa)
{
  if(! AbstractStack<T>::operator == (aa))
    {
      return  false;
    }
  if(capacity != aa.capacity)
    {
      return false;
    }
  for(int i = 0; i < AbstractStack<T>::count; i++)
    {
      if(values[i] != aa.values[i])
	{
	  return false;
	}
    }
  return true;
}

template <class T>
void ArrayStack<T>:: push(T v)
  {
    if(!isFull())
      {
	values[++(AbstractStack<T>::count)] = v;
	return;
      }
    cout << "Array is full\n";
  }
  
template <class T>
bool ArrayStack<T>:: pop(T & v)
  {
    if(!AbstractStack<T>::isEmpty())
    {
      v = values[AbstractStack<T>::count--];
      return true;
    }
    return false;
  }

template <class T>
bool ArrayStack<T>::top(T & v)
{
  if(!AbstractStack<T>::isEmpty())
    {
      v = values[AbstractStack<T>::count];
      return true;
    }
  return false;
}
  

template <class T>
void ArrayStack<T>::copyStack(const ArrayStack<T> & as)
{
  AbstractStack<T>::count = as.count;
  capacity = as.capacity;
  values = new T[capacity];
  for(int i = 0; i < capacity; i++)
    {
      values[i] = as.values[i];
    }
}

template <class T>
void ArrayStack<T>::deleteStack()
{
  if(values != nullptr)
    {
      delete [] values;
      values = nullptr;
    }
}

template <class T>
void ArrayStack<T>:: display(ostream & w)
{
  w << "Count: " << AbstractStack<T>::count << " "
    << "Capacity: "<< capacity << " Values: {";
  for(int i = 0; i <= AbstractStack<T>::count; i++)
    {
      w << values[i] << " ";
    }
  cout << "}\n";
}
