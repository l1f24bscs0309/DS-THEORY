
static const int STACK_CAP = 128;

template <class T> class AVLTree {
public:
  AVLTree();
  AVLTree(const AVLTree &avl);
  const AVLTree &operator=(const AVLTree &avl);
  ~AVLTree();

  void insert(const T &value);
  void remove(const T &value);
  bool search(const T &value) const;

  void inorder() const;
  int treeHeight() const { return height(root); }

  Node<T> *getRoot() const { return root; }

protected:
  Node<T> *root;

  int height(Node<T> *r) const;
  int balance(Node<T> *r) const;
  int balanceType(Node<T> *parent, T newValue) const;
  Node<T> *leftRotate(Node<T> *r);
  Node<T> *rightRotate(Node<T> *r);
  Node<T> *bstInsert(Node<T> *r, T value);
  Node<T> *insertNode(Node<T> *r, T value);
  Node<T> *bstDelete(Node<T> *r, T value);
  Node<T> *avlDelete(Node<T> *r, T value);
  Node<T> *rebalance(Node<T> *n);

  void destroyTree(Node<T> *r);
  Node<T> *copyTree(Node<T> *r);
  void inorderPrint(Node<T> *r) const;
};

template <class T> int AVLTree<T>::height(Node<T> *r) const {
  if (!r)
    return -1;
  MyStack<Node<T> *> st(STACK_CAP);
  MyStack<int> ht(STACK_CAP);
  st.push(r);
  ht.push(0);
  int maxH = 0;
  Node<T> *cur;
  int h;
  while (st.pop(cur)) {
    ht.pop(h);
    if (h > maxH)
      maxH = h;
    if (cur->left) {
      st.push(cur->left);
      ht.push(h + 1);
    }
    if (cur->right) {
      st.push(cur->right);
      ht.push(h + 1);
    }
  }
  return maxH;
}

template <class T> int AVLTree<T>::balance(Node<T> *r) const {
  if (!r)
    return 0;
  return height(r->left) - height(r->right);
}

template <class T>
int AVLTree<T>::balanceType(Node<T> *parent, T newValue) const {
  int bf = balance(parent);
  if (bf >= -1 && bf <= 1)
    return 0;
  if (bf > 1 && newValue < parent->left->data)
    return 1;
  if (bf < -1 && newValue > parent->right->data)
    return 2;
  if (bf > 1 && newValue > parent->left->data)
    return 3;
  return 4;
}

template <class T> Node<T> *AVLTree<T>::leftRotate(Node<T> *r) {
  if (!r || !r->right)
    return r;
  Node<T> *rc = r->right;
  Node<T> *rcl = rc->left;
  rc->left = r;
  r->right = rcl;
  return rc;
}

template <class T> Node<T> *AVLTree<T>::rightRotate(Node<T> *r) {
  if (!r || !r->left)
    return r;
  Node<T> *lc = r->left;
  Node<T> *lcr = lc->right;
  lc->right = r;
  r->left = lcr;
  return lc;
}

template <class T> Node<T> *AVLTree<T>::rebalance(Node<T> *n) {
  int bf = balance(n);
  if (bf > 1 && balance(n->left) >= 0)
    return rightRotate(n);
  if (bf < -1 && balance(n->right) <= 0)
    return leftRotate(n);
  if (bf > 1 && balance(n->left) < 0) {
    n->left = leftRotate(n->left);
    return rightRotate(n);
  }
  if (bf < -1 && balance(n->right) > 0) {
    n->right = rightRotate(n->right);
    return leftRotate(n);
  }
  return n;
}

template <class T> Node<T> *AVLTree<T>::bstInsert(Node<T> *r, T value) {
  Node<T> *newNode = new Node<T>(value);
  if (!r)
    return newNode;

  Node<T> *cur = r;
  Node<T> *parent = nullptr;
  while (cur) {
    parent = cur;
    if (value < cur->data)
      cur = cur->left;
    else if (value > cur->data)
      cur = cur->right;
    else
      return r; // duplicate
  }
  if (value < parent->data)
    parent->left = newNode;
  else
    parent->right = newNode;
  return r;
}

template <class T> Node<T> *AVLTree<T>::insertNode(Node<T> *r, T value) {
  MyStack<Node<T> *> path(STACK_CAP);

  Node<T> *cur = r;
  while (cur) {
    path.push(cur);
    if (value == cur->data)
      return r;
    cur = (value < cur->data) ? cur->left : cur->right;
  }

  r = bstInsert(r, value);

  Node<T> *node = nullptr;
  while (path.pop(node)) {
    int bf = balance(node);
    if (bf > 1 || bf < -1) {
      Node<T> *balanced = rebalance(node);
      if (!path.isEmpty()) {
        Node<T> *par = path.top();
        if (par->left == node)
          par->left = balanced;
        else
          par->right = balanced;
      } else {
        r = balanced;
      }
    }
  }
  return r;
}

template <class T> Node<T> *AVLTree<T>::bstDelete(Node<T> *r, T value) {
  Node<T> *parent = nullptr;
  Node<T> *cur = r;
  bool leftSide = false;

  while (cur && !(cur->data == value)) {
    parent = cur;
    leftSide = (value < cur->data);
    cur = leftSide ? cur->left : cur->right;
  }
  if (!cur)
    return r;

  Node<T> *replacement = nullptr;

  if (!cur->left && !cur->right) {
    replacement = nullptr;
  } else if (!cur->right) {
    replacement = cur->left;
  } else if (!cur->left) {
    replacement = cur->right;
  } else {
    Node<T> *sucParent = cur;
    Node<T> *suc = cur->right;
    while (suc->left) {
      sucParent = suc;
      suc = suc->left;
    }
    cur->data = suc->data;
    if (sucParent == cur)
      sucParent->right = suc->right;
    else
      sucParent->left = suc->right;
    delete suc;
    return r;
  }

  if (!parent)
    r = replacement;
  else if (leftSide)
    parent->left = replacement;
  else
    parent->right = replacement;
  delete cur;
  return r;
}

template <class T> Node<T> *AVLTree<T>::avlDelete(Node<T> *r, T value) {
  MyStack<Node<T> *> path(STACK_CAP);
  Node<T> *cur = r;
  while (cur && !(cur->data == value)) {
    path.push(cur);
    cur = (value < cur->data) ? cur->left : cur->right;
  }
  if (!cur)
    return r;

  r = bstDelete(r, value);

  Node<T> *node = nullptr;
  while (path.pop(node)) {
    int bf = balance(node);
    if (bf > 1 || bf < -1) {
      Node<T> *balanced = rebalance(node);
      if (!path.isEmpty()) {
        Node<T> *par = path.top();
        if (par->left == node)
          par->left = balanced;
        else
          par->right = balanced;
      } else {
        r = balanced;
      }
    }
  }
  return r;
}

template <class T> void AVLTree<T>::insert(const T &value) {
  root = insertNode(root, value);
}

template <class T> void AVLTree<T>::remove(const T &value) {
  root = avlDelete(root, value);
}

template <class T> bool AVLTree<T>::search(const T &value) const {
  Node<T> *cur = root;
  while (cur) {
    if (value == cur->data)
      return true;
    cur = (value < cur->data) ? cur->left : cur->right;
  }
  return false;
}

template <class T> void AVLTree<T>::destroyTree(Node<T> *r) {
  if (!r)
    return;
  MyStack<Node<T> *> st(STACK_CAP);
  st.push(r);
  Node<T> *cur = nullptr;
  while (st.pop(cur)) {
    if (cur->left)
      st.push(cur->left);
    if (cur->right)
      st.push(cur->right);
    delete cur;
  }
}

template <class T> Node<T> *AVLTree<T>::copyTree(Node<T> *r) {
  if (!r)
    return nullptr;
  MyStack<Node<T> *> srcSt(STACK_CAP);
  MyStack<Node<T> *> dstSt(STACK_CAP);
  Node<T> *newRoot = new Node<T>(r->data);
  srcSt.push(r);
  dstSt.push(newRoot);
  Node<T> *src = nullptr;
  Node<T> *dst = nullptr;
  while (srcSt.pop(src)) {
    dstSt.pop(dst);
    if (src->left) {
      dst->left = new Node<T>(src->left->data);
      srcSt.push(src->left);
      dstSt.push(dst->left);
    }
    if (src->right) {
      dst->right = new Node<T>(src->right->data);
      srcSt.push(src->right);
      dstSt.push(dst->right);
    }
  }
  return newRoot;
}

template <class T> AVLTree<T>::AVLTree() : root(nullptr) {}

template <class T> AVLTree<T>::AVLTree(const AVLTree &avl) {
  root = copyTree(avl.root);
}

template <class T> const AVLTree<T> &AVLTree<T>::operator=(const AVLTree &avl) {
  if (this != &avl) {
    destroyTree(root);
    root = copyTree(avl.root);
  }
  return *this;
}

template <class T> AVLTree<T>::~AVLTree() {
  destroyTree(root);
  root = nullptr;
}

template <class T> void AVLTree<T>::inorderPrint(Node<T> *r) const {
  MyStack<Node<T> *> st(STACK_CAP);
  Node<T> *cur = r;
  while (cur || !st.isEmpty()) {
    while (cur) {
      st.push(cur);
      cur = cur->left;
    }
    st.pop(cur);
    cout << cur->data << " ";
    cur = cur->right;
  }
}

template <class T> void AVLTree<T>::inorder() const {
  inorderPrint(root);
  cout << "\n";
}
