// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT THREE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
//
//
// TASK 7  — Global functions on Queue ADT:
//   a) copy        : copies source queue into destination
//   b) compare     : compares two queues for equality
//   c) deleteValues: deletes noOfValues elements starting from index (0=front)
//   d) insertQueue : inserts source queue into destination at given index
//   e) frequency   : returns a queue of frequencies of each integer value
//
// TASK 8  — Application programs:
//   a) palindromeCheck : reads integer, separates digits into queue, checks palindrome
//   b) charFrequency   : reads text.txt char by char into queue, counts frequencies

#include <iostream>
#include <fstream>
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;

#define MAX_Q_SIZE 100

void copy(MyQueue<int> source, MyQueue<int> & destination) {
    // Dequeue from source and enqueue into destination until source is empty
    MyQueue<int> temp(source);
    while (!temp.isEmpty()) {
        destination.enqueue(temp.dequeue());
    }
}

bool compare(MyQueue<int> A, MyQueue<int> B) {
    // Dequeue both simultaneously and compare
    MyQueue<int> copyA(A);
    MyQueue<int> copyB(B);
    if (copyA.isEmpty() != copyB.isEmpty()) return false;
    while (!copyA.isEmpty() && !copyB.isEmpty()) {
        int valA = copyA.dequeue();
        int valB = copyB.dequeue();
        if (valA != valB) return false;
    }
    return (copyA.isEmpty() && copyB.isEmpty());
}

void deleteValues(MyQueue<int> & values, const int & noOfValues, const int & index) {
    MyQueue<int> result(MAX_Q_SIZE);
    int pos = 0;
    while (!values.isEmpty()) {
        int val = values.dequeue();
        if (pos < index || pos >= index + noOfValues) {
            result.enqueue(val);
        }
        pos++;
    }
    // Restore original queue reference
    while (!result.isEmpty()) values.enqueue(result.dequeue());
}

void insertQueue(MyQueue<int> source, MyQueue<int> & destination, const int & index) {
    MyQueue<int> result(MAX_Q_SIZE);
    int pos = 0;

    while (!destination.isEmpty()) {
        if (pos == index) {
            MyQueue<int> srcCopy(source);   
            while (!srcCopy.isEmpty()) result.enqueue(srcCopy.dequeue());
        }
        result.enqueue(destination.dequeue());
        pos++;
    }
    if (index >= pos) {
        while (!source.isEmpty()) result.enqueue(source.dequeue());
    }

    while (!result.isEmpty()) destination.enqueue(result.dequeue());
}

MyQueue<int> frequency(MyQueue<int> source) {
    int maxVal = 0;
    MyQueue<int> temp(MAX_Q_SIZE);
    while (!source.isEmpty()) {
        int v = source.dequeue();
        if (v > maxVal) maxVal = v;
        temp.enqueue(v);
    }
    // Restore source from temp
    while (!temp.isEmpty()) source.enqueue(temp.dequeue());

    MyQueue<int> freqQ(maxVal + 1);
    for (int i = 0; i <= maxVal; i++) freqQ.enqueue(0);

    while (!source.isEmpty()) {
        int v = source.dequeue();
        temp = MyQueue<int>(MAX_Q_SIZE);
        int idx = 0;
        while (!freqQ.isEmpty()) {
            int cnt = freqQ.dequeue();
            if (idx == v) cnt++;
            temp.enqueue(cnt);
            idx++;
        }
        while (!temp.isEmpty()) freqQ.enqueue(temp.dequeue());
    }
    return freqQ;
}

void palindromeCheck() {
    cout << "Enter an integer: ";
    int num;
    cin >> num;

    MyQueue<int> digitQ(MAX_Q_SIZE);
    while (num > 0) {
        digitQ.enqueue(num % 10);
        num /= 10;
    }

    MyStack<int> tempStack(MAX_Q_SIZE);
    while (!digitQ.isEmpty()) {
        tempStack.push(digitQ.dequeue());
    }

    bool isPalindrome = true;
    while (!tempStack.isEmpty()) {
        if (tempStack.top() != digitQ.dequeue()) {
            isPalindrome = false;
            break;
        }
        tempStack.pop(num); // pop to move to next
    }

    if (isPalindrome) cout << "The number is a palindrome.\n";
    else              cout << "The number is NOT a palindrome.\n";
}

void charFrequency() {
    ifstream inFile("text.txt");
    if (!inFile) {
        cout << "Error: cannot open text.txt\n";
        return;
    }

    MyQueue<char> mainQ(MAX_Q_SIZE);
    char ch;
    while (inFile.get(ch)) mainQ.enqueue(ch);
    inFile.close();

    MyQueue<char> charQ(MAX_Q_SIZE);
    MyQueue<int>  freqQ(MAX_Q_SIZE);

    while (!mainQ.isEmpty()) {
        char c = mainQ.dequeue();
        bool found = false;

        MyQueue<char> tmpC(MAX_Q_SIZE);
        MyQueue<int>  tmpF(MAX_Q_SIZE);

        while (!charQ.isEmpty()) {
            char ec = charQ.dequeue();
            int  ef = freqQ.dequeue();
            if (ec == c) { ef++; found = true; }
            tmpC.enqueue(ec);
            tmpF.enqueue(ef);
        }
        while (!tmpC.isEmpty()) { charQ.enqueue(tmpC.dequeue()); freqQ.enqueue(tmpF.dequeue()); }

        if (!found) { charQ.enqueue(c); freqQ.enqueue(1); }
    }

    cout << "Character Frequencies:\n";
    while (!charQ.isEmpty()) {
        char ec = charQ.dequeue();
        int  ef = freqQ.dequeue();
        if (ec == '\n')      cout << "'\\n' appears " << ef << " time(s)\n";
        else if (ec == ' ')  cout << "' '  appears " << ef << " time(s)\n";
        else                 cout << "'" << ec << "'  appears " << ef << " time(s)\n";
    }
}


int main() {

    MyQueue<int> q1(MAX_Q_SIZE);
    MyQueue<int> q2(MAX_Q_SIZE);

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(2);
    q1.enqueue(1);

    cout << "\n--- Copy Function ---\n";
    copy(q1, q2);


    cout << "\n--- Compare Function ---\n";
    if (compare(q1, q2))
        cout << "Queues are equal.\n";
    else
        cout << "Queues are NOT equal.\n";

    deleteValues(q2, 2, 1); // delete 2 elements from index 1

    insertQueue(q1, q2, 1);
    cout << "Inserted q1 into q2 at index 1.\n";

    // MyQueue<int> freqQ = frequency(q1);

    palindromeCheck();

    charFrequency();

    return 0;
}






