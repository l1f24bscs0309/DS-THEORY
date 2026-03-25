// SPRING 2026 DATA STRUCTURES SECTION D11 ASSIGNMENT ONE
// Name of Student:MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309
#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
using namespace std;

/*
PROBLEM DESCRIPTION:
The following diagram shows a puzzle, each black box is blocked and each white box can be crossed. One step
moves from one box to another box left, right, up, down and across. You will need to write a complete C++
program using Stack or Queue as the Data Structure and plots a passage from the starting box (S) to the ending
box (E). The passage may not be the shortest path. An example output of the program is shown below for the
particular box of the given diagram. Your program must work for any puzzle. You will need to figure out how to
read Puzzle data from user, store each box in Stack or Queue and then plot a passage. (Passage Plot: S →1 → 2
→3 →8 →12 → 11 → 15 → 21 → 22 →23 → E). First do the problem using Stack only and then using Queue
Only in the same main.

PROBLEM SOLUTION:

STACK ONLY SOLUTION WITH OUT FUNCTIONS
-------------------------------------
1. We will represent the grid as a 2D array where -1 represents a blocked box and 0 represents a white box.

2. Making a stack of size 25 beacuse the grid is 5x5 and in worst case we will have to visit all the boxes.

3. To keep track of the visited boxes we will use a visited 2D array of the same size as the grid and initialize it with false.

4. Then to find the path we will keep track of the previous box for each box in a parent 2D 
array of the same size as the grid and initialize it with (-1,-1) to indicate that there is no parent.

5. We will start from the starting box (0,0) and push it onto the stack and mark it as visited.

6. to check all the neighbors of the current box we will use two arrays dr and dc 
to represent the change in row and column for the 8 possible moves (up, down, left, right and diagonals).

7. now pop the (0,0) and check all the neghbours of it and if any neighbour is invalid 
(that is out of bounds, blocked or already visited) we will ignore and continue 

8. we will keep track of each valid neighbour in the nr and nc variables and check each neghbour one by one

9. if the neighbour is valid we will mark it as visited 

10. then we will set the parent of the neighbour to the current box this way we will keep track of the path

11. we will push this neighbour on the stack and then for this index again all the steps will be repeated until we reach the ending box (4,4) or the stack is empty.

12. if we reach the [4][4] index and it is not visited then it means there is no path from S to E and we will print "no path found"

13. if we have the path now print the parrent array to check our path . we will basically map the parent array on the label 
array we are provided.

14. backtracking the parent array will be in this way such that each index of parent have the indices of the 
previous box in the path 

15. we will keep backtracking until we reach the starting box (0,0) 
and we will push each box in the path onto another stack to reverse the order and then print the path from S to E.


STACK ONLY SOLUTION WITH FUNCTIONS
-------------------------------
1. We will create a function findPathS that takes the grid as input and implements the above logic using stack.
2. We will create a function printParent that takes the parent array as input and prints it in a readable format.
3. We will create a function printPathStack that takes the parent array as input and prints the path from S to E using the stack.

QUEUE ONLY SOLUTION WITHOUT FUNCTIONS
-------------------------------
1. We will represent the grid as a 2D array where -1 represents a blocked box and 0 represents a white box.

2. Making a queue of size 25 beacuse the grid is 5x5 and in worst case we will have to visit all the boxes.

3. To keep track of the visited boxes we will use a visited 2D array of the same size as the grid and initialize it with false.

4. Then to find the path we will keep track of the previous box for each box in a parent 2D array of the same size as the grid and initialize it with (-1,-1) to indicate that there is no parent.

5. We will start from the starting box (0,0) and enqueue it onto the queue and mark it as visited.

6. to check all the neighbors of the current box we will use two arrays dr and dc to represent the change in row and column for the 8 possible moves (up, down, left, right and diagonals).

7. now dequeue the (0,0) and check all the neghbours of it and if any neighbour is invalid (that is out of bounds, blocked or already visited) we will ignore and continue 

8. we will keep track of each valid neighbour in the nr and nc variables and check each neghbour one by one

9. if the neighbour is valid we will mark it as visited

10. then we will set the parent of the neighbour to the current box this way we will keep track of the path

11. we will enqueue this neighbour on the queue and then for this index again all the steps will be repeated until we reach the ending box (4,4) or the queue is empty.

12. if we reach the [4][4] index and it is not visited then it means there is no path from S to E and we will print "no path found"

13. if we have the path now print the parrent array to check our path . we will basically map the parent array on the label array we are provided.

14. backtracking the parent array will be in this way such that each index of parent have the indices of the previous box in the path 

15. we will keep backtracking until we reach the starting box (0,0) and we will enqueue each box in the path onto another queue to reverse the order and then print the path from S to E.


QUEUE ONLY SOLUTION WITH FUNCTIONS
-------------------------------
1. We will create a function findPathQ that takes the grid as input and implements the above logic using queue.
2. We will create a function printParent that takes the parent array as input and prints it in a readable format.
3. We will create a function printPathQueue that takes the parent array as input and prints the path from S to E using the queue.


##############################################################################################

--- DIAGRAM TO SHOW THE STACK OPERATIONS (DFS - goes deep first)

Grid:              Stack State:
S  1  2  3  4      
5  X  X  8  X      push S{0,0}
X  11 12 13 14     stack: [S]
15 X  X  X  X      
20 21 22 23 E      pop S → push neighbors → stack: [5, 1]  ← 1 on top (LIFO)
                   pop 1 → push 2         → stack: [5, 2]  ← goes RIGHT
                   pop 2 → push 3,8       → stack: [5, 3, 8] ← 8 on top
                   pop 8 → push 13,12,14  → stack: [5, 3, 13, 12, 14] ← 14 on top
                   pop 14 → dead end      → stack: [5, 3, 13, 12]
                   pop 12 → push 11       → stack: [5, 3, 13, 11]
                   pop 11 → push 15       → stack: [5, 3, 13, 15]
                   pop 15 → push 20,21    → stack: [5, 3, 13, 20, 21]
                   pop 21 → push 22       → stack: [5, 3, 13, 20, 22]
                   pop 22 → push 23       → stack: [5, 3, 13, 20, 23]
                   pop 23 → push E        → FOUND!

KEY: Stack always pops the LAST pushed item (LIFO)
     So it goes DEEP into one branch before trying others
     This is why it found: S->1->2->8->12->11->15->21->22->23->E
     (a longer path, went deep into one direction)

--- DIAGRAM TO SHOW THE QUEUE OPERATIONS (BFS - explores level by level)

Grid:              Queue State:
S  1  2  3  4      
5  X  X  8  X      enqueue S{0,0}
X  11 12 13 14     queue: [S]
15 X  X  X  X      
20 21 22 23 E      dequeue S  → enqueue 5,1    → queue: [5, 1]      ← 5 at front
                   dequeue 5  → enqueue 11      → queue: [1, 11]     ← explores 5 first
                   dequeue 1  → enqueue 2       → queue: [11, 2]
                   dequeue 11 → enqueue 12,15   → queue: [2, 12, 15]
                   dequeue 2  → enqueue 3,8     → queue: [12, 15, 3, 8]
                   dequeue 12 → enqueue 13      → queue: [15, 3, 8, 13]
                   dequeue 15 → enqueue 20,21   → queue: [3, 8, 13, 20, 21]
                   dequeue 3  → enqueue 4       → queue: [8, 13, 20, 21, 4]
                   dequeue 8  → enqueue 14      → queue: [13, 20, 21, 4, 14]
                   dequeue 13 → enqueue 19(X)   → queue: [20, 21, 4, 14]
                   dequeue 20 → dead end        → queue: [21, 4, 14]
                   dequeue 21 → enqueue 22      → queue: [4, 14, 22]
                   dequeue 4  → dead end        → queue: [14, 22]
                   dequeue 14 → dead end        → queue: [22]
                   dequeue 22 → enqueue 23      → queue: [23]
                   dequeue 23 → enqueue E       → FOUND!

KEY: Queue always dequeues the FIRST enqueued item (FIFO)
     So it explores ALL neighbors at current level before going deeper
     This is why it found: S->5->11->15->21->22->23->E
     (explores wider, finds a different path)

--- KEY DIFFERENCE BETWEEN STACK AND QUEUE ---

STACK (DFS):                    QUEUE (BFS):
- LIFO: last in first out       - FIFO: first in first out
- goes DEEP into one path       - explores ALL paths level by level
- may find longer path          - always finds SHORTEST path
- like going into a maze and    - like ripples in water expanding
  following one wall             outward in all directions
- path: S->1->2->8->12->        - path: S->5->11->15->21->22->23->E
        11->15->21->22->23->E    (shorter, 7 steps vs 10 steps)

*/
class Box{
    public:
        int row , col;
        Box() : row(0) , col(0) {}
        Box(int row , int col){
            this->row = row;
            this->col = col;
        }
        friend ostream& operator<<(ostream& out, const Box& b){
            out << "(" << b.row << "," << b.col << ")";
            return out;
        }
};

void findPathQ(int grid[5][5]);
void findPathS(int grid[5][5]);
void printPathStack(Box parent[5][5]);
void printPathQueue(Box parent[5][5]);
void printParent(Box parent[5][5]);

int main(){
    int grid[5][5] = {
        {0, 1, 1, 1, 1},
        {1, -1, -1, 1, -1},
        {-1, 1, 1, 1, 1},
        {1, -1, -1, -1, -1},
        {1, 1, 1, 1, 0}
    };
    cout << "Path using Stack: " << endl;
    findPathS(grid);
    cout << "\n\nPath using Queue: " << endl;
    findPathQ(grid);
    return 0;
}

void findPathS(int grid[5][5]){
    MyStack<Box> s(25);
    int visited[5][5] = {0};
    Box parent[5][5];

    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            parent[i][j] = Box(-1,-1);
        }
    }

    s.push(Box(0,0));
    visited[0][0] = true;

    int dr[] = {-1 , 1 , 0 , 0 , -1 , -1 , 1 , 1};
    int dc[] = {0 , 0 , -1 , 1 , -1 , 1 , -1 , 1};

    while(!s.isEmpty() && !visited[4][4]){
       Box current ;
       s.pop(current); 

       for (int i = 0 ; i < 8 ; i++){
           int nr = current.row + dr[i];
           int nc = current.col + dc[i];

           if(nr >= 0 && nr < 5 && nc >= 0 && nc < 5 && !visited[nr][nc] && grid[nr][nc] != -1){
               visited[nr][nc] = true;
               parent[nr][nc] = current;
               s.push(Box(nr,nc));
           }
       }
    }
    if(!visited[4][4]){
        cout << "no path found";
        return;
    }
    printParent(parent);
    printPathStack(parent);
}

void findPathQ(int grid[5][5]){
    MyQueue<Box> q(25);
    int visited[5][5] = {0};
    Box parent[5][5];

    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            parent[i][j] = Box(-1,-1);
        }
    }

    visited[0][0] = true;
    q.enqueue(Box(0,0));

    int dr[] = {-1 , 1 , 0 , 0 , -1 , -1 , 1 , 1};
    int dc[] = {0 , 0 , -1 , 1 , -1 , 1 , -1 , 1};


    while(!visited[4][4] && !q.isEmpty()){
        Box current = q.dequeue();
        for (int i = 0 ; i < 8 ; i++){
            int nr = current.row + dr[i];                 
            int nc = current.col + dc[i];

            if(nr >= 0 && nr < 5 && nc >= 0 && nc < 5
                    && grid[nr][nc] != -1 && !visited[nr][nc]){
                visited[nr][nc] = true;
                parent[nr][nc] = current;
                q.enqueue(Box(nr, nc));
            }
        }
    }

    if(!visited[4][4]){
        cout << "no path found" << endl;
        return;
    }

    printParent(parent);
    printPathQueue(parent);
}

void printParent(Box parent[5][5]){
    cout << "Parent array \n";
    for(int i = 0; i < 5; i++){ 
        for(int j = 0; j < 5; j++){
            if(parent[i][j].row == -1)
                cout << "(?,?) ";  
            else
                cout << parent[i][j] << " ";
        }
        cout << endl;
    }
}

void printPathStack(Box parent[5][5]){
    int label[5][5] = {
        {0,  1,  2,  3,  4},
        {5, -1, -1,  8, -1},
        {-1, 11, 12, 13, 14},
        {15, -1, -1, -1, -1},
        {20, 21, 22, 23,  0}
    };
    MyStack<Box> s(25);
    int pathIndex = 0;
    Box current = Box(4,4);
    while(current.row != -1 && current.col != -1){
        s.push(current);
        current = parent[current.row][current.col];
    }
    cout << "Path from S to E: ";
    while(!s.isEmpty()){
        Box b;
        s.pop(b);
        cout << label[b.row][b.col];
        if(!s.isEmpty()){
            cout << "->";
        }
    };
}

void printPathQueue(Box parent[5][5]){
    int label[5][5] = {
        {0,  1,  2,  3,  4},
        {5, -1, -1,  8, -1},
        {-1, 11, 12, 13, 14},
        {15, -1, -1, -1, -1},
        {20, 21, 22, 23,  0}
    };
    
    MyQueue<Box> q(25);
    int pathIndex = 0;
    Box current = Box(4,4);
    while(current.row != -1 && current.col != -1){
        q.enqueue(current);
        current = parent[current.row][current.col];
    }
    cout << "Path from S to E: ";
    while(!q.isEmpty()){
        Box b = q.dequeue();
        cout << label[b.row][b.col];
        if(!q.isEmpty()){
            cout << "->";
        }
    };
}
