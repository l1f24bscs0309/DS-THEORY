#include <iostream>
#include <string>
using namespace std;
#include "Node.h"
#include "MyStack.h"
#include "AVLTree.h"
#include "MaxHeap.h"
#include "UserPair.h"


// displayTable: prints all user ID-password pairs in sorted order by ID
// it uses an iterative inorder traversal of the AVL tree to print the pairs in sorted order by ID, with a header and formatting for readability.
void displayTable(Node<UserPair> *root) {
    if (!root) {
        cout << "  (no users)\n";
        return;
    }

    cout << "\n"
         << "User ID              Password\n";

    MyStack<Node<UserPair> *> st(128);
    Node<UserPair> *cur = root;
    while (cur || !st.isEmpty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        st.pop(cur);

        string id  = cur->data.id;
        string pwd = cur->data.password;


        cout << id << "\t\t" << pwd << "\n";
        cur = cur->right;
    }
}

#include "UserAVL.h"

int main() {
    const int HEAP_CAP = 100;
    MaxHeap<string> ID(HEAP_CAP);
    UserAVL password;

    // this thing is simple menu that is not important to the assignment, so i won't comment it much
    // it allows user to add, remove, search, and display user ID-password pairs using the AVL tree and max heap for storage and retrieval.
    // simple itc concept
    int choice;
    do {
        cout << "1. Add new user\n";
        cout << "2. Remove user\n";
        cout << "3. Search password by user ID\n";
        cout << "4. Display all users\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string uid, pwd;
            cout << "Enter User ID   : ";
            getline(cin, uid);
            cout << "Enter Password  : ";
            getline(cin, pwd);

            if (uid.empty() || pwd.empty()) {
                cout << "  [!] ID and password cannot be empty.\n";
                continue;
            }

            if (password.findByID(uid)) {
                cout << "  [!] User '" << uid << "' already exists.\n";
                continue;
            }

            ID.insert(uid);
            password.insert(UserPair(uid, pwd));
            cout << "  [+] User '" << uid << "' added successfully.\n";

        } else if (choice == 2) {
            string uid;
            cout << "Enter User ID to remove: ";
            getline(cin, uid);

            if (!password.findByID(uid)) {
                cout << "  [!] User '" << uid << "' not found.\n";
                continue;
            }

            ID.remove(uid);
            password.remove(UserPair(uid, ""));
            cout << "  [-] User '" << uid << "' removed.\n";

        } else if (choice == 3) {
            string uid;
            cout << "Enter User ID to search: ";
            getline(cin, uid);

            UserPair *found = password.findByID(uid);
            if (found) {
                cout << "  [*] Password for '" << uid << "': " << found->password << "\n";
            } else {
                cout << "  [!] User '" << uid << "' not found.\n";
            }

        } else if (choice == 4) {
            password.showTable();

        } else if (choice != 0) {
            cout << "  [!] Invalid choice.\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
