// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include <fstream>
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

/*
PROBLEM DESCRIPTION:
Perform the following file and string operations on a Binary Search Tree of strings:
1. Read words from a text file and insert them into a BST
2. Write the BST's in-order traversal (sorted output) to an output file
3. Search for a specific value in the BST
4. Delete a value from the BST if it exists
5. Insert a new value into the BST
6. Convert all strings in a BST to their opposite case (uppercase <-> lowercase)
   and store the result in a new BST

SOLUTION:

readFromFile
-------------
1. Open the given file for reading
2. Read words one by one using the >> operator
3. Insert each word into the BST
4. Close the file after all words are read

inorderWrite (helper)
----------------------
1. Recursively traverse the tree in-order (left -> node -> right)
2. Write each node's data followed by a newline to the output file
3. This produces a sorted list of words in the file

writeToFile
------------
1. Open the output file for writing
2. Call inorderWrite to traverse and write the BST in sorted order
3. Close the file

searchValue
------------
1. Call the BST's built-in search function
2. Return true if found, false otherwise

deleteValue
------------
1. Check if the value exists in the BST using search
2. If found, call remove to delete it and print a confirmation message
3. If not found, print a not-found message

insertValue
------------
1. Call the BST's insert function with the given value
2. Print a confirmation message

traverseAndConvertValue
------------------------
1. Traverse the original BST recursively (pre-order)
2. For each node, check if the first character is lowercase or uppercase
3. Convert the entire string to the opposite case using toupper/tolower
4. Insert the converted string into the new convertedBST
*/

/*
 * readFromFile: Reads words from the given file one by one
 * and inserts each into the BST. Reports an error if the file
 * cannot be opened.
 */
template <class T>
void readFromFile(BinarySearchTree<T>& bst, const string& filename) {
    ifstream file(filename);
    // Check if file opened successfully before reading
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    T value;
    // Read and insert each word until end of file
    while (file >> value) {
        bst.insert(value);
    }
    file.close();
}

/*
 * inorderWrite: Helper function that recursively traverses the BST
 * in-order and writes each value to the output file on a new line.
 * In-order traversal of a BST produces values in sorted order.
 */
void inorderWrite(Node<string>* node, ofstream& file) {
    // Base case: nothing to write for a null node
    if (node == nullptr) {
        return;
    }
    // Traverse left subtree first (smaller values)
    inorderWrite(node->left, file);
    // Write current node's data to file
    file << node->data << endl;
    // Then traverse right subtree (larger values)
    inorderWrite(node->right, file);
}

/*
 * writeToFile: Opens the given output file and writes the BST's
 * contents in sorted (in-order) sequence using inorderWrite.
 */
void writeToFile(BinarySearchTree<string>& bst, const string& filename) {
    ofstream file(filename);
    // Check if file opened successfully before writing
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    // Write BST in sorted order to the file
    inorderWrite(bst.getRoot(), file);
    file.close();
}

/*
 * searchValue: Returns true if the given value exists in the BST,
 * false otherwise. Delegates to BST's built-in search method.
 */
bool searchValue(BinarySearchTree<string>& bst, const string& value) {
    return bst.search(value);
}

/*
 * deleteValue: Deletes a value from the BST if it exists.
 * Prints a confirmation message on success, or a not-found message otherwise.
 */
void deleteValue(BinarySearchTree<string>& bst, const string& value) {
    if (bst.search(value)) {
        bst.remove(value);
        cout << "Value '" << value << "' has been deleted from the binary search tree." << endl;
    } else {
        cout << "Value '" << value << "' not found in the binary search tree. Cannot delete." << endl;
    }
}

/*
 * insertValue: Inserts a new value into the BST and prints a confirmation message.
 */
void insertValue(BinarySearchTree<string>& bst, const string& value) {
    bst.insert(value);
    cout << "Value '" << value << "' has been inserted into the binary search tree." << endl;
}

/*
 * traverseAndConvertValue: Traverses the original BST recursively and
 * converts each string to its opposite case (lowercase -> UPPERCASE, UPPERCASE -> lowercase).
 * The converted strings are inserted into a new convertedBST.
 */
void traverseAndConvertValue(Node<string>* node, BinarySearchTree<string>& convertedBST) {
    // Base case: nothing to convert at a null node
    if (node == nullptr) {
        return;
    }
    string convertedValue = node->data;
    // Determine case by checking first character and convert all characters accordingly
    if(convertedValue[0] >= 'a' && convertedValue[0] <= 'z') {
        // String starts lowercase — convert entire string to uppercase
        for (char& c : convertedValue) {
            c = toupper(c);
        }
    }else if(convertedValue[0] >= 'A' && convertedValue[0] <= 'Z') {
        // String starts uppercase — convert entire string to lowercase
        for (char& c : convertedValue) {
            c = tolower(c);
        }
    }
    // Insert converted string into the new BST
    convertedBST.insert(convertedValue);
    // Continue traversal into left and right subtrees
    traverseAndConvertValue(node->left, convertedBST);
    traverseAndConvertValue(node->right, convertedBST);
}

/********* MAIN FUNCTION *********/

int main () {
    // --- Task 1: Read from file and build BST ---
    const string filename =  "ai.txt";
    BinarySearchTree<string> bst;
    readFromFile(bst, filename);
    cout << "In-order traversal of the binary search tree:" << endl;
    bst.inorderDisplay();

    // --- Task 2: Write sorted BST to output file ---
    const string outputFilename = "output.txt";
    writeToFile(bst, outputFilename);
    cout << "\nBinary search tree has been written to " << outputFilename << endl;

    // --- Task 3: Search for a value ---
    if (searchValue(bst, "example")) {
        cout << "The value 'example' exists in the tree." << endl;
    } else {
        cout << "The value 'example' does not exist in the tree." << endl;
    }

    // --- Task 4 & 5: Delete and insert values ---
    deleteValue(bst, "to");
    insertValue(bst, "newvalue");
    cout << "\nIn-order traversal of the binary search tree after modifications:" << endl;
    bst.inorderDisplay();

    // --- Task 6: Convert case of all strings into a new BST ---
    BinarySearchTree<string> originalBST;
    originalBST.insert("Hello");
    originalBST.insert("World");
    originalBST.insert("Test");
    originalBST.insert("data");
    originalBST.insert("Structure");
    originalBST.insert("example");
    BinarySearchTree<string> convertedBST;
    cout << "\nIn-order traversal of the original binary search tree:" << endl;
    originalBST.inorderDisplay();
    // Traverse the original BST and build a new one with case-flipped strings
    traverseAndConvertValue(originalBST.getRoot(), convertedBST);
    cout << "\nIn-order traversal of the converted binary search tree:" << endl;
    convertedBST.inorderDisplay();
}
