#pragma once
class Stack {
    public:

        Stack(int _maxCapacity = 0);
        Stack(const Stack & AA);
        virtual void push(int v) = 0; // increments currentIndex and add value if not full
        virtual bool pop(int & value) = 0; // if not empty returns the value at the currentIndex and decrements
        virtual int top() = 0; // if not empty returns the value at the currentIndex
        bool isEmpty( );
        bool isFull( );

    protected:
        int currentIndex;
        int * values;
        int maxCapacity;
};

Stack::Stack(int _maxCapacity) {
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    values = new int[maxCapacity]{0};
}

Stack::Stack(const Stack & s) {
    maxCapacity = s.maxCapacity;
    currentIndex = s.currentIndex;
    values = new int[maxCapacity]{0};
    for(int i = 0; i < maxCapacity; i++)
    {
        values[i] = s.values[i];
    }
}

bool Stack::isEmpty( ) {
    return (currentIndex < 0);
}

bool Stack::isFull( ) {
    return (currentIndex == maxCapacity - 1);
}
