#include <iostream>
using namespace std;
#include "MyStack.h"
#include "Node.h"
#include "AVLTree.h"


// this is just a main file to check the avl function all the main codes
// are in the AVLTree.h file. The main function creates an AVL tree, inserts some values into it, and then prints the in-order traversal of the tree and its height.

int main () {
  AVLTree<int> avl;
  avl.insert(10);
  avl.insert(20);
  avl.insert(30);
  avl.insert(40);
  avl.insert(50);
  avl.insert(25);

  cout << "Inorder traversal of the AVL tree is: ";
  avl.inorder();
  cout << endl;

 cout << "Height of the AVL tree is: " << avl.treeHeight() << endl; 

 // remove some values and check the tree again
    avl.remove(40);

    cout << "Inorder traversal after removing 40: ";
    avl.inorder();


  return 0;
}
