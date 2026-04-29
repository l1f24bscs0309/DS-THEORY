#pragma once
#include <iostream>
using namespace std;

class AbstractArray {
public:
    virtual int getSize() const = 0;
    virtual int getCapacity() const = 0;
    virtual void setValue(const int& index, const int& val) = 0;
    virtual int getValue(const int& index) const = 0;
    virtual void insert(const int& val) = 0;
    virtual void display(ostream& out) const = 0;
    virtual ~AbstractArray() {}
};
