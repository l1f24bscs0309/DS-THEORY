
class Blockchain {
  BinarySearchTree<BlockchainNode> chainTree;
  BinarySearchTree<KeyNode> keyRegister;

  void displayDescendingHelperForChain(Node<BlockchainNode> *node) {
    if (node == nullptr) {
      return;
    }
    displayDescendingHelperForChain(node->right);
    cout << "ID: " << node->data.id << ", Value: " << node->data.privateValue
         << ", Key: " << node->data.key << endl;
    displayDescendingHelperForChain(node->left);
  }

  void displayDescendingHelperForRegister(Node<KeyNode> *node) {
    if (node == nullptr) {
      return;
    }
    displayDescendingHelperForRegister(node->right);
    cout << "Key: " << node->data.key << endl;
    displayDescendingHelperForRegister(node->left);
  }

public:
  Blockchain() {}

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

  bool searchByKey(string key) {
    KeyNode searchKeyNode(key);
    if (!keyRegister.search(searchKeyNode)) {
      cout << "Key not found in register." << endl;
      return false;
    }

    BlockchainNode searchChainNode("", 0.0, key, "");
    if (chainTree.search(searchChainNode)) {
      return true;
    } else {
      cout << "Key not found in chain." << endl;
      return false;
    }
  }

  void deleteByKey(string key) {
    KeyNode searchKeyNode(key);
    if (!keyRegister.search(searchKeyNode)) {
      cout << "Key not found in register." << endl;
      return;
    }

    BlockchainNode searchChainNode("", 0.0, key, "");
    try {
      chainTree.remove(searchChainNode);
      keyRegister.remove(searchKeyNode);
      cout << "Coin with key " << key << " removed from chain and register."
           << endl;
    } catch (const exception &e) {
      cout << "Error deleting coin: " << e.what() << endl;
    }
  }

  // 4. verify: cross-checks every key in register against every node in chain
  // bool verify() {}

  // 5. display both trees in descending order (reverse inorder)
  void displayDescending() {
    displayDescendingHelperForChain(chainTree.getRoot());
    displayDescendingHelperForRegister(keyRegister.getRoot());
  }
};
