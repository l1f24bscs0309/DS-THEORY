// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT TWO
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File p1.cpp contains complete code of Stack Problem 1
// that implements global utility functions on MyStack<int>

#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"

/*
PROBLEM DESCRIPTION:
For Stack implement the following global functions and a suitable main to test them:
1. int getSize(Stack<int> * s)      - return the number of elements currently in the Stack
2. int peek(Stack<int> * s, int pos)- return the value at position pos without removing it
3. int insert(Stack<int> * s, int pos, const int & value) - insert value at position pos
4. void swap(Stack<int> * s, int i, int j)  - swap the values at positions i and j
5. void sort(Stack<int> * s, bool asc)      - sort the Stack ascending or descending

PROBLEM SOLUTION:

Stack Only Solution without functions
--------------------------------------
We will use a single stack of fixed size and manually test each operation inline in main.
For getSize:
  - make a copy of the stack using copy constructor
  - pop elements one by one while counting
  - return the count
  e.g. stack has: 10 20 30 40  => count = 4

For peek(pos):
  - position 0 means top of the stack (most recently pushed)
  - make a copy of the stack
  - pop (pos) elements to skip to the desired position
  - the next pop gives the value at that position
  e.g. stack: [10 20 30 40] top is 40
       peek(0) = 40, peek(1) = 30, peek(2) = 20

For insert(pos, value):
  - make a temporary stack
  - pop (pos) elements from original and push them in temp stack (reversing order)
  - push the new value onto original stack
  - pop all elements from temp and push them back onto original stack (restoring order)
  e.g. stack: [10 20 30] insert at pos=1, value=99
       pop 1 element (30) into temp
       push 99 onto stack => [10 20 99]
       pop from temp (30) back => [10 20 99 30]

For swap(i, j):
  - use peek to get values at i and j
  - use insert+pop logic to extract both, swap them, and put back
  - simpler approach: extract all elements into a temp stack, swap at indices, push back
  e.g. stack: [10 20 30 40] swap(0, 2) => [10 40 30 20]

For sort(asc):
  - selection sort using copies: repeatedly find min (or max) element,
    remove it from one stack, push it into result stack
  e.g. stack: [3 1 4 1 5] sort ascending => [1 1 3 4 5] (top = 5)


Stack Only Solution with functions
--------------------------------------
Functions to use:
1. getSize(Stack<int> * s)
2. peek(Stack<int> * s, int pos)
3. insert(Stack<int> * s, int pos, const int & value)
4. swap(Stack<int> * s, int i, int j)
5. sort(Stack<int> * s, bool asc)

1. Create a MyStack<int> s of size 10
   -----
   -----
   stack is empty, currentIndex = -1

2. Push some values to test:
   push 10 => [10]
   push 20 => [10 20]
   push 30 => [10 20 30]
   push 40 => [10 20 30 40]
   currentIndex = 3

3. Call getSize(&s) => returns 4

4. Call peek(&s, 1) => returns 30 (second from top)

5. Call insert(&s, 2, 99) => inserts 99 at position 2 from top
   stack becomes [10 20 99 30 40]

6. Call swap(&s, 0, 3) => swaps top and element at pos 3
   stack becomes [10 40 99 30 20]  (0-indexed from top)

7. Call sort(&s, true) => ascending, smallest at bottom, largest at top
*/

/********* GLOBAL FUNCTION PROTOTYPES *********/

int getSize(Stack<int> * s);
int peek(Stack<int> * s, int pos);
void insert(Stack<int> * s, int pos, const int & value);
void swapPositions(Stack<int> * s, int i, int j);
void sort(Stack<int> * s, bool asc);

/********* DRIVER FUNCTION MAIN *********/

int main(){
    MyStack<int> s(10);

    // push some test values
    s.push(10);
    s.push(30);
    s.push(50);
    s.push(20);
    s.push(40);

    cout << "Original Stack (top to bottom): ";
    s.display();

    cout << "peek at pos 0 (top): " << peek(&s, 0) << endl;
    cout << "peek at pos 2:       " << peek(&s, 2) << endl;
    cout << "peek at pos 4:       " << peek(&s, 4) << endl;

    insert(&s, 2, 99);
    cout << "Stack after insert: ";
    s.display();

    swapPositions(&s, 0, 4);
    cout << "Stack after swap:   ";
    s.display();

    sort(&s, true);
    cout << "Sorted ascending:  ";
    s.display();

    sort(&s, false);
    cout << "Sorted descending: ";
    s.display();

    return 0;
}

/********* GLOBAL FUNCTION CODE *********/

// returns the number of elements currently in the stack
// approach: make a copy, pop everything while counting, return count
int getSize(Stack<int> * s){
    MyStack<int> temp(*(MyStack<int>*)s);
    int count = 0;
    int val;
    while(!temp.isEmpty()){
        temp.pop(val);
        count++;
    }
    return count;
}

// returns the value at position pos (0 = top) without removing it
// approach: make a copy, skip 'pos' elements by popping, then peek the next one
int peek(Stack<int> * s, int pos){
    int size = getSize(s);

    MyStack<int> temp(*(MyStack<int>*)s);
    int val = 0;
    for(int i = 0; i <= pos; i++){
        temp.pop(val);
    }
    return val;
}

// inserts value at position pos from the top (0 = top)
// approach: pop 'pos' elements into a helper stack, push value, pop helper back
void insert(Stack<int> * s, int pos, const int & value){
    int size = getSize(s);
    MyStack<int> temp(size + 10);

    int val;
    for(int i = 0; i < pos; i++){
        s->pop(val);
        temp.push(val);
    }
    s->push(value);
    while(!temp.isEmpty()){
        temp.pop(val);
        s->push(val);
    }
}

// swaps the values at positions i and j (0 = top)
// approach: peek both values, use a temp stack to do two targeted replacements
void swapPositions(Stack<int> * s, int i, int j){
    int size = getSize(s);

    if(i > j){ int tmp = i; i = j; j = tmp; }

    int valI = peek(s, i);
    int valJ = peek(s, j);

    int totalSize = size + 10;
    MyStack<int> temp(totalSize);
    int val;
    int idx = 0;

    while(!s->isEmpty()){
        s->pop(val);
        if(idx == i)      temp.push(valJ);
        else if(idx == j) temp.push(valI);
        else              temp.push(val);
        idx++;
    }
    while(!temp.isEmpty()){
        temp.pop(val);
        s->push(val);
    }
}

// sorts the stack in ascending or descending order using selection sort
// ascending: smallest at bottom, largest at top
// descending: largest at bottom, smallest at top
// approach: repeatedly find the min (asc) or max (desc) from source,
//           move it to result stack; at end push result back onto original
void sort(Stack<int> * s, bool asc){
    int size = getSize(s);
    if(size <= 1) return;

    MyStack<int> source(*(MyStack<int>*)s);
    MyStack<int> result(size + 10);

    while(!source.isEmpty()){
        // find the extreme value (min for asc, max for desc) in source
        MyStack<int> scanCopy(source);
        int extreme;
        scanCopy.pop(extreme);
        int val;
        while(!scanCopy.isEmpty()){
            scanCopy.pop(val);
            if(asc  && val < extreme) extreme = val;
            if(!asc && val > extreme) extreme = val;
        }

        // remove ONE occurrence of extreme from source, push rest into temp, rebuild
        MyStack<int> temp(size + 10);
        bool removed = false;
        while(!source.isEmpty()){
            source.pop(val);
            if(!removed && val == extreme){
                removed = true; // skip this one (don't push to temp)
            } else {
                temp.push(val);
            }
        }
        // rebuild source from temp
        while(!temp.isEmpty()){
            temp.pop(val);
            source.push(val);
        }
        // push extreme into result
        result.push(extreme);
    }

    // clear the original stack (source was a copy, s still has old data)
    int v;
    while(!s->isEmpty()){
        s->pop(v);
    }
    // result has: top = last picked extreme (largest for asc, smallest for desc)
    // to push back in correct sorted order we reverse via a helper stack
    MyStack<int> reversal(size + 10);
    while(!result.isEmpty()){
        result.pop(v);
        reversal.push(v);
    }
    // now reversal top = first extreme picked = smallest (asc) or largest (desc)
    // push into s: last pushed = top => largest (asc) or smallest (desc) at top
    while(!reversal.isEmpty()){
        reversal.pop(v);
        s->push(v);
    }
}
