// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT THREE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
//

#include <iostream>
#include <fstream>
#include "CircularQueue.h"
#include "MyStack.h"

using namespace std;

#define MAX_Q_SIZE 100

void copy(CircularQueue<int> source, CircularQueue<int> & destination) {
    CircularQueue<int> temp(source);
    while (!temp.isEmpty()) {
        destination.enqueue(temp.dequeue());
    }
}

bool compare(CircularQueue<int> A, CircularQueue<int> B) {
    CircularQueue<int> copyA(A);
    CircularQueue<int> copyB(B);

    while (!copyA.isEmpty() && !copyB.isEmpty()) {
        int valA = copyA.dequeue();
        int valB = copyB.dequeue();
        if (valA != valB) return false;
    }
    return (copyA.isEmpty() && copyB.isEmpty());
}

void deleteValues(CircularQueue<int> & values, const int & noOfValues, const int & index) {
    CircularQueue<int> result(MAX_Q_SIZE);
    int pos = 0;

    while (!values.isEmpty()) {
        int val = values.dequeue();
        if (pos < index || pos >= index + noOfValues) {
            result.enqueue(val);
        }
        pos++;
    }

    while (!result.isEmpty()) values.enqueue(result.dequeue());
}

void insertQueue(CircularQueue<int> source, CircularQueue<int> & destination, const int & index) {
    CircularQueue<int> result(MAX_Q_SIZE);
    int pos = 0;

    while (!destination.isEmpty()) {
        if (pos == index) {
            CircularQueue<int> srcCopy(source);
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

CircularQueue<int> frequency(CircularQueue<int> source) {
    int maxVal = 0;
    CircularQueue<int> temp(MAX_Q_SIZE);

    while (!source.isEmpty()) {
        int v = source.dequeue();
        if (v > maxVal) maxVal = v;
        temp.enqueue(v);
    }

    while (!temp.isEmpty()) source.enqueue(temp.dequeue());

    CircularQueue<int> freqQ(maxVal + 1);
    for (int i = 0; i <= maxVal; i++) freqQ.enqueue(0);

    while (!source.isEmpty()) {
        int v = source.dequeue();
        temp = CircularQueue<int>(MAX_Q_SIZE);

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

    CircularQueue<int> digitQ(MAX_Q_SIZE);
    int temp = num;

    while (temp > 0) {
        digitQ.enqueue(temp % 10);
        temp /= 10;
    }

    CircularQueue<int> copyQ(digitQ);

    MyStack<int> stack(MAX_Q_SIZE);
    while (!digitQ.isEmpty()) {
        stack.push(digitQ.dequeue());
    }

    bool isPalindrome = true;
    int val;

    while (!stack.isEmpty()) {
        stack.pop(val);
        if (val != copyQ.dequeue()) {
            isPalindrome = false;
            break;
        }
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

    CircularQueue<char> mainQ(MAX_Q_SIZE);
    char ch;

    while (inFile.get(ch)) mainQ.enqueue(ch);
    inFile.close();

    CircularQueue<char> charQ(MAX_Q_SIZE);
    CircularQueue<int>  freqQ(MAX_Q_SIZE);

    while (!mainQ.isEmpty()) {
        char c = mainQ.dequeue();
        bool found = false;

        CircularQueue<char> tmpC(MAX_Q_SIZE);
        CircularQueue<int>  tmpF(MAX_Q_SIZE);

        while (!charQ.isEmpty()) {
            char ec = charQ.dequeue();
            int  ef = freqQ.dequeue();

            if (ec == c) {
                ef++;
                found = true;
            }

            tmpC.enqueue(ec);
            tmpF.enqueue(ef);
        }

        while (!tmpC.isEmpty()) {
            charQ.enqueue(tmpC.dequeue());
            freqQ.enqueue(tmpF.dequeue());
        }

        if (!found) {
            charQ.enqueue(c);
            freqQ.enqueue(1);
        }
    }

    cout << "Character Frequencies:\n";

    while (!charQ.isEmpty()) {
        char ec = charQ.dequeue();
        int  ef = freqQ.dequeue();

        if (ec == '\n')      cout << "'\\n' appears " << ef << " time(s)\n";
        else if (ec == ' ')  cout << "' '  appears " << ef << " time(s)\n";
        else                 cout << "'" << ec << "' appears " << ef << " time(s)\n";
    }
}


int main() {

    CircularQueue<int> q1(MAX_Q_SIZE);
    CircularQueue<int> q2(MAX_Q_SIZE);

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

    cout << "\n--- Delete Values ---\n";
    deleteValues(q2, 2, 1);

    cout << "\n--- Insert Queue ---\n";
    insertQueue(q1, q2, 1);

    cout << "\n--- Palindrome Check ---\n";
    palindromeCheck();

    cout << "\n--- Character Frequency ---\n";
    charFrequency();

    return 0;
}
