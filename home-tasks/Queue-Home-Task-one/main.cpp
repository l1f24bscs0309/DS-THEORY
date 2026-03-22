#include "Queue1.h"
#include "MQ1.h"

// size is to have a queue of 10 and input of 5 so for shifting and inserting we have enough space in the queue to test the functions without worrying about overflow
const int SIZE = 10;
const int INPUT = 5;

// return the number of elements in the queue without modifying it
int getSize(Queue* q){
    int size = 0;
    // this is something i didnot knew how to do it i used ai to make the copy of the queue i thought it would work like i did with stack 
    MyQueue temp(*(MyQueue*)q);
    while(!temp.isEmpty()){
        temp.dequeue();
        size++;
    }
    return size;
}

// Non-destructive copy: uses a temp so src is preserved
// returns true if q1 and q2 have the same elements in the same order, false otherwise
bool isEqual(Queue* q1, Queue* q2){
    MyQueue temp1(*(MyQueue*)q1);
    MyQueue temp2(*(MyQueue*)q2);

    if(getSize(q1) != getSize(q2)) return false;

    int val1, val2;
    while(!temp1.isEmpty() && !temp2.isEmpty()){
        val1 = temp1.dequeue();
        val2 = temp2.dequeue();
        if(val1 != val2) return false;
    }
    return temp1.isEmpty() && temp2.isEmpty();
}

//this function reads INPUT number of integers from the user and enqueues them into the provided queue
void read(Queue* q, istream& in){
    int val;
    cout << "enter the values to move in the queue : \n";
    for(int i = 0; i < INPUT; i++){
        in >> val;
        q->enqueue(val);
    }
}

// this function copies elements from src to dest without modifying src. It stops when either src is empty or dest is full.
void copy(Queue* src, Queue* dest){
    MyQueue temp(*(MyQueue*)src);   // work on a copy of src
    int val;
    while(!temp.isEmpty() && !dest->isFull()){
        val = temp.dequeue();
        dest->enqueue(val);
    }
}

// this function inserts all elements of src into dest starting at position pos. It shifts existing elements in dest to the right to make space for src. If pos is greater than the size of dest, it appends src at the end.
void insert(Queue* src, Queue* dest, int pos){
    int destSize = getSize(dest);
    int srcSize  = getSize(src);

    MyQueue before(SIZE);
    MyQueue after(SIZE);

    int val;

    for(int i = 0; i < pos; i++){
        val = dest->dequeue();
        before.enqueue(val);
    }
    for(int i = pos; i < destSize; i++){
        val = dest->dequeue();
        after.enqueue(val);
    }

    while(!before.isEmpty()){
        dest->enqueue(before.dequeue());
    }
    MyQueue tempSrc(*(MyQueue*)src);
    while(!tempSrc.isEmpty()){
        dest->enqueue(tempSrc.dequeue());
    }
    while(!after.isEmpty()){
        dest->enqueue(after.dequeue());
    }
}

// almost similar to shifting and inserting 
void shiftRight(Queue* q, int pos){
    int size = getSize(q);

    if(pos >= size - 1){
        cout << "Cannot shift right: position is already at the end." << endl;
        return;
    }

    int elements[SIZE];
    for(int i = 0; i < size; i++){
        elements[i] = q->dequeue();
    }

    int tmp        = elements[pos];
    elements[pos]  = elements[pos + 1];
    elements[pos+1]= tmp;

    for(int i = 0; i < size; i++){
        q->enqueue(elements[i]);
    }
}

// this was a simple function to do
void stats(Queue* q, int &sum, float &average){
    sum = 0;
    average = 0;

    int size = getSize(q);
    if(size == 0) return;

    MyQueue temp(*(MyQueue*)q);
    int var;
    while(!temp.isEmpty()){
        var = temp.dequeue();
        sum += var;
    }
    average = (float)sum / size;
}

//helper function to check if a number is palindrome or not
bool isPalindrome(int num){
    if(num < 0) return false;
    int original = num;
    int reversed = 0;
    while(num > 0){
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    return original == reversed;
}

// this function checks if all elements in the queue are palindromes. It uses a temp queue to preserve the original queue.
bool isPalindrome(Queue* q){
    MyQueue temp(*(MyQueue*)q);  
    int var;
    while(!temp.isEmpty()){
        var = temp.dequeue();
        if(!isPalindrome(var)) return false;
    }
    return true;
}

bool isPalindromeSingleDigit(Queue* q ){
    MyQueue temp(*(MyQueue*)q);     
    int number , reverseNo;
    int val;
    while(!temp.isEmpty()){
        val = temp.dequeue();
        if(val < 10 && val >= 0){
            continue;
        }
        else if(val < 0){
            return false;
        }
        number = val;
        reverseNo = 0;
        while(number > 0){
            int digit = number % 10;
            reverseNo = reverseNo * 10 + digit;
            number /= 10;
        }
        if(reverseNo != val) return false;
    }
    return true;
}

//main is written with the help of chat gpt for better outputs
int main(){
    // Test read()
    MyQueue q1(SIZE);
    read(&q1, cin);
    cout << "Q1: "; q1.display(cout);

    // Test copy()
    MyQueue q2(SIZE);
    copy(&q1, &q2);
    cout << "Q2 (copy of Q1): "; q2.display(cout);

    // Test isEqual()
    cout << "Q1 == Q2? " << (isEqual(&q1, &q2) ? "Yes" : "No") << endl;

    // Test getSize()
    cout << "Size of Q2: " << getSize(&q2) << endl;

    // Test stats()
    MyQueue q3(SIZE);
    read(&q3, cin);
    cout << "Q3: "; q3.display(cout);
    int sum; float avg;
    stats(&q3, sum, avg);
    cout << "Sum: " << sum << ", Average: " << avg << endl;
    cout << "Q3 after stats (should be unchanged): "; q3.display(cout);

    // Test insert()
    MyQueue src(SIZE), dest(SIZE);
    read(&src, cin);
    read(&dest, cin);
    cout << "Src before insert: "; src.display(cout);
    cout << "Dest before insert: "; dest.display(cout);
    insert(&src, &dest, 2);
    cout << "Dest after insert at pos 2: "; dest.display(cout);

    // Test shiftRight()
    MyQueue q4(SIZE);
    read(&q4, cin);
    cout << "Q4 before shiftRight: "; q4.display(cout);
    shiftRight(&q4, 2);
    cout << "Q4 after shiftRight at pos 2: "; q4.display(cout);

    // Test isPalindrome()
    MyQueue q5(SIZE);
    read(&q5, cin);
    cout << "Q5: "; q5.display(cout);
    cout << "All elements palindromes? " << (isPalindrome(&q5) ? "Yes" : "No") << endl;

    return 0;
}
