#pragma once
#include "LinkedList.h"
#include <iostream>
using namespace std;
// maintains a Sorted List in Ascending or Descending Order
// Insertion is always at the correct position (maintains order) from First or Last
class SortedLinkedList:public LinkedList
{
public:
  void display();
  int removeFromFirst();
  int removeFromLast();
  void insertSorted(int);
  bool deleteValue(int);
  bool search(int) ;
  bool isEmpty();
protected:
  bool ascending;
private:
  void insertAtLast(int value);
  void insertAtFirst(int value);

};

bool SortedLinkedList::isEmpty()
{
  return first==nullptr && last==nullptr;
}

int SortedLinkedList::removeFromLast()
{
  if (first==nullptr && last == nullptr) //empty linked list
    {
      cout << "LL is empty; returing NULL value" << endl;
      return -99999;
    }
  else if (first == last) //single node case
    {
      int returingValue = first->data;
      delete last;
      first = nullptr;
      last = nullptr;
      return returingValue;
    }
  else
    {
      Node*t = first;
      while(1)
        {
	  if (t->next == last)
	    {
	      break;
	    }
	  t = t->next;
        }

      int returingValue = last->data;
      delete last;
      t->next = nullptr;
      last = t;
      return returingValue;
    }
}

int SortedLinkedList::removeFromFirst()
{
  if (first==nullptr && last == nullptr) //empty linked list
    {
      cout << "LL is empty; returing NULL value" << endl;
      return -99999;
    }
  else if (first == last) //single node case
    {
      int returingValue = first->data;
      delete last;
      first = nullptr;
      last = nullptr;
      return returingValue;
    }
  else
    {
      int returingValue = first->data;
      Node*t = first;
      first = first->next;
      delete t;
      t = nullptr;
      return returingValue;
    }
}

void SortedLinkedList::display()
{
  if (first == nullptr && last == nullptr)
    {
      cout << "->\n";
      return;
    }
  Node* t = first;
  while (1)
    {
      cout << t->data;
      cout << " -> ";
      t = t->next;
      if (t == nullptr)
	{
	  //cout << "nullptr";
	  break;
	}
    }
  cout << endl;
}

void SortedLinkedList::insertAtFirst(int value)
{
  Node*nn = new Node;
  nn->data = value;
  nn->next = nullptr;
  if (first==nullptr && last == nullptr) //first node case
    {
      first = nn;
      last = nn;
    }
  else // for all Nodes other than the first
    {
      nn->next = first;
      first = nn;
    }
}

void SortedLinkedList::insertAtLast(int value)
{
  Node*nn = new Node;
  nn->data = value;
  nn->next = nullptr;
  if (first==nullptr && last == nullptr) //first node case
    {
      first = nn;
      last = nn;
    }
  else // for all Nodes other than the first
    {
      last->next = nn;
      last = nn;
    }
}

bool SortedLinkedList::deleteValue(int value)
{
  if (first==nullptr && last == nullptr) //LL is empty
    {
      return false;
    }
  else if (value == first->data)
    {
      removeFromFirst();
      return true;
    }
  else if (value == last->data)
    {
      removeFromLast();
      return true;
    }
  else
    {
      Node*t = first;
      while(true)
        {
	  if (t->next->data == value)
	    {
	      Node*t2 = t->next;
	      t->next = t->next->next;
	      delete t2;
	      t2 = nullptr;
	      return true;
	    }
	  else
	    {
	      t = t->next;
	      if (t->next == nullptr)
		{
		  return false;
		}
	    }
	}
    }
}

void SortedLinkedList::insertSorted(int value)
{
  if (first==nullptr && last == nullptr) //first node case
    {
      Node*nn = new Node;
      nn->data = value;
      nn->next = nullptr;
      first = nn;
      last = nn;
    }
  else if (value <= first->data) //smallest value
    {
      insertAtFirst(value);
    }
  else if (value >= last->data) //largest value
    {
      insertAtLast(value);
    }
  else
    {
      Node*t = first;
      Node*nn = new Node;
      nn->data = value;
      nn->next = nullptr;
      while(true)
        {
	  if (t->next->data > value)
	    {
	      nn->next=t->next;
	      t->next = nn;
	      break;
	    }
	  else
	    t = t->next;
       }
    }
}
