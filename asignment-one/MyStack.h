#pragma once
#include "Stack.h"
#include <iostream>
using namespace std;

class MyStack: public Stack {
    public:
        MyStack(int _currentIndex = 0): Stack(_currentIndex){};
        MyStack(const MyStack & ma): Stack(ma){};
        void push(int v);
        bool pop(int & v);
        int top();
};

void MyStack::push(int v){
    if(!isFull()){
        values[++currentIndex] = v;
        return;
    }
    cout << "Array is full\n";
}

bool MyStack::pop(int & v){
    if(!isEmpty()){
        v = values[currentIndex--];
        return true;
    }
    return false;
}

int MyStack::top(){
    if(!isEmpty()){
        return values[currentIndex];
    }
    return -1;
}
