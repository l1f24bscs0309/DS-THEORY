class BlockchainNode {
public:
  string id;           // public alphanumeric ID
  double privateValue; // coin's worth
  string key;          // alphanumeric key (links to key register)
  string password;

  BlockchainNode() {
    id = "";
    privateValue = 0.0;
    key = "";
    password = "";
  }
  BlockchainNode(string id, double privateValue, string key, string password) {
    this->id = id;
    this->privateValue = privateValue;
    this->key = key;
    this->password = password;
  }

  // needed so BST can compare nodes by key
  bool operator<(const BlockchainNode &other) const { return key < other.key; }
  bool operator>(const BlockchainNode &other) const { return key > other.key; }
  bool operator==(const BlockchainNode &other) const {
    return key == other.key;
  }
  friend ostream &operator<<(ostream &out, const BlockchainNode &b) {
    out << "ID: " << b.id << " | Key: " << b.key
        << " | Value: " << b.privateValue;
    return out;
  }
};
