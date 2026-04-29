#include "Node.h"
#include <iostream>
using namespace std;

class DoublyLinkedList
{
protected:
    Node* first;
    Node* last;
public:
    DoublyLinkedList() : first(nullptr), last(nullptr) {}
    ~DoublyLinkedList();
    void insertAtLast(int);
    void insertAtFirst(int);
    int removeFromFirst();
    int removeFromLast();
    bool isEmpty() const { return first == nullptr; }
    void display() const;
};

DoublyLinkedList::~DoublyLinkedList()
{
    while (!isEmpty())
    {
        removeFromFirst();
    }
}

void DoublyLinkedList::insertAtLast(int value)
{
    Node* nn = new Node;
    nn->data = value;
    nn->next = nullptr;
    nn->prev = last;

    if (isEmpty())
    {
        first = last = nn;
    }
    else
    {
        last->next = nn;
        last = nn;
    }
}

void DoublyLinkedList::insertAtFirst(int value)
{
    Node* nn = new Node;
    nn->data = value;
    nn->prev = nullptr;
    nn->next = first;

    if (isEmpty())
    {
        first = last = nn;
    }
    else
    {
        first->prev = nn;
        first = nn;
    }
}

int DoublyLinkedList::removeFromFirst()
{
    if (isEmpty())
    {
        cout << "List is empty\n";
        return -9999;
    }

    int val = first->data;
    Node* toDelete = first;

    if (first == last)
    {
        first = last = nullptr;
    }
    else
    {
        first = first->next;
        first->prev = nullptr;
    }

    delete toDelete;
    return val;
}

int DoublyLinkedList::removeFromLast()
{
    if (isEmpty())
    {
        cout << "List is empty\n";
        return -9999;
    }

    int val = last->data;
    Node* toDelete = last;

    if (first == last)
    {
        first = last = nullptr;
    }
    else
    {
        last = last->prev;
        last->next = nullptr;
    }

    delete toDelete;
    return val;
}

void DoublyLinkedList::display() const
{
    Node* temp = first;
    while (temp != nullptr)
    {
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << endl;
}


