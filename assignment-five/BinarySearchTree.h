template <class T> class BinarySearchTree : public BinaryTree<T> {

  void inorderDisplayHelper(Node<T> *node) const {
    if (node == nullptr)
      return;
    inorderDisplayHelper(node->left);
    cout << node->data << " ";
    inorderDisplayHelper(node->right);
  }

  void preorderDisplayHelper(Node<T> *node) const {
    if (node == nullptr)
      return;
    cout << node->data << " ";
    preorderDisplayHelper(node->left);
    preorderDisplayHelper(node->right);
  }

  void postorderDisplayHelper(Node<T> *node) const {
    if (node == nullptr)
      return;
    postorderDisplayHelper(node->left);
    postorderDisplayHelper(node->right);
    cout << node->data << " ";
  }

  Node<T> *insert_helper(Node<T> *node, const T &val) {
    if (search_helper(node, val)) {
      cout << "value already exists" << endl;
      return node;
    }
    if (node == nullptr) {
      Node<T> *newNode = new Node<T>(val);
      return newNode;
    }
    if (val < node->data) {
      node->left = insert_helper(node->left, val);
    } else {
      node->right = insert_helper(node->right, val);
    }
    return node;
  }

  bool search_helper(Node<T> *node, T val) const {
    if (node == nullptr)
      return false;
    if (node->data == val)
      return true;
    if (val < node->data) {
      return search_helper(node->left, val);
    } else {
      return search_helper(node->right, val);
    }
  }

  Node<T> *find_successor(Node<T> *node) const {
    if (node->left == nullptr)
      return node;
    return find_successor(node->left);
  }

  Node<T> *remove_helper(Node<T> *node, T val) {
    if (node == nullptr) {
      cout << "value doesnot exists in tree" << endl;
      return nullptr;
    }

    if (val < node->data) {
      node->left = remove_helper(node->left, val);
      return node;
    }
    if (val > node->data) {
      node->right = remove_helper(node->right, val);
      return node;
    }

    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    }
    if (node->left == nullptr) {
      Node<T> *right = node->right;
      delete node;
      return right;
    }
    if (node->right == nullptr) {
      Node<T> *left = node->left;
      delete node;
      return left;
    }

    Node<T> *successor = find_successor(node->right);
    node->data = successor->data;
    node->right = remove_helper(node->right, successor->data);
    return node;
  }

public:
  BinarySearchTree() : BinaryTree<T>() {}
  BinarySearchTree(const BinarySearchTree &bt) : BinaryTree<T>(bt) {}
  const BinarySearchTree &operator=(const BinarySearchTree &);
  ~BinarySearchTree() {}
  void insert(const T &value);
  void remove(const T &value);
  bool search(const T &value) const;
  bool isEmpty() const;
  void display() const;
  void inorderDisplay() const;
  void preorderDisplay() const;
  void postorderDisplay() const;
  Node<T> *getRoot() const { return this->root; }
  void setRoot(Node<T> *newRoot) { this->root = newRoot; }
};

template <class T> void BinarySearchTree<T>::display() const {
  cout << "Default display inoder :";
  inorderDisplayHelper(this->root);
}

template <class T> void BinarySearchTree<T>::inorderDisplay() const {
  inorderDisplayHelper(this->root);
}
template <class T> void BinarySearchTree<T>::preorderDisplay() const {
  preorderDisplayHelper(this->root);
}
template <class T> void BinarySearchTree<T>::postorderDisplay() const {
  postorderDisplayHelper(this->root);
}

template <class T> void BinarySearchTree<T>::insert(const T &value) {
  this->root = insert_helper(this->root, value);
}
template <class T> void BinarySearchTree<T>::remove(const T &value) {
  this->root = remove_helper(this->root, value);
}

template <class T> bool BinarySearchTree<T>::search(const T &value) const {
  return search_helper(this->root, value);
}
template <class T> bool BinarySearchTree<T>::isEmpty() const {
  return this->root == nullptr;
}
