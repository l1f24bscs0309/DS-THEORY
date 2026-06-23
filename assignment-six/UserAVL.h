
// UserAVL.h
// AVL tree to store user ID-password pairs, with display function
// it has a type of AVLTree<UserPair> that stores UserPair objects, which
// contain user ID and password.

class UserAVL : public AVLTree<UserPair> {
public:
  // Returns pointer to pair with matching id, or nullptr
  UserPair *findByID(const string &id) const {
    Node<UserPair> *cur = root;
    while (cur) {
      if (id == cur->data.id)
        return &cur->data;
      cur = (id < cur->data.id) ? cur->left : cur->right;
    }
    return nullptr;
  }

  void showTable() const { displayTable(root); }
};
