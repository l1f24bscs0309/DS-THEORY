// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FOUR
// Name of Student: Muhammad Ikram ul haq
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "Queue.h"
#include "ArrayQueue.h"

void display(ArrayQueue<int> aq);
void recursiveCopy(ArrayQueue<int> src, ArrayQueue<int> & copy);
int max(ArrayQueue<int> aq);
bool isFound(ArrayQueue<int> q, int x);
int countValue(ArrayQueue<int> q, int x);
// passed Queue by reference so that it persists after the function call
void insert(ArrayQueue<int> &q, int value, int position);// insert value at position
// passed Queue by reference so that it persists after the function call
void deleteValue(ArrayQueue<int> &q, int position);// selete value at position
void removeValue(ArrayQueue<int> & adt, int v); // remove all occurrences of v
void removeDuplicates(ArrayQueue<int> &q);

int getSize(ArrayQueue<int> q);
void rotate(ArrayQueue<int> &q, int n);

int main () {

    cout << "=============== Queue Display ===============\n";
    ArrayQueue<int> aq(100);
    aq.enqueue(1);
    aq.enqueue(2);
    aq.enqueue(3);
    aq.enqueue(3);
    aq.enqueue(4);
    aq.enqueue(5);
    display(aq);


    cout << "\n================ Queue Copy =================\n";
    ArrayQueue<int> copy(10);
    recursiveCopy(aq,copy);
    display(copy);

    cout << "\n================== Queue Max ==============\n";
    cout << max(aq);

    cout << "\n================== Queue Value FInd ====================\n";
    if (isFound(aq,5)) cout << "Value found";
    else cout << "Value doesnot exists\n";

    cout << "\n================== Value count ====================\n";
    int count = countValue(aq,3);
    cout << "Value exists " <<  count << " times";

    cout << "\n===================== Insert into Queue ==================\n";
    insert(aq,10,3);
    cout << "After inserting into queue : ";
    rotate(aq, getSize(aq)-1);
    display(aq);

    cout << "\n=================== Deleting Value ===============\n";
    deleteValue(aq,3);
    rotate(aq, getSize(aq)-1);
    display(aq);

    cout << "\n=================== Removing Value ===============\n";
    ArrayQueue<int> q(10);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(30);
    cout << "Before removing value : ";
    display(q);
    cout << "\nAfter removing value : ";
    removeValue(q,30);
    rotate(q, getSize(q)-1);
    display(q);

    cout << "\n=================== Removing Duplicates ===============\n";
    ArrayQueue<int> q2(10);
    q2.enqueue(10);
    q2.enqueue(20);
    q2.enqueue(30);
    q2.enqueue(30);
    q2.enqueue(20);
    q2.enqueue(50);
    q2.enqueue(30);
    cout << "Before removing duplicates : ";
    display(q2);
    cout << "\nAfter removing duplicates : ";
    removeDuplicates(q2);
    rotate(q2, getSize(q2)-1);
    display(q2);

    return 0;
}

/*
 * - Purpose: Displays queue values in front-to-rear order using recursion.
 * - Base case: If queue is empty, stop recursion.
 * - Recursive case: Dequeue front value, print it, then recurse on the
 *   remaining queue until all elements are displayed.
 */
void display(ArrayQueue<int> aq){
    if(aq.isEmpty()) return;
    int val = aq.dequeue();
    cout << val << " ";
    display(aq);
}

/*
 * - Purpose: Copies all elements from src queue into copy recursively.
 * - Base case: If source queue is empty, return.
 * - Recursive case: Dequeue one value from src, enqueue it into copy, then
 *   recurse on the remaining source queue.
 */
void recursiveCopy(ArrayQueue<int> src, ArrayQueue<int> & copy){
    if(src.isEmpty()) return;
    copy.enqueue(src.dequeue());
    recursiveCopy(src,copy);

}

/*
 * - Purpose: Returns the maximum value in the queue recursively.
 * - Base case: If queue is empty, return 0.
 * - Recursive case: Dequeue one value, compute max of the remaining queue
 *   recursively, then return the larger value.
 */
int max(ArrayQueue<int> aq){
    if (aq.isEmpty()) return 0;
    int val = aq.dequeue();
    int maxOfRest = max(aq);
    return val > maxOfRest ? val : maxOfRest;
}

/*
 * - Purpose: Checks whether value x exists in the queue.
 * - Base case: If queue is empty, value is not found.
 * - Recursive case: Dequeue front and compare with x; if not equal, recurse
 *   on the reduced queue until found or empty.
 */
bool isFound(ArrayQueue<int> q, int x){
    if(q.isEmpty()) return false;
    int val = q.dequeue();
    if(x == val) return true;
    return isFound(q,x);
}

/*
 * - Purpose: Counts total occurrences of value x in the queue.
 * - Base case: If queue is empty, count is 0.
 * - Recursive case: Dequeue one value, convert current match to 1/0, recurse
 *   on remaining queue, and add counts.
 */
int countValue(ArrayQueue<int> q, int x){
    if (q.isEmpty()) return 0;

    if (x == q.dequeue()) return 1 + countValue(q,x);
    else return countValue(q,x); 
}

/*
 * - Purpose: Computes queue size recursively.
 * - Base case: If queue is empty, size is 0.
 * - Recursive case: Dequeue one value, recurse on remaining queue, and add 1
 *   to build the total size.
 */
int getSize(ArrayQueue<int> q){
    if (q.isEmpty()) return 0;
    q.dequeue();
    return 1 + getSize(q);
}

/*
 * - Purpose: Rotates first n elements by moving them to the rear recursively.
 * - Base case: If n is 0 or queue is empty, rotation is complete.
 * - Recursive case: Dequeue one value, recurse with n-1, then enqueue saved
 *   value at the back while unwinding.
 */
void rotate(ArrayQueue<int> &q, int n){
    if (n == 0 || q.isEmpty()) return;

    int val = q.dequeue();
    rotate(q,n-1);
    q.enqueue(val);
}

/*
 * - Purpose: Inserts value at a given position in the queue.
 * - Base case: If position is 0, enqueue value and return.
 * - Recursive case: Dequeue front to move deeper toward target position,
 *   recurse with position-1, then enqueue saved value to restore order.
 */
void insert(ArrayQueue<int> &q, int value, int position){
    if(position == 0){
        q.enqueue(value);
        return;
    }

    int val = q.dequeue();
    insert(q,value,position-1);
    q.enqueue(val);
}

/*
 * - Purpose: Deletes value at a given position in the queue.
 * - Base case: If queue is empty, stop. If position is 0, skip re-enqueueing
 *   the current front value (effectively deleting it).
 * - Recursive case: Dequeue one value, recurse with position-1, then enqueue
 *   saved values back while unwinding.
 */
void deleteValue(ArrayQueue<int> &q, int position){
    if (q.isEmpty()) return;

    int val = q.dequeue();
    if (position == 0) return;

    deleteValue(q , position-1);
    q.enqueue(val);
}

/*
 * - Purpose: Removes all occurrences of value v from the queue.
 * - Base case: If queue is empty, return.
 * - Recursive case: Dequeue one value, recurse on the rest, and during return
 *   enqueue only values that are different from v.
 */
void removeValue(ArrayQueue<int> & adt, int v){
    if (adt.isEmpty()) return;
    
    int val = adt.dequeue();
    removeValue(adt , v);

    if(val != v) adt.enqueue(val);
}

/*
 * - Helper for removeDuplicates.
 * - Purpose: Checks if val already exists in queue q.
 * - Base case: If queue is empty, val has not been seen.
 * - Recursive case: Dequeue front and compare with val; if unmatched, recurse
 *   on the remaining queue.
 */
bool is_seen(ArrayQueue<int> q , int val){
    if(q.isEmpty()) return false;

    int value = q.dequeue();
    if(value == val) return true;

    return is_seen(q,val);
}

/*
 * - Purpose: Removes duplicate values from the queue.
 * - Base case: If queue is empty, return.
 * - Recursive case: Dequeue front and recursively process the rest first;
 *   while unwinding, enqueue the value only if is_seen reports it as unseen.
 * - Helper used: is_seen(q, val) checks whether val already exists.
 */
void removeDuplicates(ArrayQueue<int> &q){
    if(q.isEmpty()) return;

    int val = q.dequeue();
    removeDuplicates(q);

    if(!is_seen(q, val)) q.enqueue(val);
}
