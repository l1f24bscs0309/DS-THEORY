// SPRING 2026 DATA STRUCTURES SECTION D11 ASSIGNMENT ONE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
#include "MyQueue.h"
#include <string>
#include <fstream>

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

####################################################################

DOING THE BONUS TASK WITH FILE INPUT AND PRIORITY SCHEDULING:

####################################################################

1. Modify the Process class to include a priority attribute.This will be used to determine the order of execution of processes in the queue.

2. Implement a function readProcessesFromFile that reads process details from a file. The file should have a specific format 
(e.g., processID, time, priority, description) for each process. This function will create 
Process objects based on the file input and enqueue them into the MyQueue.

3.Making a function that will deqeueue the process with the highes proioriy , this works by making a temp queue of the same 
size as queue and then making variables to keep track of the highest priority and the process with the highest priority and then we 
will dequeue each process from the original queue and compare its priority with the highest priority 
and if it is higher than the highest priority we will update the highest priority and the process with the highest priority and 
then we will enqueue this process in the temp queue and after we have checked all the processes in the original 
queue we will enqueue all the processes from the temp queue back to the original queue except for the process with 
the highest priority which we will return from this function.

4. this was the main logic now we just call this function instead of dequeueing the first process from the queue in the simulate function and 
then we will reduce the priority of the process by 1 after each time slice and if the priority is 
less than 1 we will set it to 1 so that it does not become negative and then we will check if the process is completed or not 
and if it is not completed we will enqueue it back to the queue and then we will print the details of the 
process after each time slice and at the end we will print the total time taken for all processes and the average time per process.




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
            priority= 0;
        }
        Process(string id, bool flag, string desc, int t , int ot , int pc = 0) 
            : processID(id), isCompleted(flag), description(desc), time(t) , originalTime(ot) , priority(pc){}
        string processID;
        bool isCompleted;
        string description;
        int time;
        int originalTime;
        int priority;

        friend ostream& operator<<(ostream& out, const Process& p){
            out << p.processID << "\t" << p.description << "\t" 
                << p.time << "\t" << (p.isCompleted ? "Completed" : "In Progress");
            return out;
        }
};

// Function prototypes
void readProcesses(MyQueue<Process> & q);
void readProcessesFromFile(MyQueue<Process> & q , const string & filename);
void simulate(MyQueue<Process> & q, int timeSlice, int n);
Process dequeueHighestPriority(MyQueue<Process> &q);
int getProcessCount(const string & filename);
int getQSize(MyQueue<Process> & q);
void executeProcess();

// Main function
int main(){
    executeProcess();
    return 0;
}

int getQSize(MyQueue<Process> & q){
    MyQueue<Process> temp(q);
    int size = 0;
    while(!temp.isEmpty()){
        temp.dequeue();
        size++;
    }
    return size;
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
        cin.ignore();                         
        cout << "Enter the process job: ";
        getline(cin, p.description);
        q.enqueue(p);
        i++;
    }
}

int getProcessCount(const string & filename){
    ifstream in(filename);
    if(!in){
        cout << "Error opening file: " << filename << endl;
        return 0;
    }
    int count = 0;
    string line;
    while(getline(in, line)){
        if(!line.empty()){
            count++;
        }
    }
    in.close();
    return count;
}

void readProcessesFromFile(MyQueue<Process> & q, const string & filename){
    ifstream in(filename);
    if(!in){
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while(getline(in, line)){
        if(line.empty()) continue;
        
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);
        int pos3 = line.find(',', pos2 + 1);

        string id       = line.substr(0, pos1);
        int time        = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        int priority    = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        string desc     = line.substr(pos3 + 1);

        Process p(id, false, desc, time, time, priority);
        q.enqueue(p);
    }
    in.close();
}

Process dequeueHighestPriority(MyQueue<Process> &q){
    int size = getQSize(q);
    MyQueue<Process> temp(size);
    Process highest;
    int highest_priority = -1;

    while(!q.isEmpty()){
        Process p = q.dequeue();
        if (p.priority > highest_priority){
            highest = p;
            highest_priority = p.priority;
        }
        temp.enqueue(p);
    }
    while(!temp.isEmpty()){
        Process p = temp.dequeue();
        if(p.processID != highest.processID){
            q.enqueue(p);
        }
    }
    return highest;
}

void simulate(MyQueue<Process> & q, int timeSlice, int n){
    cout << "\nSimulating.....\n";
    int totalTime = 0;

    cout << "\nProcess ID \t Exection time \t Time Remaining \t Priority \t Status\n";
    cout << "-------------------------------------------------------------------------------------\n";

    while(!q.isEmpty()){
        Process p = dequeueHighestPriority(q);
        p.time -= timeSlice;
        p.priority--;
        if(p.priority < 1) p.priority = 1;
        if(p.time <= 0){
            p.isCompleted = true;
            p.time = 0;
        } else {
            q.enqueue(p);
        }
        cout << p.processID << "\t\t\t" << p.originalTime << "\t\t" 
             << p.time << "\t\t   " << p.priority << "\t\t"
             << (p.isCompleted ? "Completed" : "In Progress") << endl;
        totalTime += timeSlice;
    }

    cout << "\nAll processes completed in " << totalTime << " time units.\n";
    cout << "Average time per process: " << (double)totalTime / n << " time units.\n";
}

void executeProcess(){
    // cout << "Enter the number of processes: ";
    // int n;
    // cin >> n;
    int n = getProcessCount("process.csv");
    MyQueue<Process> q(n);
    // readProcesses(q);
    readProcessesFromFile(q, "process.csv");
    int timeSlice;
    cout << "\nEnter the time slice for execution: ";
    cin >> timeSlice;
    simulate(q, timeSlice, n);
}
