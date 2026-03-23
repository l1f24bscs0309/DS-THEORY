#pragma once

template <class T>
class Stack {
    public:

        Stack(int _maxCapacity = 0);
        Stack(const Stack & AA);
        virtual void push(T v) = 0; // increments currentIndex and add value if not full
        virtual bool pop(T & value) = 0; // if not empty returns the value at the currentIndex and decrements
        virtual T top() = 0; // if not empty returns the value at the currentIndex
        bool isEmpty( );
        bool isFull( );

    protected:
        int currentIndex;
        T * values;
        int maxCapacity;
};

template <class T>
Stack<T>::Stack(int _maxCapacity) {
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    values = new T[maxCapacity]{0};
}

template <class T>
Stack<T>::Stack(const Stack & s) {
    maxCapacity = s.maxCapacity;
    currentIndex = s.currentIndex;
    values = new T[maxCapacity]{0};
    for(int i = 0; i < maxCapacity; i++)
    {
        values[i] = s.values[i];
    }
}

template <class T>
bool Stack<T>::isEmpty( ) {
    return (currentIndex < 0);
}

template <class T>
bool Stack<T>::isFull( ) {
    return (currentIndex == maxCapacity - 1);
}
