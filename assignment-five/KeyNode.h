// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

/*
 * KeyNode: Represents an entry in the key register BST.
 * Stores a single alphanumeric key string. Comparison operators are
 * overloaded so the BST can order and search key entries by their key field.
 */
class KeyNode {
public:
  string key; // alphanumeric key that identifies a coin in the blockchain

  // Default constructor — initializes key to empty string
  KeyNode() { key = ""; }

  // Parameterized constructor — sets key from the given argument
  KeyNode(string key) { this->key = key; }

  // Comparison operators — ordered by key string for BST operations
  bool operator<(const KeyNode &other) const { return key < other.key; }
  bool operator>(const KeyNode &other) const { return key > other.key; }
  bool operator==(const KeyNode &other) const { return key == other.key; }

  // Stream output operator — prints just the key string
  friend ostream &operator<<(ostream &out, const KeyNode &k) {
    out << k.key;
    return out;
  }
};
