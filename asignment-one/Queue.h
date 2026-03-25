#pragma once
#include <iostream>
using namespace std;

template <class T>
class Queue{
    public:

        Queue(int cap) : startOfQIndex(-1), topOfQIndex(-1), maxCapacity(cap), count(0) {}
        Queue(const Queue & q) : startOfQIndex(q.startOfQIndex), topOfQIndex(q.topOfQIndex),
        maxCapacity(q.maxCapacity), count(q.count){}
        virtual ~Queue() {}
        bool isEmpty() const;
        bool isFull() const;
        virtual void enqueue(const T & value) = 0;
        virtual T dequeue() = 0;

    protected:

        int startOfQIndex; // corresponds to front
        int topOfQIndex;
        // corresponds to rear
        int maxCapacity;
        // total size of array
        int count; // keep a count of values in queue
};

// Check if queue is empty
template <class T>
bool Queue<T>::isEmpty() const{
    return (count == 0);
}

// Check if queue is full
template <class T>
bool Queue<T>::isFull() const{
    return (count == maxCapacity );
}
