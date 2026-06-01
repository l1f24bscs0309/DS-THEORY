template <class T> class BinaryTree {

private:
  void deleteSubTree(Node<T> *root) {
    if (root == nullptr)
      return;
    deleteSubTree(root->left);
    deleteSubTree(root->right);
    delete root;
  }

  Node<T> *copyNodes(Node<T> *root) {
    if (root == nullptr)
      return nullptr;
    Node<T> *newNode = new Node<T>;
    newNode->data = root->data;
    newNode->left = copyNodes(root->left);
    newNode->right = copyNodes(root->right);

    return newNode;
  }

  int treeHeightHelper(Node<T> *node) const {
    if (node == nullptr)
      return 0;

    int left_height = treeHeightHelper(node->left);
    int right_height = treeHeightHelper(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
  }

  int treesNodeCountHelper(Node<T> *node) const {
    if (root == nullptr)
      return 0;

    int left_count = treesNodeCountHelper(node->left);
    int right_count = treesNodeCountHelper(node->right);

    return 1 + left_count + right_count;
  }

  int treeLeavesCountHelper(Node<T> *node) {
    if (node == nullptr)
      return 0;

    if (node->left == nullptr && node->right == nullptr) {
      return 1;
    }
    int left_leaves_count = treeLeavesCountHelper(node->left);
    int right_leaves_count = treeLeavesCountHelper(node->right);

    return left_leaves_count + right_leaves_count;
  }

protected:
  Node<T> *root;
  void deleteTree();
  void copyTree(const BinaryTree *bt);

public:
  BinaryTree() { root = nullptr; }
  BinaryTree(const BinaryTree &bt) { copyTree(bt); }
  const BinaryTree &operator=(const BinaryTree &);
  virtual ~BinaryTree() { deleteTree(); }
  virtual void insert(const T &value) = 0;
  virtual void remove(const T &value) = 0;
  virtual bool search(const T &value) const = 0;
  virtual bool isEmpty() const = 0;
  virtual void inorderDisplay() const = 0;
  virtual void preorderDisplay() const = 0;
  virtual void postorderDisplay() const = 0;
  int treeHeight() const;    // Returns the height of the binary tree.
  int treeNodeCount() const; // Returns the number of nodes in the binary tree.
  int treeLeavesCount() const; // Returns the number of leaves in the binary
                               // tree
};

template <class T> void BinaryTree<T>::deleteTree() {
  deleteSubTree(root);
  root = nullptr;
}
template <class T> void BinaryTree<T>::copyTree(const BinaryTree *bt) {
  if (bt->root == nullptr) {
    this->root = nullptr;
    return;
  }
  this->root = copyNodes(bt);
}

template <class T> int BinaryTree<T>::treeHeight() const {
  return treeHeightHelper(root);
}

template <class T> int BinaryTree<T>::treeNodeCount() const {
  return treesNodeCountHelper(root);
}

template <class T> int BinaryTree<T>::treeLeavesCount() const {
  return treeLeavesCountHelper(root);
}
