#pragma once
#include "Stack.h"
#include <iostream>
using namespace std;

template <class T>
class MyStack: public Stack<T> {
    public:
        MyStack(int _currentIndex = 0): Stack<T>(_currentIndex){};
        MyStack(const MyStack & ma): Stack<T>(ma){};
        void push(T v);
        bool pop(T & v);
        T top();
};

template <class T>
void MyStack<T>::push(T v){
    if(!this->isFull()){
        this->values[++this->currentIndex] = v;
        return;
    }
    cout << "Array is full\n";
}

template <class T>
bool MyStack<T>::pop(T & v){
    if(!this->isEmpty()){
        v = this->values[this->currentIndex--];
        return true;
    }
    return false;
}

template <class T>
T MyStack<T>::top(){
    if(!this->isEmpty()){
        return this->values[this->currentIndex];
    }
    return -1;
}
