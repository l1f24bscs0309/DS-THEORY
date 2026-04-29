#include "FirstOnlyLinkedList.h"
#include <iostream>
using namespace std;

class myFirstOnlyLinkedList:public FirstOnlyLinkedList
{
public:
  myFirstOnlyLinkedList(): FirstOnlyLinkedList(){}
  ~myFirstOnlyLinkedList(){}
  void insertAtFirst(int);
  void insertAtLast(int);
  void display();
  int removeFromFirst();
  int removeFromLast();
};

int myFirstOnlyLinkedList::removeFromLast()
{
  if (first == nullptr)
    {
      cout << "Empty List\n";
      return -9999;
    }
  if (first->next == nullptr) //single node case
    {
      int RV = first->data;
      delete first;
      first = nullptr;
      return RV;
    }
  Node*t = first;
  while(1)
    {     
      if (t->next->next == nullptr)
	{
	  int RV = t->next->data; 
	  delete t->next;
	  t->next = nullptr;
	  return RV; 
	}
      t = t->next;
    }
}

int myFirstOnlyLinkedList::removeFromFirst()
{
  if (first == nullptr)
    {
      cout << "List is Empty\n";
      return -9999;
    }
  if (first->next == nullptr) //single node case
    {
      int RV = first->data;
      delete first;
      first = nullptr;
      return RV;
    }
  int RV = first->data;
  Node*t = first;
  first = first->next;
  delete t;
  t = nullptr;
  return RV;
}

void myFirstOnlyLinkedList::display()
{
  if (first==nullptr)
    cout << "LL is empty" << endl;
  else
    {
      Node*temp = first;
      while(1)
        {
	  cout << temp->data << " - > ";
	  if (temp->next == nullptr)
	    break;
	  temp = temp->next;
        }
      cout << endl;
    }
}

void myFirstOnlyLinkedList::insertAtFirst(int value)
{
  Node*nn = new Node;
  nn->next = nullptr;
  nn->data = value;

  if (first == nullptr)
    {
      first = nn;
    }
  else
    {
      nn->next = first;
      first = nn;
    }
}

void myFirstOnlyLinkedList::insertAtLast(int value)
{
  Node*nn = new Node;
  nn->next = nullptr;
  nn->data = value;

  if (first == nullptr)
    {
      first = nn;
    }
  else
    {
      Node*t = first;
      while(1)
        {
	  if (t->next == nullptr)
	    {
	      t->next=nn;
	      break;
	    }
	  t = t->next;
        }
    }
}
