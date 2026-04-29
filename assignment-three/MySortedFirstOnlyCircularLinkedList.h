#pragma once
#include "FirstOnlyLinkedList.h"
#include <iostream>
using namespace std;

class MySortedFirstOnlyCircularLinkedList : public FirstOnlyLinkedList {

public:

    MySortedFirstOnlyCircularLinkedList() : FirstOnlyLinkedList() {}

    MySortedFirstOnlyCircularLinkedList(const MySortedFirstOnlyCircularLinkedList & other)
        : FirstOnlyLinkedList() {
        if(other.first == nullptr) return;
        Node * cur = other.first;
        do {
            insertAtLast(cur->data);
            cur = cur->next;
        } while(cur != other.first);
    }

    ~MySortedFirstOnlyCircularLinkedList(){
        clearList();
        // first is now nullptr so the base class destructor's 'delete first' is a no-op
    }

    MySortedFirstOnlyCircularLinkedList & operator=(const MySortedFirstOnlyCircularLinkedList & other){
        if(this != &other){
            clearList();
            if(other.first == nullptr) return *this;
            Node * cur = other.first;
            do {
                insertAtLast(cur->data);
                cur = cur->next;
            } while(cur != other.first);
        }
        return *this;
    }

    // pure virtuals required by FirstOnlyLinkedList
    void insertAtFirst(int value);
    void insertAtLast(int value);
    int  removeFromFirst();
    int  removeFromLast();
    void display();

    // sorted circular list specific methods
    void insertSorted(int value);
    bool deleteValue(int value);
    bool search(int value) const;
    bool isEmpty() const { return first == nullptr; }

    Node * getFirst() const { return first; }

private:

    // safely deletes all nodes and sets first = nullptr
    // must break the circular link first, otherwise we would follow it forever
    void clearList(){
        if(first == nullptr) return;
        if(first->next == first){
            delete first;
            first = nullptr;
            return;
        }
        // find last, break the circle, then delete linearly
        Node * last = first;
        while(last->next != first) last = last->next;
        last->next = nullptr;
        Node * cur = first;
        while(cur != nullptr){
            Node * nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        first = nullptr;
    }
};

void MySortedFirstOnlyCircularLinkedList::insertAtFirst(int value){
    Node * nn = new Node;
    nn->data = value;
    if(first == nullptr){
        nn->next = nn;
        first = nn;
        return;
    }
    Node * last = first;
    while(last->next != first) last = last->next;
    nn->next = first;
    last->next = nn;
    first = nn;
}

void MySortedFirstOnlyCircularLinkedList::insertAtLast(int value){
    Node * nn = new Node;
    nn->data = value;
    if(first == nullptr){
        nn->next = nn;
        first = nn;
        return;
    }
    Node * last = first;
    while(last->next != first) last = last->next;
    last->next = nn;
    nn->next = first;
}

int MySortedFirstOnlyCircularLinkedList::removeFromFirst(){
    if(first == nullptr){ cout << "List is empty\n"; return -9999; }
    int val = first->data;
    if(first->next == first){
        delete first;
        first = nullptr;
        return val;
    }
    Node * last = first;
    while(last->next != first) last = last->next;
    Node * toDelete = first;
    first = first->next;
    last->next = first;
    delete toDelete;
    return val;
}

int MySortedFirstOnlyCircularLinkedList::removeFromLast(){
    if(first == nullptr){ cout << "List is empty\n"; return -9999; }
    if(first->next == first){
        int val = first->data;
        delete first;
        first = nullptr;
        return val;
    }
    Node * prev = first;
    while(prev->next->next != first) prev = prev->next;
    int val = prev->next->data;
    delete prev->next;
    prev->next = first;
    return val;
}

void MySortedFirstOnlyCircularLinkedList::display(){
    if(first == nullptr){ cout << "(empty list)\n"; return; }
    Node * cur = first;
    do {
        cout << cur->data;
        if(cur->next != first) cout << " -> ";
        cur = cur->next;
    } while(cur != first);
    cout << " -> (back to " << first->data << ")\n";
}

void MySortedFirstOnlyCircularLinkedList::insertSorted(int value){
    if(first == nullptr){
        // Case 1: empty list
        Node * nn = new Node;
        nn->data = value;
        nn->next = nn;
        first = nn;
        return;
    }
    Node * last = first;
    while(last->next != first) last = last->next;

    if(value <= first->data){
        // Case 2: goes before first (smallest value)
        insertAtFirst(value);
        return;
    }
    if(value >= last->data){
        // Case 3: goes after last (largest value)
        insertAtLast(value);
        return;
    }
    // Case 4: goes in the middle
    Node * cur = first;
    while(cur->next != first){
        if(cur->next->data > value){
            Node * nn = new Node;
            nn->data = value;
            nn->next = cur->next;
            cur->next = nn;
            return;
        }
        cur = cur->next;
    }
}

bool MySortedFirstOnlyCircularLinkedList::deleteValue(int value){
    if(first == nullptr) return false;

    if(first->next == first){
        if(first->data == value){
            delete first;
            first = nullptr;
            return true;
        }
        return false;
    }
    if(first->data == value){
        removeFromFirst();
        return true;
    }
    Node * cur = first;
    while(cur->next != first){
        if(cur->next->data == value){
            Node * toDelete = cur->next;
            cur->next = toDelete->next;
            delete toDelete;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool MySortedFirstOnlyCircularLinkedList::search(int value) const{
    if(first == nullptr) return false;
    Node * cur = first;
    do {
        if(cur->data == value) return true;
        cur = cur->next;
    } while(cur != first);
    return false;
}
