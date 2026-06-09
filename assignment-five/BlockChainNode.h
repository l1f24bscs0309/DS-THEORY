// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

/*
 * BlockchainNode: Represents a single coin block in the blockchain.
 * Each block stores a public coin ID, its monetary value, a key linking
 * it to the key register, and a password. Comparison operators are
 * overloaded so the BST can order and search blocks by their key field.
 */
class BlockchainNode {
public:
  string id;           // public alphanumeric coin identifier
  double privateValue; // monetary worth of the coin
  string key;      // alphanumeric key — links this block to the key register
  string password; // password associated with this coin

  // Default constructor — initializes all fields to empty/zero
  BlockchainNode() {
    id = "";
    privateValue = 0.0;
    key = "";
    password = "";
  }

  // Parameterized constructor — sets all fields from given arguments
  BlockchainNode(string id, double privateValue, string key, string password) {
    this->id = id;
    this->privateValue = privateValue;
    this->key = key;
    this->password = password;
  }

  // Comparison operators — all comparisons are done by key so the BST
  // can insert, search, and remove blocks using the key as the sort field
  bool operator<(const BlockchainNode &other) const { return key < other.key; }
  bool operator>(const BlockchainNode &other) const { return key > other.key; }
  bool operator==(const BlockchainNode &other) const {
    return key == other.key;
  }

  // Stream output operator — prints the block's id, key, and value
  friend ostream &operator<<(ostream &out, const BlockchainNode &b) {
    out << "ID: " << b.id << " | Key: " << b.key
        << " | Value: " << b.privateValue;
    return out;
  }
};
