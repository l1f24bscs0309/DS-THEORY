
template <class T> class NSTNode {
public:
  T data;
  NSTNode *children;
  int noOfChildren;

  NSTNode() : data(T{}), children(nullptr), noOfChildren(0) {}
  NSTNode(T val) : data(val), children(nullptr), noOfChildren(0) {}
};
