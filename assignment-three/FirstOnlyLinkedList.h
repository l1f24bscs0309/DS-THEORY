#pragma once
#include "Node.h"
class FirstOnlyLinkedList
{
protected:
    Node*first;
public:
  FirstOnlyLinkedList(){first = nullptr; };
  virtual ~FirstOnlyLinkedList();
    virtual void insertAtLast(int) = 0;
    virtual void insertAtFirst(int) = 0;
    virtual int removeFromFirst() = 0;
    virtual int removeFromLast() = 0;
    virtual void display() = 0;
};

FirstOnlyLinkedList:: ~FirstOnlyLinkedList()
{
  if(first != nullptr)
    {
      delete first;
      first = nullptr;
    }
}
