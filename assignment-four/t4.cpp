// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FOUR
// Name of Student: Muhammad Ikram ul haq
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "Node.h"
#include "DoublyLinkedList.h"
#include "ConcreteDoublyLinkedList.h"

void display(ConcreteDoublyLinkedList<int> dll);
void recursiveCopy(ConcreteDoublyLinkedList<int> src, ConcreteDoublyLinkedList<int> & copy);
int max(ConcreteDoublyLinkedList<int> dll);
bool isFound(ConcreteDoublyLinkedList<int> dll, int x);
int countValue(ConcreteDoublyLinkedList<int> dll, int x);
// passed list by reference so that it persists after the function call
void insert(ConcreteDoublyLinkedList<int> &dll, int value, int position);// insert value at position
// passed list by reference so that it persists after the function call
void deleteValue(ConcreteDoublyLinkedList<int> &dll, int position);// selete value at position
void removeValue(ConcreteDoublyLinkedList<int> & adt, int v); // remove all occurrences of v
void removeDuplicates(ConcreteDoublyLinkedList<int> &dll);

int main () {
    cout << "\n================ Testing Doubly Linked List Display ================\n";
    ConcreteDoublyLinkedList<int> dll;
    dll.insertAtFirst(1);
    dll.insertAtFirst(2);
    dll.insertAtFirst(3);
    dll.insertAtFirst(3);
    dll.insertAtFirst(4);
    dll.insertAtFirst(5);
    display(dll);

    cout << "\n================ Testing Doubly Linked List Copy ================\n";
    ConcreteDoublyLinkedList<int> copy;
    recursiveCopy(dll,copy);
    display(copy);

    cout << "\n================ Testing Doubly Linked List Max ================\n";
    cout << max(dll) << endl;

    cout << "\n================ Testing Doubly Linked List Search ================\n";
    if(isFound(dll,3)) cout << "Found\n";
    else cout << "Not Found\n";

    cout << "\n================ Testing Doubly Linked List Count Value ================\n";
    cout << "this value appears: "<<countValue(dll,3) << " times." << endl;

        cout << "\n================ Testing Doubly Linked List Insert ================\n";
    insert(dll,10,3);
    display(dll);

        cout << "\n================ Testing Doubly Linked List Delete ================\n";
    deleteValue(dll,3);
    display(dll);

        ConcreteDoublyLinkedList<int> dll2;
    dll2.insertAtFirst(10);
    dll2.insertAtFirst(20);
    dll2.insertAtFirst(30);
    dll2.insertAtFirst(30);
    dll2.insertAtFirst(20);
    dll2.insertAtFirst(50);
    dll2.insertAtFirst(30);
    cout << "\n================ Testing Doubly Linked List Remove Value ================\n";
    cout << "Before removing value : ";
    display(dll2);
    cout << "\nAfter removing value : ";
    removeValue(dll2,30);
    display(dll2);

    ConcreteDoublyLinkedList<int> dll3;
    dll3.insertAtFirst(10);
    dll3.insertAtFirst(20);
    dll3.insertAtFirst(30);
    dll3.insertAtFirst(30);
    dll3.insertAtFirst(40);
    dll3.insertAtFirst(20);
    dll3.insertAtFirst(10);
    cout << "\n================ Testing Doubly Linked List Remove Duplicates ================\n";
    cout << "Before removing duplicates : ";
    display(dll3);
    cout << "\nAfter removing duplicates : ";
    removeDuplicates(dll3);
    display(dll3);

    return 0;
}

/*
 * - Purpose: Displays doubly linked list values from tail to head.
 * - Base case: If list is empty, stop recursion.
 * - Recursive case: Remove first node, recurse on the remaining list, then
 *   print saved value while unwinding.
 */
void display(ConcreteDoublyLinkedList<int> dll){
    if (dll.isEmpty()) return;
    
    int value = dll.removeFromFirst();
    display(dll);
    cout << value << " ";
}

/*
 * - Purpose: Copies all values from src list into copy while preserving order.
 * - Base case: If source list is empty, return.
 * - Recursive case: Remove first value, recurse on remaining source list, then
 *   insert saved value at front of copy while unwinding.
 */
void recursiveCopy(ConcreteDoublyLinkedList<int> src, ConcreteDoublyLinkedList<int> & copy){
    if (src.isEmpty()) return;

    int val = src.removeFromFirst();
    recursiveCopy(src,copy);
    copy.insertAtFirst(val);
}

/*
 * - Purpose: Returns the maximum value in the list recursively.
 * - Base case: If list is empty, return 0.
 * - Recursive case: Remove first value, compute max of remaining list
 *   recursively, then return the larger value.
 */
int max(ConcreteDoublyLinkedList<int> dll){
    if(dll.isEmpty()) return 0;
    int val = dll.removeFromFirst();
    int maxRest = max(dll);
    return (val > maxRest) ? val : maxRest;
}

/*
 * - Purpose: Checks whether x exists in the list.
 * - Base case: If list is empty, value is not found.
 * - Recursive case: Remove first value and compare with x; if not equal,
 *   recurse on remaining list.
 */
bool isFound(ConcreteDoublyLinkedList<int> dll, int x){
    if (dll.isEmpty()) return false;
    if(dll.removeFromFirst() == x) return true;
    return isFound(dll,x);

}

/*
 * - Purpose: Counts total occurrences of x in the list.
 * - Base case: If list is empty, count is 0.
 * - Recursive case: Remove first value, convert current match to 1/0, recurse
 *   on the rest, and accumulate counts.
 */
int countValue(ConcreteDoublyLinkedList<int> dll, int x){
    if (dll.isEmpty()) return 0;
    if(dll.removeFromFirst() == x) return 1 + countValue(dll , x);
    else return countValue(dll,x);
}

/*
 * - Purpose: Inserts value at a given position from the head side.
 * - Base case: If list is empty or position is 0, insert value at first.
 * - Recursive case: Remove first value to move deeper, recurse with
 *   position-1, then restore removed value at first while unwinding.
 */
void insert(ConcreteDoublyLinkedList<int> &dll, int value, int position){
    if (dll.isEmpty() || position == 0){
        dll.insertAtFirst(value);
        return;
    }

   int val = dll.removeFromFirst();
   insert(dll, value , position-1);
   dll.insertAtFirst(val);
}

/*
 * - Purpose: Deletes value at a given position from the tail side.
 * - Base case: If position is 0, discard removed last value.
 * - Recursive case: Remove last value, recurse with position-1, then insert
 *   saved value back at last while unwinding.
 */
void deleteValue(ConcreteDoublyLinkedList<int> &dll, int position){
    if (dll.isEmpty()) return;
    int val = dll.removeFromLast();
    if(position == 0) return;
    deleteValue(dll,position-1);
    dll.insertAtLast(val);
}

/*
 * - Purpose: Removes all occurrences of value v from the list.
 * - Base case: If list is empty, return.
 * - Recursive case: Remove last value, recurse on remaining list, then insert
 *   back only values different from v.
 */
void removeValue(ConcreteDoublyLinkedList<int> & adt, int v){
    if(adt.isEmpty()) return;

    int val = adt.removeFromLast(); 
    removeValue(adt,v);
    if(val != v) adt.insertAtLast(val);
}

/*
 * - Helper for removeDuplicates.
 * - Purpose: Checks if value v already exists in the list.
 * - Base case: If list is empty, value was not seen.
 * - Recursive case: Remove last value and compare with v; if unmatched,
 *   recurse on remaining list.
 */
bool is_seen(ConcreteDoublyLinkedList<int> dll , int v){
    if (dll.isEmpty()) return false;
    
    int val = dll.removeFromLast();
    if(val == v) return true;
    return is_seen(dll,v);
}

/*
 * - Purpose: Removes duplicate values from the list.
 * - Base case: If list is empty, return.
 * - Recursive case: Remove last value and recursively process remaining list;
 *   while unwinding, insert value only if is_seen reports it as unseen.
 * - Helper used: is_seen(dll, val) checks whether val already exists.
 */
void removeDuplicates(ConcreteDoublyLinkedList<int> &dll){
    if(dll.isEmpty()) return;

    int val = dll.removeFromLast();
    removeDuplicates(dll);
    if(!is_seen(dll,val)) dll.insertAtLast(val);
}
