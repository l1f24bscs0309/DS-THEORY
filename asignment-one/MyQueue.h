#pragma once
#include "Queue.h"

class MyQueue: public Queue{
    public:

        MyQueue(int s): Queue(s){
            if(s != 0){
                values = new int[maxCapacity]{0};
            }
        }

        MyQueue(const MyQueue & mq): Queue(mq){
            if(maxCapacity != 0){
                values = new int[maxCapacity]{0};
                for(int i = 0; i < count; i++){
                    values[i] = mq.values[i];
                }
            }
        }

        ~MyQueue(){
            if(values != nullptr){
                delete [] values;
                values = nullptr;
            }
        }
        void enqueue(const int & value);
        int dequeue();
        void display(ostream &) const;

    protected:
        int * values;
};

// Add (insert element at topOfQIndex)
void MyQueue::enqueue(const int & value)
{
    if (isFull()) {
        cout << "MyQueue is FULL! Cannot add " << value << endl;
        return;
    }
    if (isEmpty()) { // First element insertion
        topOfQIndex = 0;
    }
    startOfQIndex++;
    values[startOfQIndex] = value;
    count++;
}

// Remove (remove element from startOfQIndex)
int MyQueue::dequeue() {
    if (isEmpty()) {
        cout << "MyQueue is EMPTY! Cannot remove." << endl;
        return -1;
    }
    int removedValue = values[topOfQIndex];
    count--;
    topOfQIndex++;
    // If queue becomes empty after remove, reset it
    if (isEmpty()) {
        startOfQIndex = topOfQIndex = -1;
    }
    return removedValue;
}

// Display the queue
void MyQueue::display(ostream & W) const{
    W <<"Queue::startOfQIndex: " << startOfQIndex
        <<", topOfQIndex: " << topOfQIndex
        <<", maxCapacity: " << maxCapacity
        <<", count: " << count << endl;
    if (isEmpty()) {
        cout << "___\n";
        cout << "___\n";
        return;
    }

    int n = topOfQIndex;
    W <<"----------------------------\n";
    for(int i = startOfQIndex ; i >= n ; i--){
      W << values[i];
        if(i > 0 && i != n){
        W << " -> ";
        }
    }
    cout << endl;
    W <<"----------------------------\n";
    // <A --> B --> C>
}
