#include <iostream>
#include <fstream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"


// read words from a file store in bst and treat upper and lower case differently.
// opens the file passed in the function and reads each word from the file. 
// Each word is then inserted into the binary search tree (BST) using the insert function of the BST class. 
// The function continues reading and inserting words until the end of the file is reached. Finally, the file is closed.
void readFileAndStoreInBST(const string &filename, BinarySearchTree<string> &bst) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        bst.insert(word);
    }

    file.close();
}

// helper function to write the words in sorted order to a file
// just does a simple in-order traversal of the BST and writes each word to the specified output file.
void writeInOrder(Node<string> *node, ofstream &file) {
    if (node == nullptr) {
        return;
    }
    writeInOrder(node->left, file);
    file << node->data << endl;
    writeInOrder(node->right, file);
}

// writing words from bst to a file in sorted order
// calls the writeInOrder function to perform an in-order traversal of the BST and write the words to the specified output file.
void writeBSTToFile(const string &filename, BinarySearchTree<string> &bst) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    writeInOrder(bst.getRoot(), file);
}

// search a word from bst
bool searchWordInBST(const string &word, BinarySearchTree<string> &bst) {
    return bst.search(word);
}

// delete a word from bst
void deleteWordFromBST(const string &word, BinarySearchTree<string> &bst) {
    bst.remove(word);
}

void insertWordInBST(const string &word, BinarySearchTree<string> &bst) {
    bst.insert(word);
}

// helper function to convert the case of a word and insert it into the BST
// checks the word passed in it function definition
// if the word is empty, it returns. Otherwise, it converts the first character of the word to uppercase and the rest of the characters to lowercase.
// The converted word is then inserted into the BST using the insert function of the BST class.
void convertCaseAndInsert(const string &word, BinarySearchTree<string> &bst) {
    if (word.empty()) return;

    if (word[0] >= 'A' && word[0] <= 'Z') {
        // Convert to lowercase
        string lowerWord = word;
        for (char &c : lowerWord) {
            c = tolower(c);
        }

        if (!bst.search(lowerWord)) {
            bst.insert(lowerWord);
        }

    } else if (word[0] >= 'a' && word[0] <= 'z') {
        // Convert to uppercase
        string upperWord = word;
        for (char &c : upperWord) {
            c = toupper(c);
        }
        if (!bst.search(upperWord)) {
            bst.insert(upperWord);
        }
    } else {
        // If the first character is not a letter, insert as is
        bst.insert(word);
    }
}

// takes words from the original BST, converts their case, and inserts them into a new BST.
// The function performs an in-order traversal of the original BST and for each word, it calls the convertCaseAndInsert function to convert the case and insert it into the new BST.
void processWordAndInsert(Node<string>* node,BinarySearchTree<string> &bst) {
    if (node == nullptr) {
        return;
    }
    string word = node->data;
    convertCaseAndInsert(word, bst);
    processWordAndInsert(node->left, bst);
    processWordAndInsert(node->right, bst);
}

int main () {
    
    BinarySearchTree<string> bst;

    // Read words from the file and store them in the BST
    readFileAndStoreInBST("input.txt", bst);
    bst.display();

    // Write the words in sorted order to a new file
    writeBSTToFile("output.txt", bst);

    // Search for a word in the BST
    string searchWord = "IKRAM"; // Change this to the word you want to search
    if (searchWordInBST(searchWord, bst)) {
        cout << searchWord << " found in the BST." << endl;
    } else {
        cout << searchWord << " not found in the BST." << endl;
    }

    // Delete a word from the BST
    string deleteWord = "example"; // Change this to the word you want to delete
    deleteWordFromBST(deleteWord, bst);
    cout << deleteWord << " deleted from the BST." << endl;
    bst.display();

    // Insert a new word into the BST
    string insertWord = "newword"; // Change this to the word you want to insert
    insertWordInBST(insertWord, bst);
    cout << insertWord << " inserted into the BST." << endl;
    bst.display();

    BinarySearchTree<string> bst2;
    cout << "\nConverting case and inserting words into the BST:" << endl;
    processWordAndInsert(bst.getRoot(), bst2);
    bst2.display();

    return 0;
}


































