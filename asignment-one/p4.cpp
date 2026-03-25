// SPRING 2026 DATA STRUCTURES SECTION D11 ASSIGNMENT ONE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
#include "MyQueue.h"
#include <string>

/*
PROBLEM DESCRIPTION:
In an operating system, the N processes are executed on the Microprocessor in a time share manner i.e., each
process is given a time slice (variable parameter of the program to be set by the user) on the microprocessor
and a process can finish in multiple time slices. The time slice slots are managed via Queue. Where all the
processes are put in a circular queue and each process is given a fixed amount of time on microprocessor and
then it is put back in the queue. Once a process is done it is taken completely out of the queue.
Please simulate this queue-based system. After the simulation display the total and average time taken by
these N processes. The output of this program must match the sample output below (In case same sample
output format is not possible then provide justification and approximately match)

PROBLEM SOLUTION:

SOLUTION WITHOUT FUNCTIONS:
1. Create a Process class to represent each process with attributes like processID, isCompleted, description, time, and originalTime.
2. Create a MyQueue of Process objects to manage the processes in a circular queue.
3. Read the details of N processes from the user and enqueue them into the MyQueue.
4. Simulate the execution of processes using a while loop that continues until the queue is empty. In each iteration, dequeue a process, reduce its time by the time slice, and check if it is completed. If completed, mark it as such; otherwise, enqueue it back into the queue.
5. Keep track of the total time taken for all processes and calculate the average time per process after the simulation is complete.
6. Display the results in the specified format.

SOLUTION WITH FUNCTIONS:
1. Define a Process class as described above.
2. Implement a function readProcesses that takes a MyQueue reference and reads the details of N processes from the user, creating Process objects and enqueuing them into the MyQueue.
3. Implement a function simulate that takes a MyQueue reference, time slice, and number of processes as parameters. This function simulates the execution of processes as described in step 4 of the solution without functions, and also calculates and displays the total and average time taken for the processes.
4. Implement a function executeProcess that serves as the main driver of the program. It prompts the user for the number of processes, creates a MyQueue, calls readProcesses to populate the queue, prompts for the time slice, and then calls simulate to execute the processes and display the results.
*/

// class to represent each process with attributes like processID, isCompleted, description, time, and originalTime 
class Process {
    public:
        Process(){
            processID = "";
            isCompleted = false;
            description = "";
            time = 0;
            originalTime = 0;
        }
        Process(string id, bool flag, string desc, int t , int ot) 
            : processID(id), isCompleted(flag), description(desc), time(t) , originalTime(ot) {}
        string processID;
        bool isCompleted;
        string description;
        int time;
        int originalTime;

        friend ostream& operator<<(ostream& out, const Process& p){
            out << p.processID << "\t" << p.description << "\t" 
                << p.time << "\t" << (p.isCompleted ? "Completed" : "In Progress");
            return out;
        }
};

// Function prototypes
void readProcesses(MyQueue<Process> & q);
void simulate(MyQueue<Process> & q, int timeSlice, int n);
void executeProcess();

// Main function
int main(){
    executeProcess();
    return 0;
}

// FUNCTION DEFINITIONS
void readProcesses(MyQueue<Process> & q){
    int i = 1;
    while(!q.isFull()){
        cout << "\nEnter the detail of process " << i << endl;
        Process p;
        cout << "Enter the process ID: ";
        cin >> p.processID;
        cout << "Execution time: ";
        cin >> p.time;
        p.originalTime = p.time;
        cin.ignore();                         // clear newline before getline
        cout << "Enter the process job: ";
        getline(cin, p.description);
        q.enqueue(p);
        i++;
    }
}

void simulate(MyQueue<Process> & q, int timeSlice, int n){
    cout << "\nSimulating.....\n";
    int totalTime = 0;

    cout << "\nProcess ID \t Exection time \t Time Remaining \t Status\n";
    cout << "-------------------------------------------------------------\n";

    while(!q.isEmpty()){
        Process p = q.dequeue();
        p.time -= timeSlice;
        if(p.time <= 0){
            p.isCompleted = true;
            p.time = 0;
        } else {
            q.enqueue(p);
        }
        cout << p.processID << "\t" << p.originalTime << "\t\t" 
             << p.time << "\t\t" 
             << (p.isCompleted ? "Completed" : "In Progress") << endl;
        totalTime += timeSlice;
    }

    cout << "\nAll processes completed in " << totalTime << " time units.\n";
    cout << "Average time per process: " << (double)totalTime / n << " time units.\n";
}

void executeProcess(){
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;
    MyQueue<Process> q(n);
    readProcesses(q);
    int timeSlice;
    cout << "\nEnter the time slice for execution: ";
    cin >> timeSlice;
    simulate(q, timeSlice, n);
}
