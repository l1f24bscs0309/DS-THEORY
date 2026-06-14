// MaxHeap.h
template <class T> class MaxHeap {
public:
  // Constructor
  // default constructor to initialize the heap with a given capacity and set
  // the current size to 0
  MaxHeap(int capacity) {
    arr = new T[capacity];
    this->capacity = capacity;
    currentSize = 0;
  }

  // a copy constructor to create a new heap object as a copy of an existing
  // heap object i.e it performs a deep copy of the existing heap object by
  // allocating new memory for the array and copying the elements from the
  // existing heap to the new heap.
  MaxHeap(const MaxHeap &mh) {
    arr = new T[mh.capacity];
    for (int i = 0; i < mh.currentSize; i++) {
      arr[i] = mh.arr[i];
    }
    capacity = mh.capacity;
    currentSize = mh.currentSize;
  }

  // an assignment operator to assign the values of one heap object to another
  // heap object i.e it performs a deep copy of the existing heap object by
  // allocating new memory for the array and copying the elements from the
  // existing heap to the new heap.
  const MaxHeap &operator=(const MaxHeap &mh) {
    T *newArr = new T[mh.capacity];
    for (int i = 0; i < mh.currentSize; i++) {
      newArr[i] = mh.arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = mh.capacity;
    currentSize = mh.currentSize;
    return *this;
  }

  // free the allocated memory for the array when the heap object is destroyed
  ~MaxHeap() { delete[] arr; }

  // Insertion algorithm for max heap.
  // first check if the heap is fill or not, if it is full then return. If it is
  // not full then insert the new value; insertion add an element to the end of
  // the array and then call buildHeap() to maintain the max heap property.
  void insert(const T value) {
    if (currentSize == capacity) {
      cout << "Heap is full. Cannot insert." << endl;
      return;
    }
    arr[currentSize] = value;
    currentSize++;
    buildHeap();
  }

  // Removal algorithm for max heap:
  // first check if the value is present in the heap or not, if it is not
  // present then return. if it is present we find the index of the value in the
  // array, replace it with the last element in the array, decrease the current
  // size of the heap, and then call buildHeap() to maintain the max heap
  // property.
  void remove(const T &value) {
    int index = -1;
    for (int i = 0; i < currentSize; i++) {
      if (arr[i] == value) {
        index = i;
        break;
      }
    }
    if (index == -1) {
      cout << "Value not found in heap." << endl;
      return;
    }
    arr[index] = arr[currentSize - 1];
    currentSize--;
    buildHeap();
  }

  // Search algorithm for max heap:
  // matches the value with each element in the array and returns true if a
  // match is found, otherwise returns false.
  bool search(const T &value) const {
    for (int i = 0; i < currentSize; i++) {
      if (arr[i] == value) {
        return true;
      }
    }
    return false;
  }

  // Heap sort algorithm for max heap:
  // (1) the heap sort algorithm is called after every insertion and removal
  // (2) the heap sort algorithm first builds the max heap using the buildHeap()
  // function and then repeatedly swaps the root of the heap (the maximum
  // element) with the last element in the heap and reduces the size of the heap
  // by one until the heap is empty. After each swap, the max heap property is
  // maintained by calling the MaxHeapify() function on the root of the heap.
  // (3) the result of the heap sort algorithm is a sorted array in ascending
  // order
  void heapSort() {
    buildHeap();
    for (int i = currentSize - 1; i > 0; --i) {
      swap(0, i);
      MaxHeapify(0, i);
    }
  }

  // Returns the maximum element in the heap, which is the root of the heap.
  bool isEmpty() const { return currentSize == 0; }

  // Returns true if the heap is full, which means that the current size of the
  // heap is equal to its capacity.
  bool isFull() const { return currentSize == capacity; }

  // Displays the elements in the heap in the order they are stored in the
  // array.
  void display() const {
    for (int i = 0; i < currentSize; i++) {
      cout << arr[i] << " ";
    }
  }

  // BUild heap algorithm for max heap:
  // (1) the build heap is called after every insertion and removal
  // (2) the build heap starts at current size / 2 as we are sure that half of
  // the elements are going to be leaf nodes and we dont need to heapify them.
  // then heapify each node from the last non-leaf node to the root node to
  // maintain the max heap property.
  //
  // (3) if we start from the root node and
  // heapify each node then we will not be able to maintain the max heap
  // property as we are not sure if the child nodes are heapified or not.
  void buildHeap() {
    for (int i = currentSize / 2; i >= 0; --i) {
      MaxHeapify(i, currentSize);
    }
  }

protected:
  T *arr;          // pointer to array of elements in heap
  int capacity;    // maximum possible size of min heap
  int currentSize; // Current number of elements in min heap
  // to heapify a subtree with the root at given index

  // max heapify algorithm :
  // (1) the max heapify algorithm is called after every insertion and removal
  // (2) the max heapify algorithm starts at the given index and compares the
  // value at that index with its left and right child nodes.
  //
  // (3) If the value at the given index is smaller than either of its child
  // nodes, then we swap the value at the given index with the larger of its
  // child nodes and recursively call the max heapify algorithm on the child
  // node that was swapped. This process continues until the value at the given
  // index is larger than both of its child nodes or until we reach a leaf node.
  //
  //
  //
  // \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
  // i changed the fucntion definition to take the size of the heap as a
  // parameter instead of using the current size beacause doing this helps us to
  // easily implement the heap sort algorithm as we can call the max heapify
  // function with the size of the heap as a parameter and it will heapify the
  // heap accordingly.
  void MaxHeapify(int i, int size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && arr[left] > arr[largest])
      largest = left;
    if (right < size && arr[right] > arr[largest])
      largest = right;
    if (largest != i) {
      swap(i, largest);
      MaxHeapify(largest, size);
    }
  }

  // basic itc concept of swapping two elements in an array using a temporary
  // variable.
  void swap(int i, int largest) {
    T temp = arr[largest];
    arr[largest] = arr[i];
    arr[i] = temp;
  }
};
