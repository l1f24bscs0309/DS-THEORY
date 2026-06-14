#include <iostream>
using namespace std;
#include "MaxHeap.h"

// all the comments are done in the MaxHeap.h file as the main function is just to test the functionality of the MaxHeap class and its member functions.

int main (){
     MaxHeap<int> h(10);

  cout << "\nInserting: 5 3 8 1 9 2 7" << endl;
  h.insert(5);
  h.insert(3);
  h.insert(8);
  h.insert(1);
  h.insert(9);
  h.insert(2);
  h.insert(7);

  cout << "Heap after inserts: ";
  h.display();

  cout << "\nCopying heap to another heap using copy constructor" << endl;
  MaxHeap<int> h2(h);
  cout << "Heap 2 after copy: ";
  h2.display();

  cout << "\nCopying heap to another heap using assignment operator" << endl;
  MaxHeap<int> h3(10);
  h3 = h;
  cout << "Heap 3 after assignment: ";
  h3.display();

  cout << "searching for 8: " << (h.search(8) ? "Found" : "Not Found") << endl;
    cout << "searching for 10: " << (h.search(10) ? "Found" : "Not Found") << endl;

    h.remove(7);
    cout << "Heap after removal: ";
    h.display();

    h.insert(10);
    h.insert(15);
    h.insert(20);
    h.insert(25);
    cout << "\nHeap after inserting 10, 15, 20, 25: ";
    h.display();

    cout << "\nChecking if heap is empty: " << (h.isEmpty() ? "Empty" : "Not Empty") << endl;
    cout << "\nChecking if heap is full: " << (h.isFull() ? "Full" : "Not Full") << endl;


    MaxHeap<int> heap(8);
    heap.insert(100);
    heap.insert(5);
    heap.insert(3);
    heap.insert(2);
    heap.insert(8);
    heap.insert(15);
    heap.insert(6);
    heap.insert(102);

    cout << "\nOriginal heap: ";
    heap.display();

    cout << "\nHeap after heap sort: ";
    heap.heapSort();
    heap.display();
}
