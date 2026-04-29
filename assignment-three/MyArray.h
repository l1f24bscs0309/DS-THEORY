
#pragma once
#include <iostream>
using namespace std;
#include "AbstractArray.h"

class MyArray : public AbstractArray {
private:
    int* values;
    int capacity;
    int size;

public:
    MyArray(int cap) {
        capacity = cap;
        size = 0;
        values = new int[capacity]{0};
    }

    MyArray(const MyArray& a) {
        capacity = a.capacity;
        size = a.size;
        values = new int[capacity]{0};
        for (int i = 0; i < capacity; i++) {
            values[i] = a.values[i];
        }
    }

    MyArray& operator=(const MyArray& a) {
        if (this != &a) {
            delete[] values;
            capacity = a.capacity;
            size = a.size;
            values = new int[capacity]{0};
            for (int i = 0; i < capacity; i++) {
                values[i] = a.values[i];
            }
        }
        return *this;
    }

    ~MyArray() {
        delete[] values;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void setValue(const int& index, const int& val) {
        if (index >= 0 && index < capacity) {
            values[index] = val;
        }
    }

    int getValue(const int& index) const {
        if (index >= 0 && index < capacity) {
            return values[index];
        }
        return -1;
    }

    void insert(const int& val) {
        if (size < capacity) {
            values[size] = val;
            size++;
        } else {
            cout << "Array is full, cannot insert " << val << endl;
        }
    }

    void display(ostream& out) const {
        out << "[ ";
        for (int i = 0; i < size; i++) {
            out << values[i];
            if (i < size - 1) out << ", ";
        }
        out << " ]" << endl;
    }
};

