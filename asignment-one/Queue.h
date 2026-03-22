#pragma once
#include <iostream>
using namespace std;

class Queue{
    public:

        Queue(int cap) : startOfQIndex(-1), topOfQIndex(-1), maxCapacity(cap), count(0) {}
        Queue(const Queue & q) : startOfQIndex(q.startOfQIndex), topOfQIndex(q.topOfQIndex),
        maxCapacity(q.maxCapacity), count(q.count){}
        virtual ~Queue() {}
        bool isEmpty() const;
        bool isFull() const;
        virtual void enqueue(const int & value) = 0;
        virtual int dequeue() = 0;
        virtual void display(ostream &) const = 0;

    protected:

        int startOfQIndex; // corresponds to front
        int topOfQIndex;
        // corresponds to rear
        int maxCapacity;
        // total size of array
        int count; // keep a count of values in queue
};

// Check if queue is empty
bool Queue::isEmpty() const{
    return (count == 0);
}

// Check if queue is full
bool Queue::isFull() const{
    return (count == maxCapacity );
}
