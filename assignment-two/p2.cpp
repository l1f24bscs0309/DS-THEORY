// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT TWO
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File p2.cpp contains complete code of Stack Problem 2:
// Part A: Undo and Redo using Stack (directions with verification)
// Part B: Prefix, Postfix, and Infix math expression evaluation using Stack

#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "MyStack.h"

/*
PROBLEM DESCRIPTION:

Part A: Undo and Redo using Stack
----------------------------------
Read directions from one UCP location to another and store them on a Stack.
Display each direction and let the user approve (yes) or correct (no) it.
If the user says no, update the direction on the Stack.
Once all directions are verified, display the final verified route.

PROBLEM SOLUTION:

Part A: Undo and Redo using Stack
----------------------------------
Solution without functions
--------------------------
1. Create two stacks: undoStack (stores verified directions) and a temp stack.
2. Read the starting and destination locations.
3. Read directions one by one until user enters "done" and push each onto undoStack.

step 1: Go to elevator
---
step 2: Take elevator to first floor
---

   undoStack: [Go to elevator | Take elevator to first floor | ...]

4. Now display each direction to user one by one for verification.
   For this, we must display them in ORDER (first entered = first displayed).
   Since undoStack is LIFO, to display in order we need to transfer to a display stack first.

   Transfer all directions from undoStack to displayStack (reverses order):
   displayStack top = "Go to elevator" (first step)

5. Pop from displayStack, ask user "yes or no":
   - If "yes": push to verifiedStack (direction is approved)
   - If "no": read new correct direction, push corrected one to verifiedStack

6. After verifying all directions, verifiedStack has them in reverse display order.
   Transfer to a final printStack and display.

Solution with functions
-----------------------
Functions to use:
1. readDirections(MyStack<string> * s)     - read steps from user, push to stack
2. verifyDirections(MyStack<string> * s,
                    MyStack<string> * verified,
                    string from, string to)  - display and verify each direction
3. displayRoute(MyStack<string> * s)       - print final route with arrows


/********* GLOBAL FUNCTION PROTOTYPES *********/

// Part A
void readDirections(MyStack<string> * s, string & from, string & to);
void verifyDirections(MyStack<string> * s, MyStack<string> * verified, const string & from, const string & to);
void displayRoute(MyStack<string> * s);

// Part B - expression evaluation helpers
bool isOperator(const string & token);
int precedence(const string & token);
int applyOp(int a, int b, const string & op);
int evaluatePrefix(MyStack<int> & st, const string & expr);
int evaluatePostfix(MyStack<int> & st, const string & expr);
int evaluateInfix(MyStack<int> & opStack, const string & expr);

/********* DRIVER FUNCTION MAIN *********/

int main(){


    const int MAX_STEPS = 20;
    MyStack<string> directionStack(MAX_STEPS);
    MyStack<string> verifiedStack(MAX_STEPS);

    string from, to;
    readDirections(&directionStack, from, to);
    verifyDirections(&directionStack, &verifiedStack, from, to);

    cout << "\nHere are the verified directions:\n";
    displayRoute(&verifiedStack);

    return 0;
}

/********* GLOBAL FUNCTION CODE *********/

// reads directions from user step by step and pushes onto the stack
// also sets the from and to location strings
void readDirections(MyStack<string> * s, string & from, string & to){
    cout << "Please enter starting location: ";
    getline(cin, from);
    cout << "Please enter destination location: ";
    getline(cin, to);

    int stepNum = 1;
    string step;
    cout << "Enter steps one by one. Type 'done' when finished.\n";
    while(!s->isFull()){
        cout << "Please enter step " << stepNum << ": ";
        getline(cin, step);
        if(step == "done") break;
        s->push(step);
        stepNum++;
    }
}

void verifyDirections(MyStack<string> * s, MyStack<string> * verified, const string & from, const string & to){

    int size = 0;
    string val;
    MyStack<string> displayStack(100);

    MyStack<string> reversal(size + 5);
    MyStack<string> tempCount(*s);

    while(!tempCount.isEmpty()){
        tempCount.pop(val);
        reversal.push(val);
        size++;
    }

    while(!reversal.isEmpty()){
        reversal.pop(val);
        displayStack.push(val);
    }

    cout << "\nPlease verify the directions from " << from << " to : " << to << endl;

    MyStack<string> displayOrder(size + 5);

    while(!displayStack.isEmpty()){
        displayStack.pop(val);
        displayOrder.push(val);
    }
    // displayOrder top = first step as stack is reversed twice; 

    int stepNum = 1;
    MyStack<string> tempVerified(size + 5);

    while(!displayOrder.isEmpty()){
        displayOrder.pop(val);
        string answer;
        cout << "step " << stepNum << ": " << val << ": yes or no: ";
        cin >> answer;
        cin.ignore();
        if(answer == "yes"){
            tempVerified.push(val);
        } else {
            string corrected;
            cout << "Please enter correct direction: ";
            getline(cin, corrected);
            tempVerified.push(corrected);
        }
        stepNum++;
    }
    // tempVerified top = last verified step
    // verified should have first step at top (displayRoute pops and prints first step first)
    // transfer tempVerified to verified via reversal so first step ends up at top
    MyStack<string> verReversal(size + 5);
    while(!tempVerified.isEmpty()){
        tempVerified.pop(val);
        verReversal.push(val);
    }
    while(!verReversal.isEmpty()){
        verReversal.pop(val);
        verified->push(val);
    }
}

void displayRoute(MyStack<string> * s){
    int size = 0;
    string val;
    MyStack<string> temp(*s);
    while(!temp.isEmpty()){
        temp.pop(val);
        size++;
    }

    MyStack<string> reversal(size + 5);
    MyStack<string> copy(*s);
    while(!copy.isEmpty()){
        copy.pop(val);
        reversal.push(val);
    }

    while(!reversal.isEmpty()){
        reversal.pop(val);
        cout << val << " -> ";}
    cout << endl;
}
