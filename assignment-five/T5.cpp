#include <iostream>
using namespace std;
#include "NSTNode.h"
#include "NSearchTree.h"

int main() {

  NSearchTree<int> tree(4);

  cout << "isEmpty : " << (tree.isEmpty() ? "true" : "false") << "\n";

  int vals[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65};
  for (int v : vals)
    tree.insert(v);
  tree.display();

  cout << "\nInserting duplicate: ";
  tree.insert(30);

  cout << "Search 40 : " << (tree.search(40) ? "Found" : "Not Found") << "\n";
  cout << "Search 55 : " << (tree.search(55) ? "Found" : "Not Found") << "\n";
  cout << "Search 99 : " << (tree.search(99) ? "Found" : "Not Found") << "\n";

  tree.remove(10);
  tree.remove(30);
  tree.remove(50);
  tree.remove(999);

  cout << "\nAfter removals:\n";
  tree.display();

  return 0;
}
