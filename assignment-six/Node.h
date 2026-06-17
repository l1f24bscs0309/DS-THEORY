
template <class T> class Node {
public:
  T data;
  Node *left;  // left child
  Node *right; // right child
  Node(const T &value, Node *leftPtr = nullptr, Node *rightPtr = nullptr) {
    data = value;
    left = leftPtr;
    right = rightPtr;
  }
};
