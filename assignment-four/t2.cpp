// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FOUR
// Name of Student: Muhammad Ikram ul haq
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "ArrayStack.h"

void display(ArrayStack<int> as);
void recursiveCopy(ArrayStack<int> src, ArrayStack<int> & copy);
int max(ArrayStack<int> as);
bool isFound(ArrayStack<int> s, int x);
int countValue(ArrayStack<int> s, int x);
// passed stack by reference so that it persists after the function call
void insert(ArrayStack<int> &s, int value, int position);// insert value at position
// passed stack by reference so that it persists after the function call
void deleteValue(ArrayStack<int> &s, int position);// selete value at position
void removeValue(ArrayStack<int> & adt, int v); // remove all occurrences of v
void removeDuplicates(ArrayStack<int> &s);

int main () {
    cout << "=============== Stack Display ===============\n";
    ArrayStack<int> as(10);
    as.push(1);
    as.push(2);
    as.push(3);
    as.push(3);
    as.push(4);
    as.push(5);
    display(as);

    cout << "\n=============== Stack Copy ===============\n";
    ArrayStack<int> copy(10);
    recursiveCopy(as,copy);
    display(copy);

    cout << "\n=============== Stack Max ===============\n";
    cout << max(as) << endl;

    cout << "\n=============== Stack Search ===============\n";
    if(isFound(as,3)) cout << "Found\n";
    else cout << "Not Found\n";

    cout << "\n=============== Stack Count Value ===============\n";
    cout << "this value appears: "<<countValue(as,3) << " times." << endl;

    cout << "\n=============== Stack Insert ===============\n";
    insert(as,10,3);
    display(as);

    cout << "\n=============== Stack Delete ===============\n";
    deleteValue(as,3);
    display(as);


    ArrayStack<int> s(10);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(30);
    cout << "\n=============== Stack Display Before Remove===============\n";
    display(s);
    cout << "\n=============== Stack Remove Value ===============\n"; 
    removeValue(s,30);
    display(s);

    cout << "\n=============== Stack Remove Duplicates ===============\n";
    removeDuplicates(as);
    display(as);

    return 0;
}

/*
 * - Purpose: Displays stack values from bottom to top using recursion.
 * - Base case: If stack is empty, stop recursion.
 * - Recursive case: Pop one value and recurse on the smaller stack first; when calls return, print the saved value to keep original bottom-to-top order.
 */
void display(ArrayStack<int> as) {
    if(as.isEmpty()) return;
    int val = 0;
    as.pop(val);
    display(as);
    cout << val << " ";
}

/*
 * - Purpose: Copies all elements from src to copy while preserving order.
 * - Base case: If source stack is empty, return.
 * - Recursive case: Pop top from src and recurse on the reduced src; during unwinding, push saved values into copy so order matches src.
 */

void recursiveCopy(ArrayStack<int> src , ArrayStack<int> &copy){
    if(src.isEmpty()) return;

    int value = 0;
    src.pop(value);
    recursiveCopy(src,copy);
    copy.push(value);
}

/*
 * - Purpose: Returns the maximum value in the stack recursively.
 * - Base case: If stack is empty, return 0.
 * - Recursive case: Pop one value, compute max of the remaining stack recursively, then return the larger between current value and recursive result.
 */

int max(ArrayStack<int> as){
    if(as.isEmpty()) return 0;
    int val = 0;
    as.pop(val);
    return val > max(as) ? val : max(as);
}

/*
 * - Purpose: Checks whether value x exists in the stack.
 * - Base case: If stack is empty, value is not found.
 * - Recursive case: Pop top and compare with x; if not equal, recurse on the reduced stack until match is found or stack ends.
 */
bool isFound(ArrayStack<int> s, int x){
    if(s.isEmpty()) return false;
    int val = 0;
    s.pop(val);
    if(val == x) return true;
    return isFound(s,x);
}

/*
 * - Purpose: Counts total occurrences of value x in the stack.
 * - Base case: If stack is empty, count is 0.
 * - Recursive case: Pop top, convert current match into 1/0, recurse on remaining stack, and add both counts together.
 */
int countValue(ArrayStack<int> s, int x){
    if(s.isEmpty()) return 0;

    int val = 0;
    s.pop(val);
    int count = val == x ? 1 : 0;
    return count + countValue(s,x);
}

/*
 * - Purpose: Inserts value at given position from top using recursion.
 * - Base case: If position is 0, push value and return.
 * - Recursive case: Pop top to move deeper toward target position, recurse with position-1, then push popped item back to restore stack structure.
 */
void insert(ArrayStack<int> &s, int value, int position){
    if (position == 0){
        s.push(value);
        return;
    }

    int temp;
    s.pop(temp);
    insert(s, value, position - 1);

    s.push(temp);
}

/*
 * - Purpose: Deletes element at given position from top.
 * - Base case: If stack is empty, stop. If position is 0, discard popped value.
 * - Recursive case: Pop top and recurse with position-1; once target is deleted in deeper call, push saved values back while unwinding.
 */
void deleteValue(ArrayStack<int> &s, int position){
    if(s.isEmpty()) return;

    int val = 0;
    s.pop(val);

    if(position == 0) return;
    deleteValue(s,position-1);

    s.push(val);
}

/*
 * - Purpose: Removes all occurrences of value v from the stack.
 * - Base case: If stack is empty, return.
 * - Recursive case: Pop top and recurse on the rest; during return, reinsert only those values that are different from v.
 */
void removeValue(ArrayStack<int> & adt, int v){
    if(adt.isEmpty()) return;

    int val = 0;
    adt.pop(val);
    removeValue(adt,v);

    if(val != v){
        adt.push(val);
    }
}

/*
 * - Helper function for removeDuplicates.
 * - Purpose: Checks if val already exists in stack s.
 * - Base case: If stack is empty, val has not been seen.
 * - Recursive case: Pop top and compare with val; if different, recurse on the remaining stack until found or empty.
 */
bool is_seen(ArrayStack<int> s, int val) {
   if(s.isEmpty()) return false; 
    
   int value;
   s.pop(value);
   if(val == value) return true;
     
   return is_seen(s,val);
}

/*
 * - Purpose: Removes duplicate values from the stack.
 * - Base case: If stack is empty, return.
 * - Recursive case: Pop top and recursively clean the remaining stack first; then use is_seen to push value only if it does not already exist.
 * - Helper used: is_seen(s, val) checks whether val already exists.
 */
void removeDuplicates(ArrayStack<int> &s){
    if(s.isEmpty()) return;

    int val ;
    s.pop(val);

    removeDuplicates(s);

    if(!is_seen(s,val)){
        s.push(val);
    }
}
