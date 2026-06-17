
static const int STACK_CAP = 128;

template <class T> class AVLTree {
public:
  AVLTree();
  AVLTree(const AVLTree &avl);
  const AVLTree &operator=(const AVLTree &avl);
  ~AVLTree();

  void insert(const T &value);
  void remove(const T &value);

  void inorder() const;
  int treeHeight() const { return height(root); }

protected:
  Node<T> *root;

  int height(Node<T> *r) const;
  int balance(Node<T> *r) const;
  int balanceType(Node<T> *parent, T newValue) const;
  Node<T> *leftRotate(Node<T> *r);
  Node<T> *rightRotate(Node<T> *r);
  Node<T> *bstInsert(Node<T> *r, T value);
  Node<T> *insert(Node<T> *r, T value);
  Node<T> *bstDelete(Node<T> *n, T value);
  Node<T> *avlDelete(Node<T> *r,
                     T value); // named avlDelete (not 'delete' – reserved)

  void destroyTree(Node<T> *r);
  Node<T> *copyTree(Node<T> *r);
  void inorderPrint(Node<T> *r) const;
  Node<T> *rebalance(Node<T> *n); // single-node rebalance
};

// calculate the height of the tree iteratively using a stack to perform a
// depth-first traversal of the tree the algorithm starts by checking if the
// root node is null, in which case it returns a height of 0. If the root node
// is not null, it initializes a stack to keep track of the nodes to visit and a
// variable to keep track of the maximum height encountered during the
// traversal. The algorithm then enters a loop that continues until the stack is
// empty. In each iteration of the loop, it pops a node from the stack and
// checks if it is not null. If the node is not null, it updates the maximum
// height if the current height is greater than the maximum height. It then
// pushes the left and right child nodes of the current node onto the stack,
// along with their corresponding heights (current height + 1). Finally, after
// the loop completes, it returns the maximum height encountered during the
// traversal.

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

// the balance factor of a node is calculated as the height of its left subtree
// minus the height of its right subtree. The balance factor is used to
// determine whether a node is balanced, left-heavy, or right-heavy. A balance
// factor of 0 indicates that the node is perfectly balanced, a balance factor
// of 1 indicates that the node is left-heavy, and a balance factor of -1
// indicates that the node is right-heavy. If the balance factor of a node is
// greater than 1 or less than -1, it means that the node is unbalanced and
// requires rebalancing through rotations.

template <class T> int AVLTree<T>::balance(Node<T> *r) const {
  if (!r)
    return 0;
  return height(r->left) - height(r->right);
}

// the balance type of a node is determined by its balance factor and the value
// of the new node being inserted. The balance type is used to determine which
// rotation(s) to perform in order to rebalance the tree after an insertion. The
// balance type can be one of four values: 0 (balanced), 1 (left-heavy), 2
// (right-heavy), 3 (left-right heavy), or 4 (right-left heavy). The balance
// type is calculated based on the balance factor of the node and the value of
// the new node being inserted. If the balance factor is greater than 1 and the
// new value is less than the value of the left child, it is a left-heavy case
// (balance type 1). If the balance factor is less than -1 and the new value is
// greater than the value of the right child, it is a right-heavy case (balance
// type 2). If the balance factor is greater than 1 and the new value is greater
// than the value of the left child, it is a left-right heavy case (balance type
// 3). If the balance factor is less than -1 and the new value is less than the
// value of the right child, it is a right-left heavy case (balance type 4).
template <class T>
int AVLTree<T>::balanceType(Node<T> *parent, T newValue) const {
  int bf = balance(parent);
  if (bf >= -1 && bf <= 1)
    return 0; // balanced
  if (bf > 1 && newValue < parent->left->data)
    return 1; // LL
  if (bf < -1 && newValue > parent->right->data)
    return 2; // RR
  if (bf > 1 && newValue > parent->left->data)
    return 3; // LR
  return 4;   // RL
}

// left rotation is a tree transformation that is performed on a node in a
// binary search tree (BST) to maintain the balance of the tree. It is used when
// a node becomes right-heavy (i.e., its balance factor is less than -1) after
// an insertion or deletion operation. The left rotation operation involves the
// following steps:
// 1. Identify the node to be rotated (let's call it "x") and its right child
// (let's call it "y").
// 2. Make the left child of "y" the right child of "x".
// 3. Make "y" the new root of the subtree, and "x" becomes the left child of
// "y".
// 4. Update the heights of the affected nodes after the rotation.
// The left rotation helps to restore the balance of the tree by moving the
// heavier subtree (the right subtree) up and the lighter subtree (the left
// subtree) down, thus maintaining the properties of the AVL tree. It is
// important to perform the left rotation correctly to ensure that the tree
// remains balanced and that the properties of the binary search tree are
// preserved.
template <class T> Node<T> *AVLTree<T>::leftRotate(Node<T> *r) {
  if (!r || !r->right)
    return r;
  Node<T> *rc = r->right;
  Node<T> *rcl = rc->left;
  rc->left = r;
  r->right = rcl;
  return rc;
}

// right rotation is a tree transformation that is performed on a node in a
// binary search tree (BST) to maintain the balance of the tree. It is used when
// a node becomes left-heavy (i.e., its balance factor is greater than 1) after
// an insertion or deletion operation. The right rotation operation involves the
// following steps:
// 1. Identify the node to be rotated (let's call it "y") and its left child
// (let's call it "x").
// 2. Make the right child of "x" the left child of "y".
// 3. Make "x" the new
// root of the subtree, and "y" becomes the right child of "x".
// 4. Update the heights of the affected nodes after the rotation.
// The right rotation helps to restore the balance of the tree by moving the
// heavier subtree (the left subtree) up and the lighter subtree (the right
// subtree) down, thus maintaining the properties of the AVL tree. It is
// important to perform the right rotation correctly to ensure that the tree
// remains balanced and that the properties of the binary search tree are
// preserved.
template <class T> Node<T> *AVLTree<T>::rightRotate(Node<T> *r) {
  if (!r || !r->left)
    return r;
  Node<T> *lc = r->left;
  Node<T> *lcr = lc->right;
  lc->right = r;
  r->left = lcr;
  return lc;
}

// the rebalance function is responsible for restoring the balance of the AVL
// tree after an insertion or deletion operation. It takes a node as input and
// checks its balance factor to determine if it is unbalanced. If the node is
// unbalanced, the function identifies the type of imbalance (left-heavy,
// right-heavy, left-right heavy, or right-left heavy) and performs the
// appropriate rotation(s) to restore the balance of the tree. The function
// first checks if the node is null, in which case it returns the node itself.
// If the node is not null, it calculates the balance factor of the node and
// determines the type of imbalance. Based on the type of imbalance, it performs
// the necessary rotations (left rotation, right rotation, or a combination of
// both) to restore the balance of the tree. Finally, it returns the updated
// node after the rotations have been performed. The rebalance function is
// crucial for maintaining the properties of the AVL tree and ensuring that it
// remains balanced after insertions and deletions.
template <class T> Node<T> *AVLTree<T>::rebalance(Node<T> *n) {
  int bf = balance(n);
  if (bf > 1 && balance(n->left) >= 0) // LL
    return rightRotate(n);
  if (bf < -1 && balance(n->right) <= 0) // RR
    return leftRotate(n);
  if (bf > 1 && balance(n->left) < 0) { // LR
    n->left = leftRotate(n->left);
    return rightRotate(n);
  }
  if (bf < -1 && balance(n->right) > 0) { // RL
    n->right = rightRotate(n->right);
    return leftRotate(n);
  }
  return n;
}

// the insert function is responsible for adding a new value to the AVL tree
// while maintaining its balance. It takes a value as input and inserts it into
// the appropriate position in the tree based on the properties of a binary
// search tree. After inserting the new value, the function calls the rebalance
// function to ensure that the tree remains balanced. The insert function first
// checks if the current node is null, in which case it creates a new node with
// the given value and returns it. If the current node is not null, it compares
// the new value with the value of the current node to determine whether to
// insert it into the left or right subtree. If the new value is less than the
// current node's value, it recursively calls insert on the left subtree; if it
// is greater, it recursively calls insert on the right subtree. After inserting
// the new value, it calls the rebalance function to restore the balance of the
// tree if necessary. Finally, it returns the updated node after insertion and
// rebalancing.
template <class T> Node<T> *AVLTree<T>::bstInsert(Node<T> *r, T value) {
  Node<T> *newNode = new Node<T>(value);
  if (!r)
    return newNode;

  Node<T> *cur = r;
  Node<T> *parent = nullptr;
  while (cur) {
    parent = cur;
    cur = (value < cur->data) ? cur->left : cur->right;
  }
  if (value < parent->data)
    parent->left = newNode;
  else
    parent->right = newNode;
  return r;
}

template <class T> Node<T> *AVLTree<T>::insert(Node<T> *r, T value) {
  // collect ancestors so we can rebalance bottom-up
  MyStack<Node<T> *> path(STACK_CAP);

  Node<T> *cur = r;
  while (cur) {
    path.push(cur);
    if (value == cur->data)
      return r; // duplicate: no insert
    cur = (value < cur->data) ? cur->left : cur->right;
  }

  // plain BST insert
  r = bstInsert(r, value);

  // walk back up via path stack and rebalance
  Node<T> *node = nullptr;
  while (path.pop(node)) {
    int bf = balance(node);
    if (bf > 1 || bf < -1) {
      Node<T> *balanced = rebalance(node);
      // update parent of node to point to balanced
      if (!path.isEmpty()) {
        Node<T> *par = path.top();
        if (par->left == node)
          par->left = balanced;
        else
          par->right = balanced;
      } else {
        r = balanced; // node was root
      }
    }
  }
  return r;
}

// the delete function is responsible for removing a value from the AVL tree
// while maintaining its balance. It takes a value as input and searches for the
// node containing that value in the tree. If the node is found, it removes it
// from the tree and then calls the rebalance function to ensure that the tree
// remains balanced. The delete function first checks if the current node is
// null, in which case it returns null. If the current node is not null, it
// compares the value to be deleted with the value of the current node to
// determine whether to search for it in the left or right subtree. If the value
// is less than the current node's value, it recursively calls delete on the
// left subtree; if it is greater, it recursively calls delete on the right
// subtree. If the value matches the current node's value, it means that the
// node to be deleted has been found. The function then handles three cases: if
// the node has no children, it simply deletes the node; if the node has one
// child, it replaces the node with its child; if the node has two children, it
// finds the in-order successor (the smallest value in the right subtree),
// replaces the current node's value with the successor's value, and then
// deletes the successor node. After deleting the node, it calls the rebalance
// function to restore the balance of the tree if necessary. Finally, it returns
// the updated node after deletion and rebalancing.
template <class T> Node<T> *AVLTree<T>::bstDelete(Node<T> *r, T value) {
  Node<T> *parent = nullptr;
  Node<T> *cur = r;
  bool leftSide = false;

  // find the node
  while (cur && cur->data != value) {
    parent = cur;
    leftSide = (value < cur->data);
    cur = leftSide ? cur->left : cur->right;
  }
  if (!cur)
    return r; // not found

  Node<T> *replacement = nullptr;

  if (!cur->left && !cur->right) { // ── leaf
    replacement = nullptr;
  } else if (!cur->right) { // ── only left child
    replacement = cur->left;
  } else if (!cur->left) { // ── only right child
    replacement = cur->right;
  } else { // ── two children: in-order successor
    Node<T> *sucParent = cur;
    Node<T> *suc = cur->right;
    while (suc->left) {
      sucParent = suc;
      suc = suc->left;
    }
    cur->data = suc->data; // copy successor value
    // now delete successor (it has at most a right child)
    if (sucParent == cur)
      sucParent->right = suc->right;
    else
      sucParent->left = suc->right;
    delete suc;
    return r; // structure already updated
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
  // collect path to target
  MyStack<Node<T> *> path(STACK_CAP);
  Node<T> *cur = r;
  while (cur && cur->data != value) {
    path.push(cur);
    cur = (value < cur->data) ? cur->left : cur->right;
  }
  if (!cur)
    return r;

  r = bstDelete(r, value);

  // rebalance all ancestors bottom-up
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
  root = insert(root, value);
}

template <class T> void AVLTree<T>::remove(const T &value) {
  root = avlDelete(root, value);
}

// delete all nodes in the tree to free memory
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

// copy constructor: deep copy of tree
// uses pre-order traversal to copy nodes
// first creates a new node with the same value as the current node, then
// recursively copies the left and right subtrees returns a pointer to the new
// node that is the root of the copied subtree

template <class T> Node<T> *AVLTree<T>::copyTree(Node<T> *r) {
  if (!r)
    return nullptr;
  // level-order copy using two stacks: source nodes & dest nodes
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

// helper function to print tree in-order (for testing)
// prints values in sorted order
// uses a stack to perform iterative in-order traversal
// first goes to the leftmost node, then processes the current node, and finally
// goes to the right subtree
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
