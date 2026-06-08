class KeyNode {

public:
  string key;

  KeyNode() { key = ""; }
  KeyNode(string key) { this->key = key; }

  // needed so BST can compare nodes by key
  bool operator<(const KeyNode &other) const { return key < other.key; }
  bool operator>(const KeyNode &other) const { return key > other.key; }
  bool operator==(const KeyNode &other) const { return key == other.key; }
  friend ostream &operator<<(ostream &out, const KeyNode &k) {
    out << k.key;
    return out;
  }
};
