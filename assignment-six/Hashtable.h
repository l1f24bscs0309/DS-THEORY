
template <class T> class Hashtable {
public:
  Hashtable(int capacity);
  Hashtable(const Hashtable &);
  const Hashtable &operator=(const Hashtable &);
  ~Hashtable();

  void insert(T value);
  void remove(T value);
  T search(T key);
  void display() const;

  // Extra helpers used by Huffman task
  // Returns the AVLTree bucket at the hash slot of `key`
  AVLTree<T> *getBucket(T key) const;

  template <class Visitor> void forEach(Visitor v) const;

protected:
  AVLTree<T> **values;
  int capacity;
  int count;

  int getHashCode(int value) const {
    return ((value % capacity) + capacity) % capacity;
  }

  int getHashCode(const string &s) const {
    int code = 0;
    for (int i = 0; i < (int)s.size(); i++)
      code += (unsigned char)s[i];
    return (code % capacity + capacity) % capacity;
  }

  // Generic dispatcher — works for any T that is either
  // int or string used in this assignment
  int hashOf(T value) const;

  // Deep-copy all buckets from src into this table
  void copyBuckets(const Hashtable &src);
  void destroyBuckets();
};

template <> int Hashtable<int>::hashOf(int value) const {
  return getHashCode(value);
}

template <> int Hashtable<string>::hashOf(string value) const {
  return getHashCode(value);
}

template <class T> Hashtable<T>::Hashtable(int cap) : capacity(cap), count(0) {
  values = new AVLTree<T> *[capacity];
  for (int i = 0; i < capacity; i++)
    values[i] = nullptr;
}

template <class T>
Hashtable<T>::Hashtable(const Hashtable &ht)
    : capacity(ht.capacity), count(ht.count) {
  values = new AVLTree<T> *[capacity];
  for (int i = 0; i < capacity; i++)
    values[i] = nullptr;
  copyBuckets(ht);
}

template <class T>
const Hashtable<T> &Hashtable<T>::operator=(const Hashtable &ht) {
  if (this != &ht) {
    destroyBuckets();
    delete[] values;
    capacity = ht.capacity;
    count = ht.count;
    values = new AVLTree<T> *[capacity];
    for (int i = 0; i < capacity; i++)
      values[i] = nullptr;
    copyBuckets(ht);
  }
  return *this;
}

template <class T> Hashtable<T>::~Hashtable() {
  destroyBuckets();
  delete[] values;
}

template <class T> void Hashtable<T>::insert(T value) {
  int idx = hashOf(value);
  if (!values[idx])
    values[idx] = new AVLTree<T>();
  // AVLTree ignores duplicates automatically
  values[idx]->insert(value);
  count++;
}

template <class T> void Hashtable<T>::remove(T value) {
  int idx = hashOf(value);
  if (!values[idx]) {
    cout << "Value not found.\n";
    return;
  }
  if (values[idx]->search(value)) {
    values[idx]->remove(value);
    count--;
  } else {
    cout << "Value not found.\n";
  }
}

template <class T> T Hashtable<T>::search(T key) {
  int idx = hashOf(key);
  if (values[idx] && values[idx]->search(key))
    return key;
  return T(); // not found
}

template <class T> void Hashtable<T>::display() const {
  for (int i = 0; i < capacity; i++) {
    if (values[i] && values[i]->getRoot()) {
      cout << "[" << i << "] -> ";
      values[i]->inorder();
    }
  }
}

template <class T> AVLTree<T> *Hashtable<T>::getBucket(T key) const {
  int idx = hashOf(key);
  return values[idx];
}

template <class T>
template <class Visitor>
void Hashtable<T>::forEach(Visitor v) const {
  for (int i = 0; i < capacity; i++) {
    if (!values[i])
      continue;
    // iterative inorder over the AVL bucket
    MyStack<Node<T> *> st(512);
    Node<T> *cur = values[i]->getRoot();
    while (cur || !st.isEmpty()) {
      while (cur) {
        st.push(cur);
        cur = cur->left;
      }
      st.pop(cur);
      v(cur->data);
      cur = cur->right;
    }
  }
}

template <class T> void Hashtable<T>::copyBuckets(const Hashtable &src) {
  for (int i = 0; i < capacity; i++) {
    if (src.values[i] && src.values[i]->getRoot()) {
      values[i] = new AVLTree<T>(*src.values[i]);
    }
  }
}

template <class T> void Hashtable<T>::destroyBuckets() {
  for (int i = 0; i < capacity; i++) {
    delete values[i];
    values[i] = nullptr;
  }
}
