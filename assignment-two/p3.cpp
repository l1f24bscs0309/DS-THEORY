// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT TWO
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File p3.cpp contains complete code of Queue Problem 1:
// Implements global utility functions on MyQueue<int> (CircularQueue)

#include <iostream>
using namespace std;
#include "MyQueue.h"

/*
PROBLEM DESCRIPTION:
For CircularQueue (MyQueue) implement the following functions and a suitable main to test them:
1. int getSize(MyQueue<int> * q)              - return the number of elements currently in queue
2. int peek(MyQueue<int> * q, int pos)        - return value at position pos without removing
3. void insert(MyQueue<int> * q, int pos, const int & value) - insert value at position pos
4. void swap(MyQueue<int> * q, int i, int j)  - swap values at positions i and j
5. void sort(MyQueue<int> * q, bool asc)      - sort queue ascending or descending

PROBLEM SOLUTION:

Queue Only Solution without functions
--------------------------------------
For getSize:
  - make a copy of the queue using copy constructor
  - dequeue elements one by one while counting
  - return the count
  e.g. queue: [10 -> 20 -> 30 -> 40] => count = 4

For peek(pos):
  - position 0 means front of queue (first to be dequeued)
  - make a copy of the queue
  - dequeue 'pos' elements to reach the desired position
  - the next dequeue gives the value at that position
  e.g. queue: [10 -> 20 -> 30 -> 40]
       peek(0) = 10, peek(1) = 20, peek(2) = 30

For insert(pos, value):
  - make a temporary queue
  - dequeue 'pos' elements from original and enqueue them into temp queue
  - enqueue the new value onto original queue
  - dequeue all elements from temp and enqueue them back onto original queue

  e.g. queue: [10 -> 20 -> 30]  insert at pos=1, value=99
       dequeue 1 element (10) into temp
       enqueue 99 => queue: [20 -> 30 -> 99]
       enqueue from temp (10) back => queue: [20 -> 30 -> 99 -> 10]

  Wait, that's wrong. After dequeuing 10 into temp, original = [20 -> 30].
  Enqueue 99 => [20 -> 30 -> 99].
  Enqueue back from temp: 10 => [20 -> 30 -> 99 -> 10].
  That puts 10 at the end. But we want: [10 -> 99 -> 20 -> 30].
  
  Correct approach: dequeue 'pos' elements into temp (preserving their order),
  enqueue new value into ORIGINAL, then enqueue all from temp into ORIGINAL.
  Actually we need to re-enqueue the original elements before the insertion point
  and then rebuild. 
  
  Let's think again:
  original: [10 -> 20 -> 30], insert at pos=1 means after 1 element
  => result should be [10 -> 99 -> 20 -> 30]
  
  Step 1: dequeue pos=1 elements from original, store in temp
          temp gets: 10  (first dequeued)
          original is now: [20 -> 30]
  Step 2: enqueue new value into original
          original: [20 -> 30 -> 99]
  Step 3: dequeue all remaining from original into another temp2
          temp2 gets: 20, 30, 99
          original is empty
  Step 4: enqueue from temp back into original: 10
          enqueue from temp2 back into original: 20, 30, 99
          Wait, that gives [10 -> 20 -> 30 -> 99], not [10 -> 99 -> 20 -> 30]
  
  The right way:
  Step 1: dequeue pos elements from original, enqueue into temp => temp: [10]
  Step 2: enqueue new value into original => original: [20 -> 30 -> 99]
  Hmm, the original already had its front removed...
  
  We need to rebuild from scratch:
  Step 1: dequeue ALL elements from original into an array/temp queue
  Step 2: enqueue the first 'pos' back
  Step 3: enqueue new value
  Step 4: enqueue the rest
  
  Since we can only use queue, we use two helper queues.
  e.g. queue: [10 -> 20 -> 30], insert at pos=1, value=99
       dequeue all into backup: backup=[10 -> 20 -> 30], original empty
       enqueue 1 element from backup into original: original=[10], backup=[20 -> 30]
       enqueue 99 into original: original=[10 -> 99], backup=[20 -> 30]
       enqueue rest from backup into original: original=[10 -> 99 -> 20 -> 30] CORRECT!

For swap(i, j):
  - peek values at i and j
  - extract all elements, swap them at positions i and j, requeue
  e.g. queue: [10 -> 20 -> 30 -> 40] swap(0, 2)
       => [30 -> 20 -> 10 -> 40]

For sort(asc):
  - selection sort: repeatedly find min (asc) or max (desc),
    remove it from the queue, enqueue into result queue
  - similar to stack sort but using dequeue/enqueue
  e.g. queue: [3 -> 1 -> 4 -> 1 -> 5] sort ascending
       find min=1, remove from queue, enqueue to result
       find min=1, remove, enqueue to result
       find min=3, remove, enqueue to result
       ... result: [1 -> 1 -> 3 -> 4 -> 5]


Queue Only Solution with functions
--------------------------------------
Functions to use:
1. getSize(MyQueue<int> * q)
2. peek(MyQueue<int> * q, int pos)
3. insert(MyQueue<int> * q, int pos, const int & value)
4. swap(MyQueue<int> * q, int i, int j)
5. sort(MyQueue<int> * q, bool asc)

1. Create a MyQueue<int> q of size 10
   queue is empty, count = 0

2. Enqueue some test values: 10, 30, 50, 20, 40
   queue: [10 -> 30 -> 50 -> 20 -> 40]

3. Call getSize(&q) => returns 5

4. Call peek(&q, 0) => returns 10 (front), peek(&q, 2) => 50

5. Call insert(&q, 2, 99) => inserts 99 at position 2
   queue becomes: [10 -> 30 -> 99 -> 50 -> 20 -> 40]

6. Call swap(&q, 0, 3) => swaps front and element at pos 3
   queue becomes: [50 -> 30 -> 99 -> 10 -> 20 -> 40]

7. Call sort(&q, true) => ascending order, smallest at front
*/

/********* GLOBAL FUNCTION PROTOTYPES *********/

int getSize(MyQueue<int> * q);
int peek(MyQueue<int> * q, int pos);
void insert(MyQueue<int> * q, int pos, const int & value);
void swapPositions(MyQueue<int> * q, int i, int j);
void sort(MyQueue<int> * q, bool asc);

/********* DRIVER FUNCTION MAIN *********/

int main(){
    MyQueue<int> q(15);

    q.enqueue(10);
    q.enqueue(30);
    q.enqueue(50);
    q.enqueue(20);
    q.enqueue(40);

    q.display(cout);


    cout << "peek at pos 0 (front): " << peek(&q, 0) << endl;
    cout << "peek at pos 2:         " << peek(&q, 2) << endl;
    cout << "peek at pos 4:         " << peek(&q, 4) << endl;

    insert(&q, 2, 99);
    cout << "Queue after insert: ";
    q.display(cout);

    swapPositions(&q, 0, 4);
    cout << "Queue after swap:   ";
    q.display(cout);

    sort(&q, true);
    cout << "Sorted ascending:  ";
    q.display(cout);

    sort(&q, false);
    cout << "Sorted descending: ";
    q.display(cout);

    return 0;
}

/********* GLOBAL FUNCTION CODE *********/

int getSize(MyQueue<int> * q){
    MyQueue<int> temp(*q);
    int count = 0;
    while(!temp.isEmpty()){
        temp.dequeue();
        count++;
    }
    return count;
}

int peek(MyQueue<int> * q, int pos){
    int size = getSize(q);

    MyQueue<int> temp(*q);
    int val = 0;
    for(int i = 0; i <= pos; i++){
        val = temp.dequeue();
    }
    return val;
}

void insert(MyQueue<int> * q, int pos, const int & value){
    int size = getSize(q);

    int newCapacity = size + 10;
    MyQueue<int> backup(newCapacity);

    for(int i = 0; i < pos; i++){
        backup.enqueue(q->dequeue());
    }

    MyQueue<int> rest(newCapacity);
    while(!q->isEmpty()){
        rest.enqueue(q->dequeue());
    }

    while(!backup.isEmpty()){
        q->enqueue(backup.dequeue());
    }
    q->enqueue(value);
    while(!rest.isEmpty()){
        q->enqueue(rest.dequeue());
    }
}

void swapPositions(MyQueue<int> * q, int i, int j){
    int size = getSize(q);

    int valI = peek(q, i);
    int valJ = peek(q, j);

    MyQueue<int> rebuilt(size + 10);
    int idx = 0;
    while(!q->isEmpty()){
        int val = q->dequeue();
        if(idx == i)      rebuilt.enqueue(valJ);
        else if(idx == j) rebuilt.enqueue(valI);
        else              rebuilt.enqueue(val);
        idx++;
    }

    while(!rebuilt.isEmpty()){
        q->enqueue(rebuilt.dequeue());
    }
}

void sort(MyQueue<int> * q, bool asc){
    int size = getSize(q);

    MyQueue<int> result(size + 10);

    while(!q->isEmpty()){
        MyQueue<int> scan(*q);
        int extreme = scan.dequeue();
        while(!scan.isEmpty()){
            int val = scan.dequeue();
            if(asc  && val < extreme) extreme = val;
            if(!asc && val > extreme) extreme = val;
        }

        MyQueue<int> temp(size + 10);
        bool removed = false;
        while(!q->isEmpty()){
            int val = q->dequeue();
            if(!removed && val == extreme){
                removed = true; // skip this one
            } else {
                temp.enqueue(val);
            }
        }
        while(!temp.isEmpty()){
            q->enqueue(temp.dequeue());
        }
        result.enqueue(extreme);
    }

    while(!result.isEmpty()){
        q->enqueue(result.dequeue());
    }
}
