#include <iostream>
using namespace std;
#include <fstream>
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

template <class T>
void readFromFile(BinarySearchTree<T>& bst, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    T value;
    while (file >> value) {
        bst.insert(value);
    }
    file.close();
}

void inorderWrite(Node<string>* node, ofstream& file) {
    if (node == nullptr) {
        return;
    }
    inorderWrite(node->left, file);
    file << node->data << endl;
    inorderWrite(node->right, file);
}

void writeToFile(BinarySearchTree<string>& bst, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    inorderWrite(bst.getRoot(),file);
    file.close();
}

bool searchValue(BinarySearchTree<string>& bst, const string& value) {
    return bst.search(value);
}

void deleteValue(BinarySearchTree<string>& bst, const string& value) {
    if (bst.search(value)) {
        bst.remove(value);
        cout << "Value '" << value << "' has been deleted from the binary search tree." << endl;
    } else {
        cout << "Value '" << value << "' not found in the binary search tree. Cannot delete." << endl;
    }
}

void insertValue(BinarySearchTree<string>& bst, const string& value) {
    bst.insert(value);
    cout << "Value '" << value << "' has been inserted into the binary search tree." << endl;
}

void traverseAndConvertValue(Node<string>* node, BinarySearchTree<string>& convertedBST) {
    if (node == nullptr) {
        return;
    }
    string convertedValue = node->data;
    if(convertedValue[0] >= 'a' && convertedValue[0] <= 'z') {
        for (char& c : convertedValue) {
            c = toupper(c);
        }
    }else if(convertedValue[0] >= 'A' && convertedValue[0] <= 'Z') {
        for (char& c : convertedValue) {
            c = tolower(c);
        }
    }
    convertedBST.insert(convertedValue);
    traverseAndConvertValue(node->left, convertedBST);
    traverseAndConvertValue(node->right, convertedBST);
}

int main () {
    const string filename =  "ai.txt";
    BinarySearchTree<string> bst;
    readFromFile(bst, filename);
    cout << "In-order traversal of the binary search tree:" << endl;
    bst.inorderDisplay();

    const string outputFilename = "output.txt";
    writeToFile(bst, outputFilename);
    cout << "\nBinary search tree has been written to " << outputFilename << endl;

    if (searchValue(bst, "example")) {
        cout << "The value 'example' exists in the tree." << endl;
    } else {
        cout << "The value 'example' does not exist in the tree." << endl;
    }

    deleteValue(bst, "to");
    insertValue(bst, "newvalue");
    cout << "\nIn-order traversal of the binary search tree after modifications:" << endl;
    bst.inorderDisplay();

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
    traverseAndConvertValue(originalBST.getRoot(), convertedBST);
    cout << "\nIn-order traversal of the converted binary search tree:" << endl;
    convertedBST.inorderDisplay();


}



























