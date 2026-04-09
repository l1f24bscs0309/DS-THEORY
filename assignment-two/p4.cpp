// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT TWO
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
// File p4.cpp contains complete code of Queue Problem 2:
// Message Queue Calculator: reader, operand, and calculator programs
// coordinated through file-based queues (commands.txt, data.txt, results.txt)
// BONUS: also supports "average", "maximum", "minimum" commands

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "MyQueue.h"

/*
PROBLEM DESCRIPTION:
Three programs coordinate via a message queue system using files:
1. Reader program: reads operations from user, stores in CommandQueue, writes to "commands.txt"
2. Operand program: reads commands from "commands.txt", asks user for operands per command,
   stores data in DataQueue, writes to "data.txt"
3. Calculator program: reads commands from "commands.txt" and data from "data.txt",
   applies each command to its operands, stores results in ResultQueue, writes to "results.txt"

Bonus: commands also include "average", "maximum", "minimum"

PROBLEM SOLUTION:

Queue Only Solution without functions
--------------------------------------
READER PROGRAM:
1. Create a CommandQueue of some reasonable size (e.g., 100)
2. Read command names from the user one by one until they enter "done"
   e.g. "Addition", "Subtraction", "Multiplication" ...
3. Enqueue each command into CommandQueue
   CommandQueue: [Addition -> Subtraction -> Multiplication]
4. Open file "commands.txt" for writing
5. Dequeue each command from CommandQueue and write to the file separated by spaces
6. Close the file

OPERAND PROGRAM:
1. Open "commands.txt" and read all commands into CommandQueue
   CommandQueue: [Addition -> Subtraction -> Multiplication]
2. Create a DataQueue of appropriate size
3. For each command in CommandQueue, ask the user to enter two operands (or more for bonus)
   and enqueue each operand into DataQueue
   e.g. for "Addition": enter 2 3 => enqueue 2, 3
        for "Subtraction": enter 5 6 => enqueue 5, 6
   DataQueue: [2 -> 3 -> 5 -> 6 -> ...]
4. Write DataQueue to "data.txt", one row per command (two numbers per line)
5. Close the file

CALCULATOR PROGRAM:
1. Read commands from "commands.txt" into CommandQueue
2. Read operands from "data.txt" into DataQueue (as integers)
3. Create a ResultQueue of appropriate size
4. For each command in CommandQueue, dequeue two operands from DataQueue
   Apply the command, enqueue result into ResultQueue
   e.g. Addition: a=2, b=3 => result=5
        Subtraction: a=5, b=6 => result=-1
5. Write ResultQueue to "results.txt" (all results on one line separated by spaces)
6. At the end, three files exist: commands.txt, data.txt, results.txt

Queue Only Solution with functions
--------------------------------------
Functions to use:
1. void runReader()                            - reads commands, writes commands.txt
2. void runOperand()                           - reads commands.txt, asks operands, writes data.txt
3. void runCalculator()                        - reads commands.txt + data.txt, writes results.txt
4. int applyCommand(const string& cmd, int a, int b) - applies command to two operands
5. void writeQueueToFile(MyQueue<string>&, const string&) - writes queue to file
6. void readCommandsFromFile(MyQueue<string>&, const string&) - reads file into queue
7. void displayResults()                       - reads and displays results.txt

1. Create a main menu that lets the user run reader, operand, or calculator program
   in sequence to demonstrate the full pipeline.
2. For demo purposes, run all three automatically with test data.
*/

/********* GLOBAL FUNCTION PROTOTYPES *********/

void runReader();
void runOperand();
void runCalculator();
int applyCommand(const string & cmd, int a, int b, int c);
int applyCommandBonus(const string & cmd, MyQueue<int> & dataQ, int count);
void writeCommandsToFile(MyQueue<string> & q, const string & filename);
void readCommandsFromFile(MyQueue<string> & q, const string & filename);
void readDataFromFile(MyQueue<int> & q, const string & filename);
void displayFile(const string & filename);
int countLinesInFile(const string & filename);

/********* DRIVER FUNCTION MAIN *********/

int main(){
    cout << "====================================================\n";
    cout << " MESSAGE QUEUE CALCULATOR\n";
    cout << "====================================================\n\n";
    cout << "This program runs three stages:\n";
    cout << "  1. Reader  - reads commands from user, writes commands.txt\n";
    cout << "  2. Operand - reads commands.txt, asks for operands, writes data.txt\n";
    cout << "  3. Calculator - reads both files, computes results, writes results.txt\n\n";

    cout << "----- STAGE 1: READER -----\n";
    runReader();

    cout << "\n----- STAGE 2: OPERAND -----\n";
    runOperand();

    cout << "\n----- STAGE 3: CALCULATOR -----\n";
    runCalculator();

    cout << "\n====== FINAL FILES ======\n";
    cout << "\ncommands.txt:\n";
    displayFile("commands.txt");
    cout << "\ndata.txt:\n";
    displayFile("data.txt");
    cout << "\nresults.txt:\n";
    displayFile("results.txt");

    return 0;
}

/********* GLOBAL FUNCTION CODE *********/

// writes all elements of string queue to a file, space-separated on one line
void writeCommandsToFile(MyQueue<string> & q, const string & filename){
    ofstream out(filename);
    if(!out){
        cout << "Error opening " << filename << " for writing\n";
        return;
    }
    MyQueue<string> temp(q);
    bool first = true;
    while(!temp.isEmpty()){
        if(!first) out << " ";
        out << temp.dequeue();
        first = false;
    }
    out << endl;
    out.close();
}

// reads space-separated commands from a file into the queue
void readCommandsFromFile(MyQueue<string> & q, const string & filename){
    ifstream in(filename);
    if(!in){
        cout << "Error opening " << filename << " for reading\n";
        return;
    }
    string word;
    while(in >> word){
        if(!q.isFull()) q.enqueue(word);
    }
    in.close();
}

// reads integers from a file into the queue (one integer per token)
void readDataFromFile(MyQueue<int> & q, const string & filename){
    ifstream in(filename);
    if(!in){
        cout << "Error opening " << filename << " for reading\n";
        return;
    }
    int val;
    while(in >> val){
        if(!q.isFull()) q.enqueue(val);
    }
    in.close();
}

// count lines in a file (used to estimate queue sizes)
int countLinesInFile(const string & filename){
    ifstream in(filename);
    if(!in) return 0;
    int count = 0;
    string line;
    while(getline(in, line)) count++;
    return count;
}

// displays the contents of a file to the screen
void displayFile(const string & filename){
    ifstream in(filename);
    if(!in){ cout << "(file not found)\n"; return; }
    string line;
    while(getline(in, line)) cout << line << "\n";
}

// applies a basic arithmetic command to two operands a and b
// also supports bonus commands: average (of a and b), maximum, minimum
// third parameter c is used for three-operand bonus commands
int applyCommand(const string & cmd, int a, int b, int c = 0){
    if(cmd == "Addition")       return a + b;
    if(cmd == "Subtraction")    return a - b;
    if(cmd == "Multiplication") return a * b;
    if(cmd == "Division"){
        if(b == 0){ cout << "Error: division by zero\n"; return 0; }
        return a / b;
    }
    // BONUS commands
    if(cmd == "average")  return (a + b + c) / 3;
    if(cmd == "maximum")  return (a > b ? (a > c ? a : c) : (b > c ? b : c));
    if(cmd == "minimum")  return (a < b ? (a < c ? a : c) : (b < c ? b : c));
    cout << "Unknown command: " << cmd << endl;
    return 0;
}

// READER PROGRAM
// reads commands from the user and writes them to commands.txt
void runReader(){
    const int MAX_CMDS = 100;
    MyQueue<string> commandQueue(MAX_CMDS);

    cout << "Available commands: Addition, Subtraction, Multiplication, Division\n";
    cout << "Bonus commands:     average, maximum, minimum\n";
    cout << "Enter commands one by one. Type 'done' when finished.\n";

    string cmd;
    int num = 1;
    while(!commandQueue.isFull()){
        cout << "Command " << num << ": ";
        cin >> cmd;
        if(cmd == "done") break;
        commandQueue.enqueue(cmd);
        num++;
    }

    writeCommandsToFile(commandQueue, "commands.txt");
    cout << "Commands written to commands.txt\n";
}

// OPERAND PROGRAM
// reads commands from commands.txt and asks user for operands per command
// writes all operands to data.txt (one line per command)
void runOperand(){
    MyQueue<string> commandQueue(100);
    readCommandsFromFile(commandQueue, "commands.txt");

    int cmdCount = 0;
    MyQueue<string> cmdCopy(commandQueue);
    while(!cmdCopy.isEmpty()){ cmdCopy.dequeue(); cmdCount++; }

    ofstream dataOut("data.txt");
    if(!dataOut){
        cout << "Error opening data.txt for writing\n";
        return;
    }

    MyQueue<string> temp(commandQueue);
    cout << "For each command, enter the required operands.\n";
    cout << "(Addition, Subtraction, Multiplication, Division need 2 operands)\n";
    cout << "(average, maximum, minimum need 3 operands)\n\n";

    while(!temp.isEmpty()){
        string cmd = temp.dequeue();
        cout << "Command: " << cmd << "\n";
        // bonus commands (average, maximum, minimum) need 3 operands; others need 2
        bool isBonus = (cmd == "average" || cmd == "maximum" || cmd == "minimum");
        int numOperands = isBonus ? 3 : 2;
        cout << "Enter " << numOperands << " operands: ";
        for(int i = 0; i < numOperands; i++){
            int val;
            cin >> val;
            dataOut << val;
            if(i < numOperands - 1) dataOut << " ";
        }
        dataOut << "\n";
    }

    dataOut.close();
    cout << "Operands written to data.txt\n";
}

// CALCULATOR PROGRAM
// reads commands and data files, applies operations, writes results.txt
void runCalculator(){
    MyQueue<string> commandQueue(100);
    readCommandsFromFile(commandQueue, "commands.txt");

    // count commands to know how many operands to expect
    int cmdCount = 0;
    MyQueue<string> cmdCopy(commandQueue);
    while(!cmdCopy.isEmpty()){ cmdCopy.dequeue(); cmdCount++; }

    // read all data from data.txt
    MyQueue<int> dataQueue(cmdCount * 3 + 10);
    readDataFromFile(dataQueue, "data.txt");

    // result queue and file
    MyQueue<int> resultQueue(cmdCount + 10);
    ofstream resultsOut("results.txt");
    if(!resultsOut){
        cout << "Error opening results.txt for writing\n";
        return;
    }

    cout << "Processing commands...\n";
    cout << "Command\t\t\tOperands\t\tResult\n";
    cout << "-----------------------------------------------------------\n";

    while(!commandQueue.isEmpty()){
        string cmd = commandQueue.dequeue();
        bool isBonus = (cmd == "average" || cmd == "maximum" || cmd == "minimum");

        int a = dataQueue.isEmpty() ? 0 : dataQueue.dequeue();
        int b = dataQueue.isEmpty() ? 0 : dataQueue.dequeue();
        int c = (isBonus && !dataQueue.isEmpty()) ? dataQueue.dequeue() : 0;

        int result = applyCommand(cmd, a, b, c);
        resultQueue.enqueue(result);

        if(isBonus)
            cout << cmd << "\t\t" << a << " " << b << " " << c << "\t\t\t" << result << "\n";
        else
            cout << cmd << "\t\t" << a << " " << b << "\t\t\t" << result << "\n";
    }

    // write results to file (space-separated on one line)
    MyQueue<int> resTemp(resultQueue);
    bool first = true;
    while(!resTemp.isEmpty()){
        if(!first) resultsOut << " ";
        resultsOut << resTemp.dequeue();
        first = false;
    }
    resultsOut << "\n";
    resultsOut.close();

    cout << "\nResults written to results.txt\n";
}
