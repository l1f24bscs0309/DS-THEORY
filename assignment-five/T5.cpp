// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "NSTNode.h"
#include "NSearchTree.h"

/*
PROBLEM DESCRIPTION:
Implement and test an N-ary Search Tree (NSearchTree) where each node can hold
up to N children. The tree supports the following operations:
1. Check if the tree is empty
2. Insert values (with duplicate detection)
3. Display the tree structure
4. Search for a value
5. Remove a value (with handling for non-existent values)

SOLUTION:

isEmpty
--------
1. Check if the root of the NSearchTree is null
2. Return true if the tree has no nodes, false otherwise

insert
-------
1. Traverse the tree using the N-ary search property to find the correct position
2. If the value already exists in the tree, print a duplicate message and do not insert
3. Otherwise, create a new NSTNode and place it in the correct child slot

display
--------
1. Traverse the tree and print all nodes in a structured format
2. Each node shows its value and its children's positions

search
-------
1. Traverse the tree using the N-ary search property
2. Compare the target value at each node's keys
3. Return true if the value is found, false otherwise

remove
-------
1. Search for the node containing the target value
2. If not found, print a not-found message and do nothing
3. If found, remove the value and restructure the node or the tree accordingly

##################################################################

Main demonstrates:
- Creating an N-ary Search Tree with branching factor 4
- Verifying isEmpty on an empty tree
- Inserting 13 values and displaying the tree
- Attempting to insert a duplicate value
- Searching for values that exist and do not exist
- Removing values including a leaf, an internal node, the root, and a non-existent value
- Displaying the tree after all removals
*/

/********* MAIN FUNCTION *********/

int main() {
    // Create an N-ary Search Tree with a branching factor of 4 (each node has up to 4 children)
    NSearchTree<int> tree(4);

    // --- Check if tree is empty before any insertions ---
    cout << "isEmpty : " << (tree.isEmpty() ? "true" : "false") << "\n";

    // --- Insert 13 values into the N-ary Search Tree ---
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65};
    for (int v : vals)
        tree.insert(v);
    // Display tree structure after all insertions
    tree.display();

    // --- Attempt to insert a duplicate value (30 already exists) ---
    cout << "\nInserting duplicate: ";
    tree.insert(30);

    // --- Search for values: two that exist and one that does not ---
    cout << "Search 40 : " << (tree.search(40) ? "Found" : "Not Found") << "\n";
    cout << "Search 55 : " << (tree.search(55) ? "Found" : "Not Found") << "\n";
    cout << "Search 99 : " << (tree.search(99) ? "Found" : "Not Found") << "\n";  // does not exist

    // --- Remove values from the tree ---
    tree.remove(10);   // leaf node removal
    tree.remove(30);   // internal node removal
    tree.remove(50);   // root node removal
    tree.remove(999);  // non-existent value — should be handled gracefully

    // --- Display tree after all removals ---
    cout << "\nAfter removals:\n";
    tree.display();

    return 0;
}
