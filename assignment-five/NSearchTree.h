template <class T> class NSearchTree {
  NSTNode<T> *root;
  int order;

  int halfOrder() const { return order / 2; }

  void allocChildren(NSTNode<T> *node) const {
    node->children = new NSTNode<T>[order];
    node->noOfChildren = 0;
  }

  bool addChild(NSTNode<T> *parent, const T &val) const {
    for (int i = 0; i < parent->noOfChildren; ++i)
      if (parent->children[i].data == val)
        return false;

    int pos = parent->noOfChildren;
    for (int i = 0; i < parent->noOfChildren; ++i) {
      if (val < parent->children[i].data) {
        pos = i;
        break;
      }
    }

    for (int i = parent->noOfChildren; i > pos; --i) {
      parent->children[i].data = parent->children[i - 1].data;
      parent->children[i].noOfChildren = parent->children[i - 1].noOfChildren;
      parent->children[i].children = parent->children[i - 1].children;
    }

    parent->children[pos].data = val;
    parent->children[pos].noOfChildren = 0;

    parent->children[pos].children = new NSTNode<T>[order];

    parent->noOfChildren++;
    return true;
  }

  void removeChildAt(NSTNode<T> *parent, int idx) const {
    destroyNode(&parent->children[idx]);

    for (int i = idx; i < parent->noOfChildren - 1; ++i) {
      parent->children[i].data = parent->children[i + 1].data;
      parent->children[i].noOfChildren = parent->children[i + 1].noOfChildren;
      parent->children[i].children = parent->children[i + 1].children;
    }

    int last = parent->noOfChildren - 1;
    parent->children[last].data = T{};
    parent->children[last].noOfChildren = 0;
    parent->children[last].children = nullptr;

    parent->noOfChildren--;
  }

  void destroyNode(NSTNode<T> *node) const {
    if (!node || !node->children)
      return;
    for (int i = 0; i < node->noOfChildren; ++i)
      destroyNode(&node->children[i]);
    delete[] node->children;
    node->children = nullptr;
    node->noOfChildren = 0;
  }

  int leftCount(NSTNode<T> *node) const {
    int c = 0;
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data < node->data)
        c++;
    return c;
  }
  int rightCount(NSTNode<T> *node) const {
    int c = 0;
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data > node->data)
        c++;
    return c;
  }

  int rml(NSTNode<T> *node) const {
    int idx = -1;
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data < node->data)
        idx = i;
    return idx;
  }

  int lmr(NSTNode<T> *node) const {
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data > node->data)
        return i;
    return -1;
  }

  void insert_helper(NSTNode<T> *node, const T &val) {
    if (val == node->data) {
      cout << "Value already exists.\n";
      return;
    }

    if (val < node->data) {
      if (leftCount(node) < halfOrder()) {
        if (!addChild(node, val))
          cout << "Value already exists.\n";
      } else {
        insert_helper(&node->children[rml(node)], val);
      }
    } else {
      if (rightCount(node) < halfOrder()) {
        if (!addChild(node, val))
          cout << "Value already exists.\n";
      } else {
        insert_helper(&node->children[lmr(node)], val);
      }
    }
  }

  bool search_helper(NSTNode<T> *node, const T &val) const {
    if (!node)
      return false;
    if (node->data == val)
      return true;
    if (val < node->data) {
      for (int i = 0; i < node->noOfChildren; ++i)
        if (node->children[i].data < node->data)
          if (search_helper(&node->children[i], val))
            return true;
    } else {
      for (int i = 0; i < node->noOfChildren; ++i)
        if (node->children[i].data > node->data)
          if (search_helper(&node->children[i], val))
            return true;
    }
    return false;
  }

  void inorder_helper(NSTNode<T> *node) const {
    if (!node)
      return;
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data < node->data)
        inorder_helper(&node->children[i]);
    cout << node->data << " ";
    for (int i = 0; i < node->noOfChildren; ++i)
      if (node->children[i].data > node->data)
        inorder_helper(&node->children[i]);
  }

  bool remove_helper(NSTNode<T> *node, const T &val) {
    if (!node) {
      cout << "Value does not exist in tree.\n";
      return false;
    }

    if (node->data == val) {
      if (node->noOfChildren == 0)
        return true; // tell caller to remove slot

      int succIdx = lmr(node); // inorder successor = leftmost right child
      int predIdx = rml(node); // largest left child

      if (succIdx != -1) {
        T succ = node->children[succIdx].data;
        node->data = succ;
        if (remove_helper(&node->children[succIdx], succ))
          removeChildAt(node, succIdx);
      } else {
        T pred = node->children[predIdx].data;
        node->data = pred;
        if (remove_helper(&node->children[predIdx], pred))
          removeChildAt(node, predIdx);
      }
      return false;
    }

    if (val < node->data) {
      for (int i = 0; i < node->noOfChildren; ++i) {
        if (node->children[i].data < node->data &&
            search_helper(&node->children[i], val)) {
          if (remove_helper(&node->children[i], val))
            removeChildAt(node, i);
          return false;
        }
      }
    } else {
      for (int i = 0; i < node->noOfChildren; ++i) {
        if (node->children[i].data > node->data &&
            search_helper(&node->children[i], val)) {
          if (remove_helper(&node->children[i], val))
            removeChildAt(node, i);
          return false;
        }
      }
    }
    cout << "Value does not exist in tree.\n";
    return false;
  }

public:
  NSearchTree(int n) : root(nullptr), order(n) {
    if (order < 2 || order % 2 != 0) {
      cout << "Order must be even >= 2. Defaulting to 2.\n";
      order = 2;
    }
  }

  ~NSearchTree() {
    if (root) {
      destroyNode(root);
      delete root;
    }
  }

  void insert(const T &val) {
    if (!root) {
      root = new NSTNode<T>(val);
      allocChildren(root);
    } else {
      insert_helper(root, val);
    }
  }

  void remove(const T &val) {
    if (!root) {
      cout << "Tree is empty.\n";
      return;
    }
    if (remove_helper(root, val)) {
      delete[] root->children;
      delete root;
      root = nullptr;
    }
  }

  bool search(const T &val) const { return search_helper(root, val); }
  bool isEmpty() const { return root == nullptr; }

  void inorderDisplay() const {
    if (isEmpty()) {
      cout << "Tree is empty.\n";
      return;
    }
    cout << "Inorder: ";
    inorder_helper(root);
    cout << "\n";
  }

  void display() const { inorderDisplay(); }
};
