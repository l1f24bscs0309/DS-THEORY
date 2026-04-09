// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT TWO
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File p5.cpp contains complete code of both LinkedList problems:
// Problem 1: MySortedFirstOnlyCircularLinkedList (extends FirstOnlyLinkedList)
// Problem 2: consecutiveSubsets using a circular linked list

#include <iostream>
using namespace std;
#include "MySortedFirstOnlyCircularLinkedList.h"

/*
PROBLEM DESCRIPTION:

LinkedList Problem 1:
A SortedFirstOnlyCircularLinkedList is a First-Only Circular LinkedList that is always Sorted.
"First-Only" : only a 'first' pointer is maintained (no 'last' pointer).
"Circular"   : the last node's next pointer points back to 'first'.
"Sorted"     : every insertion maintains ascending order automatically.

We implement MySortedFirstOnlyCircularLinkedList as a concrete child of FirstOnlyLinkedList.
The base class (FirstOnlyLinkedList.h) provides the 'first' Node* pointer and requires:
  insertAtFirst, insertAtLast, removeFromFirst, removeFromLast, display.
We add: insertSorted, deleteValue, search, isEmpty.

Global functions on this ADT:
  a. int  getSize(list)    - traverse once counting nodes until we wrap back to first
  b. bool isEqual(a, b)   - check same size, then compare each node value in order
  c. void read(list)       - read ints from user until 0, call insertSorted for each
  d. list* frequency(list) - count occurrences of each value, return new sorted list

LinkedList Problem 2:
void consecutiveSubsets(Node* first, int listSize, int subsetSize)
Displays all consecutive (contiguous) subsets of the given size.
e.g. list 2->1->5->7->1->4, size=2  gives:
     2->1,  1->5,  5->7,  7->1,  1->4


PROBLEM SOLUTION:

LinkedList Problem 1 without functions
----------------------------------------
List structure: first -> A -> B -> C -> (C->next points back to first)
No 'last' pointer: to reach last node we walk until node->next == first.

insertSorted(value):
  Reusing the same logic as SortedLinkedList.h but adapted for circular+first-only.

  Case 1: list is empty
    create one node, node->next = node (self-loop), first = node

  Case 2: value <= first->data  (goes before current first)
    call insertAtFirst(value)
    insertAtFirst: find last (last->next==first), new->next=first, last->next=new, first=new

  Case 3: find last; if value >= last->data (goes at end)
    call insertAtLast(value)
    insertAtLast: last->next=new, new->next=first

  Case 4: insert in middle
    traverse from first; when cur->next->data > value, insert between cur and cur->next

  e.g. list [1->3->5->(back to 1)], insert 4:
    value=4 > first->data=1, so not Case 2.
    last->data=5 and 4 < 5, so not Case 3.
    cur=node(1): cur->next->data=3, 3 not > 4, keep going.
    cur=node(3): cur->next->data=5, 5 > 4, insert here.
    new(4)->next = node(5), node(3)->next = new(4)
    result: [1->3->4->5->(back to 1)]

deleteValue(value):
  Case 1: empty => return false
  Case 2: only one node and data==value => delete it, first=nullptr, return true
  Case 3: first->data==value => find last, toDelete=first, first=first->next,
          last->next=first, delete toDelete, return true
  Case 4: traverse; if cur->next->data==value relink and delete, return true
          stop when cur->next==first (full circle). return false if not found.

search(value):
  start at first, walk until cur==first again.
  return true if any node->data == value.

display():
  walk from first until cur->next==first, print each value.
  print circular back-reference at end.


LinkedList Problem 1 with functions
--------------------------------------
1. getSize:    traverse, count until back at first.
2. isEqual:    sizes must match, then traverse both together comparing data.
3. read:       loop: cin >> val; if val==0 break; list->insertSorted(val);
4. frequency:
   list is already sorted so identical values are adjacent.
   track (prevVal, count) as we traverse.
   when value changes: print "prevVal appears count time(s)", insert prevVal count times into result list.
   after loop ends, handle the last group.
   return the new result list (caller must delete it).


LinkedList Problem 2 without functions
-----------------------------------------
consecutiveSubsets(Node* first, int n, int size):
  number of subsets = n - (size - 1)
  let startNode = first
  repeat (n - size + 1) times:
    from startNode, walk 'size' steps printing each node
    then advance startNode = startNode->next

  e.g. n=6, size=2: 5 subsets
    start=2 => print 2->1
    start=1 => print 1->5
    start=5 => print 5->7
    start=7 => print 7->1
    start=1 => print 1->4

LinkedList Problem 2 with functions
--------------------------------------
1. int  getCircularSize(Node * first) - count nodes in circular list
2. void consecutiveSubsets(Node * first, int listSize, int subsetSize)
*/

/********* MySortedFirstOnlyCircularLinkedList CLASS *********/


/********* GLOBAL FUNCTION PROTOTYPES *********/

int  getSize(MySortedFirstOnlyCircularLinkedList * list);
bool isEqual(MySortedFirstOnlyCircularLinkedList * a, MySortedFirstOnlyCircularLinkedList * b);
void read(MySortedFirstOnlyCircularLinkedList * list);
MySortedFirstOnlyCircularLinkedList * frequency(MySortedFirstOnlyCircularLinkedList * list);

int  getCircularSize(Node * first);
void consecutiveSubsets(Node * first, int listSize, int subsetSize);

/********* DRIVER FUNCTION MAIN *********/

int main(){

    // ===== PROBLEM 1 =====


    MySortedFirstOnlyCircularLinkedList list;
    list.insertSorted(5);
    list.insertSorted(2);
    list.insertSorted(8);
    list.insertSorted(1);
    list.insertSorted(5);
    list.insertSorted(3);
    cout << "display:   ";
    list.display();

    cout << "search(5): " << (list.search(5) ? "found" : "not found") << "\n";
    cout << "search(9): " << (list.search(9) ? "found" : "not found") << "\n";

    cout << "\ndeleteValue(2) [middle]...\n";
    list.deleteValue(2);
    cout << "after: "; list.display();

    cout << "deleteValue(1) [first]...\n";
    list.deleteValue(1);
    cout << "after: "; list.display();

    cout << "deleteValue(8) [last]...\n";
    list.deleteValue(8);
    cout << "after: "; list.display();

    cout << "\n--- Copy constructor ---\n";
    MySortedFirstOnlyCircularLinkedList copyList(list);
    cout << "original: "; list.display();
    cout << "copy:     "; copyList.display();
    cout << "isEqual:  " << (isEqual(&list, &copyList) ? "true" : "false") << "\n";
    copyList.insertSorted(100);
    cout << "after inserting 100 into copy, isEqual: "
         << (isEqual(&list, &copyList) ? "true" : "false") << "\n";

    cout << "\n--- removeFromFirst / removeFromLast ---\n";
    cout << "removeFromFirst: " << list.removeFromFirst() << "\n";
    cout << "after: "; list.display();
    cout << "removeFromLast:  " << list.removeFromLast() << "\n";
    cout << "after: "; list.display();

    cout << "\n--- read() ---\n";
    MySortedFirstOnlyCircularLinkedList readList;
    read(&readList);
    cout << "read list: "; readList.display();

    cout << "\n--- frequency() ---\n";
    MySortedFirstOnlyCircularLinkedList * freqList = frequency(&readList);
    cout << "frequency list: "; freqList->display();
    delete freqList;


    cout << "\n\n====== LINKED LIST PROBLEM 2: consecutiveSubsets ======\n\n";

    // build unsorted circular list 2->1->5->7->1->4 using insertAtLast
    MySortedFirstOnlyCircularLinkedList cl;
    cl.insertAtLast(2);
    cl.insertAtLast(1);
    cl.insertAtLast(5);
    cl.insertAtLast(7);
    cl.insertAtLast(1);
    cl.insertAtLast(4);

    cout << "List: "; cl.display();
    int n = getCircularSize(cl.getFirst());

    cout << "\nConsecutive subsets of size 2:\n";
    consecutiveSubsets(cl.getFirst(), n, 2);

    cout << "\nConsecutive subsets of size 3:\n";
    consecutiveSubsets(cl.getFirst(), n, 3);

    return 0;
}

/********* GLOBAL FUNCTION CODE *********/

int getSize(MySortedFirstOnlyCircularLinkedList * list){
    if(list->isEmpty()) return 0;
    Node * cur = list->getFirst();
    int count = 0;
    do { count++; cur = cur->next; } while(cur != list->getFirst());
    return count;
}

bool isEqual(MySortedFirstOnlyCircularLinkedList * a, MySortedFirstOnlyCircularLinkedList * b){
    if(getSize(a) != getSize(b)) return false;
    if(a->isEmpty() && b->isEmpty()) return true;
    Node * ca = a->getFirst();
    Node * cb = b->getFirst();
    do {
        if(ca->data != cb->data) return false;
        ca = ca->next;
        cb = cb->next;
    } while(ca != a->getFirst());
    return true;
}

void read(MySortedFirstOnlyCircularLinkedList * list){
    cout << "Enter integers to insert (0 to stop): ";
    int val;
    while(cin >> val && val != 0)
        list->insertSorted(val);
}

// returns a new sorted list where each unique value V that appears F times
// is inserted F times into the result list
// since the input is sorted, duplicates are always adjacent — easy to count
MySortedFirstOnlyCircularLinkedList * frequency(MySortedFirstOnlyCircularLinkedList * list){
    MySortedFirstOnlyCircularLinkedList * result = new MySortedFirstOnlyCircularLinkedList();
    if(list->isEmpty()) return result;

    Node * cur = list->getFirst();
    int prevVal = cur->data;
    int count   = 1;
    cur = cur->next;

    while(cur != list->getFirst()){
        if(cur->data == prevVal){
            count++;
        } else {
            cout << prevVal << " appears " << count << " time(s)\n";
            for(int i = 0; i < count; i++) result->insertSorted(prevVal);
            prevVal = cur->data;
            count   = 1;
        }
        cur = cur->next;
    }
    // handle the last group
    cout << prevVal << " appears " << count << " time(s)\n";
    for(int i = 0; i < count; i++) result->insertSorted(prevVal);

    return result;
}

int getCircularSize(Node * first){
    if(first == nullptr) return 0;
    int count = 0;
    Node * cur = first;
    do { count++; cur = cur->next; } while(cur != first);
    return count;
}

void consecutiveSubsets(Node * first, int listSize, int subsetSize){
    if(first == nullptr){ cout << "(empty)\n"; return; }
    if(subsetSize > listSize){
        cout << "subset size " << subsetSize << " is larger than list size " << listSize << "\n";
        return;
    }
    int numSubsets = listSize - (subsetSize - 1);
    Node * startNode = first;
    for(int s = 0; s < numSubsets; s++){
        Node * cur = startNode;
        for(int i = 0; i < subsetSize; i++){
            cout << cur->data;
            if(i < subsetSize - 1) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
        startNode = startNode->next;
    }
}
