#pragma once
#include "Queue1.h"

class MyQueue: public Queue
{
    public:
        MyQueue(int s);
        MyQueue(const MyQueue & mq);
        ~MyQueue();
        void enqueue(const int & value);
        int dequeue();
        void display(ostream &) const;
    protected:
        int * values;
};

MyQueue::MyQueue (int s) : Queue(s){
    values = new int[s];
}

MyQueue::MyQueue (const MyQueue &mq) : Queue(mq){
    values = new int[maxCapacity];
    for (int i = 0 ; i < count ; i++){
        values[i] = mq.values[i];
    }
}

MyQueue::~MyQueue(){
    delete []values;
}

void MyQueue::enqueue(const int & value){
    if(startIndex == -1)
        startIndex = 0;
    if(!isFull()){
    endIndex++;
    values[endIndex] = value; 
    count++;
    }else {
        throw "cannot add to filled queue";
    }
}



int MyQueue::dequeue(){
    if(isEmpty()){
      throw "cannot remove from empty queue";
    }
    int removed = values[startIndex];
    startIndex++;
    count--;
    if (count == 0){
        endIndex = -1;
        startIndex = -1;
    }
    return removed;
}

void MyQueue::display(ostream &out)const{
    if(isEmpty()){
        out << "EMpty nothing to prinr \n";
    }
    for (int i = startIndex ; i <= endIndex; i++){
        out << values[i] << " ";
    }
    out << endl;
}
