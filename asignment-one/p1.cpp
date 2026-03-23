// SPRING 2026 DATA STRUCTURES SECTION D11 ASSIGNMENT ONE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
using namespace std;

/*
PROBLEM DESCRIPTION:
First N is read from the user and then N integers. Calculate and display Average, Maximum and Minimum
Values on screen. First do the problem using Stack only and then using Queue Only in the same main.

SOLUTION:

Stack only solution without functions
-------------------------------------
1. create a stack of size N
2. read N values and push them in the stack until the stack is full

12
--
43
--
34
--
2
--

stack current index = 3 and count = 4

3. use the copy construtor to create a copy of stack and preserve the original stack
4. create variables max , min , sum and counter and initialize them with the first value of the stack
5. pop values from the copy stack until it is empty
6. compare the popped value with max and min and update them accordingly
7. add the popped value to sum and increment counter
8. display the max , min and average (sum / counter) on the screen

Stack only solution with functions
-------------------------------------
Functions to use:
1. readValues
2. stats

1. create a stack of size N
2. call readValues function to read N values and push them in the stack until the stack

12
--
43
--
34
--
2
--
stack current index = 3 and count = 4

3. call stats function and copy of stack is created inside the function

##################################################################

Queue only solution without functions
-------------------------------------

1. create a queue of size N
2. read N values and enqueue them in the queue until the queue is full
Q: 12->43->34->2
startOfQIndex = 0 , topOfQIndex = 3
3. use the copy construtor to create a copy of queue and preserve the original queue
4. create variables max , min , sum and counter and initialize them with the first value of the queue
5. dequeue values from the copy queue until it is empty
6. compare the dequeued value with max and min and update them accordingly
7. add the dequeued value to sum and increment counter
8. display the max , min and average (sum / counter) on the screen

Queue only solution with functions
-------------------------------------
Functions to use:
1. readQueue
2. statsQ

1. create a queue of size N
2. call readQueue function to read N values and enqueue them in the queue until the queue is full
Q: 12->43->34->2
startOfQIndex = 0 , topOfQIndex = 3
3. call statsQ function and copy of queue is created inside the function

*/

// ------------- CHANGE IN THE COPY CONSTRUCTOR OF STACK CLASS -------------
// I changed the current index from -1 to s.currentindex because if we dont it will check the isEmpty function and it will always shows the stack empty.
// Stack::Stack(const Stack & s) {
//     maxCapacity = s.maxCapacity;
//     currentIndex = s.currentIndex;
//     values = new int[maxCapacity]{0};
//     for(int i = 0; i < maxCapacity; i++)
//     {
//         values[i] = s.values[i];
//     }
// }

/********* GLOBAL FUNCTION PROTOTYPES *********/

const int MAX_SIZE = 10;
void readValues(Stack<int>* st , istream& in);
void stats(MyStack<int> *s);
void readQueue(Queue<int> *q , istream& in);
void statsQ(MyQueue<int> *q);

/********* MAIN FUNCTION *********/

int main () {  
    MyStack<int> s(MAX_SIZE);
    readValues(&s , cin); 
    stats(&s);

    MyQueue<int> q(10);
    readQueue(&q , cin);
    statsQ(&q);

    q.display(cout);
     return 0;
}

/********* FUNCTION DEFINITIONS *********/

void readValues(Stack<int>* st , istream& in){
    cout << "Enter the size of stack: " ;
    int N;
    in >> N;

    cout << "Enter " << N << " values to push in the stack :";
    int val;
    while(N > 0){
        in >> val; 
        st->push(val);
        N--;
    }
}

void stats(MyStack<int> *s){
    
    MyStack temp(*s);
    int max , min , sum = 0 , counter = 1;
    temp.pop(max);
    min = max;
    sum = max;
    float avg;

    int val;
    while(!temp.isEmpty()){
       temp.pop(val); 
       if(val > max){
           max = val;
       }
       if(val < min){
           min = val;
       }
       sum += val;
       counter++;
    }
    avg = float(sum) / counter;
    cout << "\nMax number in stack is : " << max;
    cout << "\nMin number in stack is : " << min;
    cout << "\naverage of stack is : " << avg;

}

void readQueue(Queue<int> *q , istream& in){
    cout << "\nEnter the number of elemnts: ";
    int N;
    in >> N;

    int val;
    cout << "Enter " << N << " values to move in the queue:";
    while(N > 0){
        in >> val;
        q->enqueue(val);
        N--;
    }
}

void statsQ(MyQueue<int> *q){
    MyQueue temp(*q);
    int max , min , sum = 0 , counter = 1;
    max = temp.dequeue();
    min = max;
    sum = max;
    float avg;

    int val;
    while(!temp.isEmpty()){
        val = temp.dequeue();
       if(val > max){
           max = val;
       }
       if(val < min){
           min = val;
       }
       sum += val;
       counter++;
    }
    avg = float(sum) / counter;
    cout << "\nMax number in queue is : " << max;
    cout << "\nMin number in queue is : " << min;
    cout << "\naverage of queue is : " << avg;
    cout << endl;
}
