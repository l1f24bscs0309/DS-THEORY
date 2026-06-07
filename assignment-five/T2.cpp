#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

template <class T>
void swapSubTrees(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    swapSubTrees(node->left);
    swapSubTrees(node->right);
    Node<int>* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

int singleChild(Node<int>* node) {
    if (node == nullptr) {
        return 0;
    }

    if ((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) {
        return 1 + singleChild(node->left) + singleChild(node->right);
    }
    return singleChild(node->left) + singleChild(node->right);
}

void splitBinaryTree(Node<int>* node, BinarySearchTree<int>& leftSplit, BinarySearchTree<int>& rightSplit) {
    if (node == nullptr) {
        return;
    }
    leftSplit.setRoot(node->left);
    rightSplit.setRoot(node->right);
    node->left = nullptr;
    node->right = nullptr;
}

template <class T>
Node<T>* returnTreeFromMatchingValue(Node<T>* root, T val){
    if (root == nullptr) return nullptr;

    if (root->data == val) return root;
    if (val < root->data)
    return returnTreeFromMatchingValue(root->left, val);
    else
    return returnTreeFromMatchingValue(root->right, val);
}

int main () {
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    cout << "Original tree (in-order): ";
    bst.preorderDisplay();

    swapSubTrees<int>(bst.getRoot());

    cout << "\nSwapped tree (in-order): ";
    bst.preorderDisplay();

    int count = singleChild(bst.getRoot());
    cout << "\nNumber of nodes with exactly one child: " << count << endl;

    BinarySearchTree<int> splitThis;
    splitThis.insert(5);
    splitThis.insert(3);
    splitThis.insert(7);
    splitThis.insert(2);
    splitThis.insert(4);

    cout << "\nTree to split : ";
    splitThis.preorderDisplay();

    BinarySearchTree<int> leftSplit, rightSplit; 
    splitBinaryTree(splitThis.getRoot(), leftSplit, rightSplit);
    cout << "\nLeft split tree : ";
    leftSplit.preorderDisplay();
    cout << "\nRight split tree: ";
    rightSplit.preorderDisplay();

    BinarySearchTree<int> findSubtree;
    findSubtree.insert(5);
    findSubtree.insert(3);
    findSubtree.insert(7);
    findSubtree.insert(2);
    findSubtree.insert(4);
    cout << "\nSubtree rooted at given value: ";
    Node<int>* matchingNode = returnTreeFromMatchingValue(findSubtree.getRoot(), 3);
    BinarySearchTree<int> subtree;
    subtree.setRoot(matchingNode);
    subtree.preorderDisplay();
    subtree.setRoot(nullptr);
    
    return 0;
}
