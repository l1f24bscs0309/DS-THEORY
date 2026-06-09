// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "ListNode.h"
#include "DoublyLinkedList.h"
#include "ConcreteDoublyLinkedList.h"

/*
PROBLEM DESCRIPTION:
Perform the following operations on a Binary Search Tree:
1. Swap left and right subtrees of every node (mirror the tree)
2. Count nodes that have exactly one child
3. Split a BST into two trees at the root (left subtree and right subtree)
4. Return the subtree rooted at a node whose value matches a given value
5. Convert a BST into a Doubly Linked List using in-order traversal

SOLUTION:

swapSubTrees
-------------
1. Recursively reach the bottom of the tree (post-order)
2. At each node, swap the left and right child pointers using a temp variable
3. This mirrors the entire tree

singleChild
------------
1. Traverse every node recursively
2. At each node, check if exactly one of its children is nullptr
3. If yes, count that node and recurse into both children
4. Return the total count of such nodes

splitBinaryTree
----------------
1. Take the root node of a BST
2. Set the left child as the root of leftSplit tree
3. Set the right child as the root of rightSplit tree
4. Disconnect both children from the original root (set to nullptr)

returnTreeFromMatchingValue
-----------------------------
1. Recursively search the BST for a node whose data matches val
2. Use BST property: go left if val < root->data, go right otherwise
3. Return the pointer to the matching node (which is the root of a subtree)

convertToList
--------------
1. Traverse the BST in-order (left -> root -> right)
2. At each node, insert the node's data at the front of the doubly linked list
3. The result is a linked list containing all BST values
*/

/*
 * swapSubTrees: Mirrors the entire binary tree by recursively swapping
 * the left and right children of every node (post-order traversal).
 */
template <class T>
void swapSubTrees(Node<T>* node) {
    // Base case: nothing to swap at a null node
    if (node == nullptr) {
        return;
    }
    // Recurse into subtrees before swapping (post-order)
    swapSubTrees(node->left);
    swapSubTrees(node->right);
    // Swap the left and right child pointers at this node
    Node<int>* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

/*
 * singleChild: Counts and returns the number of nodes in the tree
 * that have exactly one child (either left or right, not both).
 */
int singleChild(Node<int>* node) {
    // Base case: null node contributes 0
    if (node == nullptr) {
        return 0;
    }
    // Check if exactly one child exists (XOR condition on children)
    if ((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) {
        // Count this node and continue checking in both subtrees
        return 1 + singleChild(node->left) + singleChild(node->right);
    }
    // Node has zero or two children — just recurse without counting current node
    return singleChild(node->left) + singleChild(node->right);
}

/*
 * splitBinaryTree: Splits a BST at its root into two separate BSTs.
 * leftSplit gets the left subtree, rightSplit gets the right subtree.
 * The original root is disconnected from both children.
 */
void splitBinaryTree(Node<int>* node, BinarySearchTree<int>& leftSplit, BinarySearchTree<int>& rightSplit) {
    // Nothing to split if the tree is empty
    if (node == nullptr) {
        return;
    }
    // Assign left and right children as roots of the two new trees
    leftSplit.setRoot(node->left);
    rightSplit.setRoot(node->right);
    // Disconnect the original root from both subtrees
    node->left = nullptr;
    node->right = nullptr;
}

/*
 * returnTreeFromMatchingValue: Searches the BST for a node with the given value
 * and returns a pointer to it (i.e., the root of the subtree at that node).
 * Returns nullptr if the value is not found.
 */
template <class T>
Node<T>* returnTreeFromMatchingValue(Node<T>* root, T val){
    // Base case: value not found in this path
    if (root == nullptr) return nullptr;

    // Found the matching node — return it as subtree root
    if (root->data == val) return root;
    // Use BST property to decide which direction to search
    if (val < root->data)
    return returnTreeFromMatchingValue(root->left, val);
    else
    return returnTreeFromMatchingValue(root->right, val);
}

/*
 * convertToList: Converts a BST into a Doubly Linked List using in-order traversal.
 * Each node's data is inserted at the front of the list.
 */
template <class T>
void convertToList(Node<T>* node, ConcreteDoublyLinkedList<T>& list) {
    // Base case: nothing to insert for a null node
    if (node == nullptr) {
        return;
    }
    // In-order: left subtree first
    convertToList(node->left, list);
    // Insert current node's data into the linked list
    list.insertAtFirst(node->data);
    // Then right subtree
    convertToList(node->right, list);
}

/********* MAIN FUNCTION *********/

int main () {
    // --- Task 1: Swap Subtrees ---
    // Build a BST with 7 nodes
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

    // Mirror the tree by swapping every node's children
    swapSubTrees<int>(bst.getRoot());

    cout << "\nSwapped tree (in-order): ";
    bst.preorderDisplay();

    // --- Task 2: Count Single-Child Nodes ---
    int count = singleChild(bst.getRoot());
    cout << "\nNumber of nodes with exactly one child: " << count << endl;

    // --- Task 3: Split BST ---
    // Build a separate BST to split
    BinarySearchTree<int> splitThis;
    splitThis.insert(5);
    splitThis.insert(3);
    splitThis.insert(7);
    splitThis.insert(2);
    splitThis.insert(4);

    cout << "\nTree to split : ";
    splitThis.preorderDisplay();

    // Split into left and right subtrees at the root
    BinarySearchTree<int> leftSplit, rightSplit; 
    splitBinaryTree(splitThis.getRoot(), leftSplit, rightSplit);
    cout << "\nLeft split tree : ";
    leftSplit.preorderDisplay();
    cout << "\nRight split tree: ";
    rightSplit.preorderDisplay();

    // --- Task 4: Return Subtree at Matching Value ---
    BinarySearchTree<int> findSubtree;
    findSubtree.insert(5);
    findSubtree.insert(3);
    findSubtree.insert(7);
    findSubtree.insert(2);
    findSubtree.insert(4);
    cout << "\nSubtree rooted at given value: ";
    // Find the node with value 3 and treat it as the root of a new BST
    Node<int>* matchingNode = returnTreeFromMatchingValue(findSubtree.getRoot(), 3);
    BinarySearchTree<int> subtree;
    subtree.setRoot(matchingNode);
    subtree.preorderDisplay();
    // Disconnect the subtree reference to avoid double-free on destruction
    subtree.setRoot(nullptr);

    // --- Task 5: Convert BST to Doubly Linked List ---
    BinarySearchTree<int> convertThis;
    convertThis.insert(10);
    convertThis.insert(5);
    convertThis.insert(3);
    convertThis.insert(99);
    convertThis.insert(7);
    convertThis.insert(2);
    cout << "\nTree to convert: ";
    convertThis.preorderDisplay();
    // Perform in-order traversal and populate the doubly linked list
    ConcreteDoublyLinkedList<int> list;
    convertToList(convertThis.getRoot(), list);
    cout << "\nConverted list: ";
    list.display();

    return 0;
}
