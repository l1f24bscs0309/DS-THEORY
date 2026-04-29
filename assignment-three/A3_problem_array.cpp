// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT THREE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File A3_PROBLEM_1.cpp contains complete code of ADT Array (Tasks 1 and 2),
// that will compile and run

/*
PROBLEM DESCRIPTION:
Task 1: Complete the code of ADT Array and write a function main to test the class.
Task 2: Use the ADT Class to write and test the following GLOBAL functions:
    a) copy    - returns a copy of the array
    b) compare - compares two arrays for equality
    c) deleteValues - deletes number of values from a given index by shifting left
    d) insert  - inserts one array into another at a given index by shifting right (cut-off beyond size)
    e) frequency - calculates and returns frequency of each value in the array

SOLUTION PLAN:
1. AbstractArray: abstract base class with pure virtual functions
2. MyArray: concrete class inheriting AbstractArray, uses dynamic int array
3. Global functions: copy, compare, deleteValues, insert, frequency
4. main: tests the class and all global functions
*/

#include <iostream>
using namespace std;
#include "AbstractArray.h"
#include "MyArray.h"
/********* GLOBAL FUNCTION PROTOTYPES *********/

void copy(AbstractArray& source, AbstractArray& destination);
bool compare(AbstractArray& A, AbstractArray& B);
void deleteValues(AbstractArray& values, const int& noOfValues, const int& index);
void insert(AbstractArray& source, AbstractArray& destination, const int& index);
MyArray frequency(AbstractArray& source);


/********* GLOBAL FUNCTION CODE *********/

void copy(AbstractArray& source, AbstractArray& destination) {
    // copy all values from source into destination one by one
    // destination must have enough capacity
    for (int i = 0; i < source.getSize(); i++) {
        destination.setValue(i, source.getValue(i));
    }
}

bool compare(AbstractArray& A, AbstractArray& B) {
    // two arrays are equal if they have the same size and same values at every index
    if (A.getSize() != B.getSize()) return false;
    for (int i = 0; i < A.getSize(); i++) {
        if (A.getValue(i) != B.getValue(i)) return false;
    }
    return true;
}

void deleteValues(AbstractArray& arr, const int& noOfValues, const int& index) {
    // delete noOfValues elements starting from index by shifting elements left
    // elements after the deleted range shift left to fill the gap
    int size = arr.getSize();
    if (index < 0 || index >= size) return;

    int valstodel = noOfValues;
    if (index + noOfValues > size) valstodel = size - index;

    for (int i = index; i < size - valstodel ; i++) {
        arr.setValue(i, arr.getValue(i + valstodel));
    }
    // zero out the leftover tail
    for (int i = size - valstodel; i < size; i++) {
        arr.setValue(i, 0);
    }
}

void insert(AbstractArray& source, AbstractArray& destination, const int& index) {
    // insert all values of source into destination starting at index
    // destination array shifts right to make room, values beyond capacity are cut off
    int destSize = destination.getSize();
    int srcSize = source.getSize();
    int destCap = destination.getCapacity();

    // shift destination values right by srcSize positions starting from index
    for (int i = destCap - 1; i >= index + srcSize; i--) {
        // only shift if the source position is within destination size
        int fromPos = i - srcSize;
        if (fromPos < destSize) {
            destination.setValue(i, destination.getValue(fromPos));
        }
    }

    // insert source values into destination starting at index
    for (int i = 0; i < srcSize; i++) {
        if (index + i < destCap) {
            destination.setValue(index + i, source.getValue(i));
        }
    }
}

MyArray frequency(AbstractArray& source) {
    // calculate frequency of each unique value in the array
    // returns a new array where index i holds the count of value i
    // finds the maximum value first to determine result array size

    int size = source.getSize();
    if (size == 0) return MyArray(1);

    // find the max value to size the frequency array
    int maxVal = source.getValue(0);
    for (int i = 1; i < size; i++) {
        if (source.getValue(i) > maxVal) maxVal = source.getValue(i);
    }

    MyArray freqArr(maxVal + 1);

    // initialize all frequency counts to 0
    for (int i = 0; i <= maxVal; i++) {
        freqArr.setValue(i, 0);
    }

    // count occurrences of each value
    for (int i = 0; i < size; i++) {
        int val = source.getValue(i);
        freqArr.setValue(val, freqArr.getValue(val) + 1);
    }

    return freqArr;
}

/********* MAIN *********/

int main() {

    MyArray arr1(5);
    arr1.insert(10);
    arr1.insert(20);
    arr1.insert(30);
    arr1.insert(40);
    arr1.insert(50);

    cout << "arr1: ";
    arr1.display(cout);
    MyArray arr2(arr1);
    cout << "arr2 (copy of arr1): ";
    arr2.display(cout);

    arr1.setValue(2, 99);
    cout << "arr1 after setValue(2, 99): ";
    arr1.display(cout);
    cout << "arr1.getValue(2) = " << arr1.getValue(2) << endl;


    cout << "\ncopy --" << endl;
    MyArray src(5);
    src.insert(1); src.insert(2); src.insert(3); src.insert(4); src.insert(5);
    MyArray dest(5);
    dest.insert(0); dest.insert(0); dest.insert(0); dest.insert(0); dest.insert(0);
    cout << "source: "; src.display(cout);
    cout << "destination before copy: "; dest.display(cout);
    copy(src, dest);
    cout << "destination after copy: "; dest.display(cout);

    cout << "\ncompare --" << endl;
    MyArray a(3); a.insert(1); a.insert(2); a.insert(3);
    MyArray b(3); b.insert(1); b.insert(2); b.insert(3);
    MyArray c(3); c.insert(1); c.insert(9); c.insert(3);
    cout << "a: "; a.display(cout);
    cout << "b: "; b.display(cout);
    cout << "c: "; c.display(cout);
    cout << "compare(a, b) = " << (compare(a, b) ? "true" : "false") << endl;
    cout << "compare(a, c) = " << (compare(a, c) ? "true" : "false") << endl;

    cout << "\ndeleteValues --" << endl;
    MyArray d(6);
    d.insert(10); d.insert(20); d.insert(30); d.insert(40); d.insert(50); d.insert(60);
    cout << "d before delete: "; d.display(cout);
    deleteValues(d, 2, 1);
    cout << "d after deleteValues(2 values from index 1): "; d.display(cout);

    cout << "\ninsert --" << endl;
    MyArray srcIns(2);
    srcIns.insert(77); srcIns.insert(88);
    MyArray destIns(6);
    destIns.insert(1); destIns.insert(2); destIns.insert(3); destIns.insert(4);
    cout << "source to insert: "; srcIns.display(cout);
    cout << "destination before insert: "; destIns.display(cout);
    insert(srcIns, destIns, 1);
    cout << "destination after insert at index 1: "; destIns.display(cout);

    cout << "\nfrequency --" << endl;
    MyArray data(8);
    data.insert(3); data.insert(1); data.insert(2); data.insert(3);
    data.insert(1); data.insert(3); data.insert(2); data.insert(1);
    cout << "data array: "; data.display(cout);
    MyArray freqResult = frequency(data);
    cout << "frequency result (index = value, content = count):" << endl;
    for (int i = 0; i < freqResult.getCapacity(); i++) {
        if (freqResult.getValue(i) > 0) {
            cout << "  value " << i << " appears " << freqResult.getValue(i) << " time(s)" << endl;
        }
    }

    return 0;
}
