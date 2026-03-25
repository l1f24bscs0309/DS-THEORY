#pragma once
#include "Queue.h"

template <class T>
class MyQueue: public Queue<T>{
    public:

        MyQueue(int s): Queue<T>(s){
            if(s != 0){
                values = new T[this->maxCapacity]{};
            }
        }

        MyQueue(const MyQueue & mq): Queue<T>(mq){
            if(this->maxCapacity != 0){
                values = new T[this->maxCapacity]{};
                for(int i = 0; i < this->maxCapacity; i++){
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
        void enqueue(const T & value);
        T dequeue();
        void display(ostream &) const;

    protected:
       T * values;
};

// Add (insert element at topOfQIndex)
template <class T>
void MyQueue<T>::enqueue(const T & value)
{
    if (this->isFull()) {
        cout << "MyQueue is FULL! Cannot add " << value << endl;
        return;
    }
    if (this->isEmpty()) { // First element insertion
        this->topOfQIndex = 0;
    }
    this->startOfQIndex = (this->startOfQIndex + 1) % this->maxCapacity;
    values[this->startOfQIndex] = value;
    this->count++;
}

// Remove (remove element from startOfQIndex)
template <class T>
T MyQueue<T>::dequeue() {
    if (this->isEmpty()) {
        cout << "MyQueue is EMPTY! Cannot remove." << endl;
        return T{};
    }
    T removedValue = values[this->topOfQIndex];
    this->count--;
    this->topOfQIndex = (this->topOfQIndex + 1) % this->maxCapacity;
    // If queue becomes empty after remove, reset it
    if (this->isEmpty()) {
        this->startOfQIndex = this->topOfQIndex = -1;
    }
    return removedValue;
}

// Display the queue
template <class T>
void MyQueue<T>::display(ostream & W) const{
    W <<"Queue::startOfQIndex: " << this->startOfQIndex
        <<", topOfQIndex: " << this->topOfQIndex
        <<", maxCapacity: " << this->maxCapacity
        <<", count: " << this->count << endl;
    if (this->isEmpty()) {
        cout << "___\n";
        cout << "___\n";
        return;
    }

    int n = this->topOfQIndex;
    W <<"----------------------------\n";
    for(int i = this->startOfQIndex ; i >= n ; i--){
      W << values[i];
        if(i > 0 && i != n){
        W << " -> ";
        }
    }
    cout << endl;
    W <<"----------------------------\n";
    // <A --> B --> C>
}
