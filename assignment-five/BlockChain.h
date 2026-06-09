// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

/*
 * Blockchain: Manages two parallel BSTs — chainTree (stores BlockchainNode
 * coin blocks) and keyRegister (stores KeyNode entries). Every coin added
 * must have a matching key in both trees; deletion and verification keep
 * the two trees in sync.
 */
class Blockchain {
  BinarySearchTree<BlockchainNode>
      chainTree; // BST of coin blocks ordered by key
  BinarySearchTree<KeyNode>
      keyRegister; // BST of registered keys ordered by key

  /*
   * displayDescendingHelperForChain
   * - Purpose: Prints all coin blocks in descending key order (reverse
   * in-order).
   * - Base case: Node is nullptr — return immediately.
   * - Recursive case: Traverse right subtree first (larger keys), print current
   *   block's id, value, and key, then traverse left subtree (smaller keys).
   */
  void displayDescendingHelperForChain(Node<BlockchainNode> *node) {
    if (node == nullptr) {
      return;
    }
    displayDescendingHelperForChain(node->right);
    cout << "ID: " << node->data.id << ", Value: " << node->data.privateValue
         << ", Key: " << node->data.key << endl;
    displayDescendingHelperForChain(node->left);
  }

  /*
   * displayDescendingHelperForRegister
   * - Purpose: Prints all key register entries in descending key order (reverse
   * in-order).
   * - Base case: Node is nullptr — return immediately.
   * - Recursive case: Traverse right subtree first, print current key,
   *   then traverse left subtree.
   */
  void displayDescendingHelperForRegister(Node<KeyNode> *node) {
    if (node == nullptr) {
      return;
    }
    displayDescendingHelperForRegister(node->right);
    cout << "Key: " << node->data.key << endl;
    displayDescendingHelperForRegister(node->left);
  }

  /*
   * verifyHelper
   * - Purpose: Validates that every coin block in chainTree has a matching key
   *   in keyRegister, ensuring the two trees are in sync.
   * - Base case: Node is nullptr — return true (no block to verify here).
   * - Recursive case: Search keyRegister for the current block's key; if not
   *   found, print a failure message and return false. Otherwise, recurse into
   *   both subtrees and return true only if both sides also verify
   * successfully.
   */
  bool verifyHelper(Node<BlockchainNode> *node) {
    if (node == nullptr) {
      return true;
    }
    KeyNode searchKeyNode(node->data.key);
    // Check that this block's key exists in the key register
    if (!keyRegister.search(searchKeyNode)) {
      cout << "Verification failed: Key " << node->data.key
           << " not found in register." << endl;
      return false;
    }
    // Both subtrees must also verify for the entire chain to be valid
    return verifyHelper(node->left) && verifyHelper(node->right);
  }

public:
  Blockchain() {}

  /*
   * addCoin: Creates a BlockchainNode and a KeyNode from the given arguments
   * and inserts both into their respective BSTs. Prints a confirmation on
   * success or an error message if an exception is thrown.
   */
  void addCoin(string id, double privateValue, string key, string password) {
    BlockchainNode newNode(id, privateValue, key, password);
    KeyNode newKeyNode(key);

    try {
      chainTree.insert(newNode);
      keyRegister.insert(newKeyNode);
      cout << "Coin with key " << key << " added to chain and register."
           << endl;
    } catch (const exception &e) {
      cout << "Error adding coin: " << e.what() << endl;
    }
  }

  /*
   * searchByKey: Checks for the given key in keyRegister first, then in
   * chainTree. Returns true only if the key exists in both trees.
   * Prints a message if the key is missing from either tree.
   */
  bool searchByKey(string key) {
    KeyNode searchKeyNode(key);
    // First verify the key exists in the register
    if (!keyRegister.search(searchKeyNode)) {
      cout << "Key not found in register." << endl;
      return false;
    }
    // Then confirm the corresponding block exists in the chain
    BlockchainNode searchChainNode("", 0.0, key, "");
    if (chainTree.search(searchChainNode)) {
      return true;
    } else {
      cout << "Key not found in chain." << endl;
      return false;
    }
  }

  /*
   * deleteByKey: Removes the coin block and its key entry from both BSTs.
   * First checks keyRegister; if the key is absent, prints a message and
   * returns. Otherwise removes from both chainTree and keyRegister, printing
   * confirmation or an error message if an exception occurs.
   */
  void deleteByKey(string key) {
    KeyNode searchKeyNode(key);
    // Abort if the key is not registered
    if (!keyRegister.search(searchKeyNode)) {
      cout << "Key not found in register." << endl;
      return;
    }

    BlockchainNode searchChainNode("", 0.0, key, "");
    try {
      // Remove from both trees to keep them in sync
      chainTree.remove(searchChainNode);
      keyRegister.remove(searchKeyNode);
      cout << "Coin with key " << key << " removed from chain and register."
           << endl;
    } catch (const exception &e) {
      cout << "Error deleting coin: " << e.what() << endl;
    }
  }

  /*
   * verify: Validates that every block in chainTree has a matching key in
   * keyRegister. Uses verifyHelper which does an in-order traversal of
   * chainTree and checks each key against keyRegister.
   * Returns true if all keys are synced, false otherwise.
   */
  bool verify() {
    // Cannot use vector — only BSTs allowed; verifyHelper does in-order
    // traversal of chainTree and checks each block's key against the
    // keyRegister tree
    return verifyHelper(chainTree.getRoot());
  }

  /*
   * displayDescending: Prints both the chain blocks and the key register
   * entries in descending key order using reverse in-order traversal helpers.
   */
  void displayDescending() {
    displayDescendingHelperForChain(chainTree.getRoot());
    displayDescendingHelperForRegister(keyRegister.getRoot());
  }
};
