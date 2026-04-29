// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT THREE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

/*
PROBLEM DESCRIPTION:
Task 3: MyStack class (from header) tested with main
Task 4: Global functions using Stack ADT:
    a) copy    - copies one stack into another
    b) compare - compares two stacks for equality
    c) deleteValues - deletes noOfValues from a given index by shifting downward
    d) insert  - inserts one stack into another at a given position by shifting up
    e) frequency - returns a stack of frequencies of each value
Task 5:
    a) Read an integer, separate digits into a stack, check palindrome using TWO stacks
    b) Read text.txt character by character into a stack, display character frequencies

SOLUTION PLAN:
Task 4: Since Stack only gives push/pop/top, to access index-based operations
         we must pop elements into a temp, manipulate, then restore.
Task 5a: push digits of number into stack1, copy to stack2, compare popped from
         stack1 with popped from stack2 (reversed) to check palindrome.
Task 5b: push each char from file into stack, then use a second stack/counting
         approach to tally frequencies per character.
*/

#include <iostream>
#include <fstream>
#include "MyStack.h"
using namespace std;
#define MAX_STACK_SIZE 100
/********* GLOBAL FUNCTION PROTOTYPES *********/

void copyStack(MyStack<int>& source, MyStack<int>& destination);
bool compareStack(MyStack<int>& A, MyStack<int>& B);
void deleteValues(MyStack<int>& st, const int& noOfValues, const int& index);
void insertStack(MyStack<int>& source, MyStack<int>& destination, const int& index);
MyStack<int> frequency(MyStack<int>& source);
void palindromeCheck();
void charFrequency();

/********* GLOBAL FUNCTION CODE *********/

void copyStack(MyStack<int>& source, MyStack<int>& destination) {
    // pop all from source into a temp to reverse order, then push into destination
    MyStack<int> temp(MAX_STACK_SIZE);
    MyStack<int> src(source);
    int val;
    while (!src.isEmpty()) {
        src.pop(val);
        temp.push(val);
    }
    while (!temp.isEmpty()) {
        temp.pop(val);
        destination.push(val);
    }
}

bool compareStack(MyStack<int>& A, MyStack<int>& B) {
    // pop both stacks simultaneously and compare each element
    // stacks are equal if all elements match in the same order
    MyStack<int> copyA(A);
    MyStack<int> copyB(B);
    if (copyA.isEmpty() != copyB.isEmpty()) return false;
    int valA, valB;
    while (!copyA.isEmpty() && !copyB.isEmpty()) {
        copyA.pop(valA);
        copyB.pop(valB);
        if (valA != valB) return false;
    }
    return (copyA.isEmpty() && copyB.isEmpty());
}

void deleteValues(MyStack<int>& st, const int& noOfValues, const int& index) {
    // pop all into temp to reverse order, skip values to delete, then push back
    MyStack<int> temp(MAX_STACK_SIZE);
    MyStack<int> copy(st);
    int val;
    int size = 0;
    while (!copy.isEmpty()) {
        copy.pop(val);
        temp.push(val);
        size++;
    }
    // skip noOfValues starting from index (index 0 = bottom)
    MyStack<int> result(MAX_STACK_SIZE);
    for (int i = 0; i < size; i++) {
        temp.pop(val);
        if (i < index || i >= index + noOfValues) {
            result.push(val);
        }
    }
    // push back into original stack
    while (!result.isEmpty()) {
        result.pop(val);
        st.push(val);
    }
}

void insertStack(MyStack<int>& source, MyStack<int>& destination, const int& index) {
    // pop destination into temp to reverse, insert source values at index, then push back
    MyStack<int> temp(MAX_STACK_SIZE);
    MyStack<int> destCopy(destination);
    int val;
    int destSize = 0;
    while (!destCopy.isEmpty()) {
        destCopy.pop(val);
        temp.push(val);
        destSize++;
    }
    // push source values into result stack at index
    MyStack<int> result(MAX_STACK_SIZE);
    int srcSize = 0;
    MyStack<int> srcCopy(source);
    while (!srcCopy.isEmpty()) {
        srcCopy.pop(val);
        result.push(val);
        srcSize++;
    }
    // push destination values back, inserting source at index
    for (int i = 0; i < destSize; i++) {
        if (i == index) {
            // insert source values
            MyStack<int> srcTemp(result);
            while (!srcTemp.isEmpty()) {
                srcTemp.pop(val);
                destination.push(val);
            }
        }
        temp.pop(val);
        destination.push(val);
    }
     // if index is beyond current size, just push source at the end
     if (index >= destSize) {
         MyStack<int> srcTemp(result);
         while (!srcTemp.isEmpty()) {
             srcTemp.pop(val);
             destination.push(val);
         }
     }
}

MyStack<int> frequency(MyStack<int>& source) {
    // find max value to size frequency stack, then count occurrences
    MyStack<int> copy(source);
    int maxVal = 0;
    int val;
    while (!copy.isEmpty()) {
        copy.pop(val);
        if (val > maxVal) maxVal = val;
    }
    MyStack<int> freq(maxVal + 1);
    // initialize frequency stack with 0s
    for (int i = 0; i <= maxVal; i++) {
        freq.push(0);
    }
    // count occurrences
    MyStack<int> srcCopy(source);
    while (!srcCopy.isEmpty()) {
        srcCopy.pop(val);
        // increment frequency at index = val
        MyStack<int> temp(MAX_STACK_SIZE);
        int idx = 0;
        while (!freq.isEmpty()) {
            freq.pop(val);
            if (idx == val) {
                val++; // increment frequency count
            }
            temp.push(val);
            idx++;
        }
        // restore freq stack
        while (!temp.isEmpty()) {
            temp.pop(val);
            freq.push(val);
        }
    }
    return freq;
}

void palindromeCheck() {
    // read an integer, push digits into stack1, copy to stack2, compare popped from both
    cout << "\n-- Task 5a: Palindrome Check --" << endl;
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    MyStack<int> stack1(MAX_STACK_SIZE);
    MyStack<int> stack2(MAX_STACK_SIZE);

    // push digits of number into stack1
    int tempNum = num;
    while (tempNum > 0) {
        int digit = tempNum % 10;
        stack1.push(digit);
        tempNum /= 10;
    }

    // copy stack1 to stack2
    copyStack(stack1, stack2);

    // compare popped from both stacks
    bool isPalindrome = true;
    while (!stack1.isEmpty() && !stack2.isEmpty()) {
        int d1, d2;
        stack1.pop(d1);
        stack2.pop(d2);
        if (d1 != d2) {
            isPalindrome = false;
            break;
        }
    }
    if (isPalindrome) {
        cout << num << " is a palindrome." << endl;
    } else {
        cout << num << " is not a palindrome." << endl;
    }
}

void charFrequency() {
    cout << "\n-- Task: Character Frequency (Stack Only) --" << endl;

    ifstream inFile("text.txt");
    if (!inFile) {
        cout << "Error opening file text.txt" << endl;
        return;
    }

    MyStack<char> mainStack(MAX_STACK_SIZE);
    char ch;

    // Step 1: Push all characters into main stack
    while (inFile.get(ch)) {
        mainStack.push(ch);
    }
    inFile.close();

    // Step 2: Two stacks → one for chars, one for frequencies
    MyStack<char> charStack(MAX_STACK_SIZE);
    MyStack<int> freqStack(MAX_STACK_SIZE);

    // Step 3: Process each character
    while (!mainStack.isEmpty()) {
        mainStack.pop(ch);

        MyStack<char> tempChar(MAX_STACK_SIZE);
        MyStack<int> tempFreq(MAX_STACK_SIZE);

        bool found = false;
        char c;
        int f;

        // Search if character already exists
        while (!charStack.isEmpty()) {
            charStack.pop(c);
            freqStack.pop(f);

            if (c == ch) {
                f++;        // increment frequency
                found = true;
            }

            tempChar.push(c);
            tempFreq.push(f);
        }

        // Restore stacks
        while (!tempChar.isEmpty()) {
            tempChar.pop(c);
            tempFreq.pop(f);
            charStack.push(c);
            freqStack.push(f);
        }

        // If not found, add new character
        if (!found) {
            charStack.push(ch);
            freqStack.push(1);
        }
    }

    // Step 4: Display result
    cout << "Character Frequencies:\n";
    char c;
    int f;

    while (!charStack.isEmpty()) {
        charStack.pop(c);
        freqStack.pop(f);
        cout << "'" << c << "' appears " << f << " time(s)\n";
    }
}

/********* DRIVER FUNCTION MAIN *********/

int main() {

    MyStack<int> s(5);
    s.push(10); s.push(20); s.push(30); s.push(40); s.push(50);
    cout << "Stack (top to bottom): "; s.display(); cout << endl;
    int v;
    s.pop(v);
    cout << "Popped: " << v << endl;
    cout << "Top: " << s.top() << endl;


    MyStack<int> src(4);
    src.push(1); src.push(2); src.push(3); src.push(4);
    MyStack<int> dest(4);
    cout << "source (top to bottom): "; src.display(); cout << endl;
    copyStack(src, dest);
    cout << "destination after copy (top to bottom): "; dest.display(); cout << endl;

    MyStack<int> A(3); A.push(1); A.push(2); A.push(3);
    MyStack<int> B(3); B.push(1); B.push(2); B.push(3);
    MyStack<int> C(3); C.push(1); C.push(9); C.push(3);
    cout << "A: "; A.display(); cout << endl;
    cout << "B: "; B.display(); cout << endl;
    cout << "C: "; C.display(); cout << endl;
    cout << "compareStack(A, B) = " << (compareStack(A, B) ? "true" : "false") << endl;
    cout << "compareStack(A, C) = " << (compareStack(A, C) ? "true" : "false") << endl;

    MyStack<int> d(6);
    d.push(10); d.push(20); d.push(30); d.push(40); d.push(50); d.push(60);
    cout << "Before delete (top to bottom): "; d.display(); cout << endl;
    deleteValues(d, 2, 1);
    cout << "After deleteValues(2, index 1 from bottom): "; d.display(); cout << endl;

    MyStack<int> srcIns(2); srcIns.push(77); srcIns.push(88);
    MyStack<int> destIns(6); destIns.push(1); destIns.push(2); destIns.push(3); destIns.push(4);
    cout << "Source: "; srcIns.display(); cout << endl;
    cout << "Destination before insert: "; destIns.display(); cout << endl;
    insertStack(srcIns, destIns, 1);
    cout << "Destination after insert at index 1: "; destIns.display(); cout << endl;

    MyStack<int> data(8);
    data.push(3); data.push(1); data.push(2); data.push(3);
    data.push(1); data.push(3); data.push(2); data.push(1);
    cout << "Data stack (top to bottom): "; data.display(); cout << endl;
    MyStack<int> freqResult = frequency(data);
    cout << "Frequency stack (index from bottom = value, content = count):" << endl;
    MyStack<int> freqCopy(freqResult);
    MyStack<int> freqRev(MAX_STACK_SIZE);
    int fv;
    while (!freqCopy.isEmpty()) { freqCopy.pop(fv); freqRev.push(fv); }
    int idx = 0;
    while (!freqRev.isEmpty()) {
        freqRev.pop(fv);
        if (fv > 0) cout << "  value " << idx << " appears " << fv << " time(s)" << endl;
        idx++;
    }


    palindromeCheck();
    charFrequency();

    return 0;
}

