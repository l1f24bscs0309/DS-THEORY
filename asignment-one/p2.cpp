// SPRING 2026 DATA STRUCTURES SECTION D11 ASSIGNMENT ONE
// Name of Student: MUHAMMAD IKRAM UL HAQ
// Registration of Student: L1F24BSCS0309

#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
#include <string>
using namespace std;

/*
PROBLEM DESCRIPTION:

Read An English Sentence (ends with a full stop) from a User. First Display the count of characters and words
on screen. Next copy the Sentence in word-reverse and display on screen. A word-reverse sentence has words
in the sentence in reverse order while keeping the full stop at the end. Now calculate frequencies of each word
and display. First do the problem using Stack only and then using Queue Only in the same main.
SOLUTION:

Stack only solution without functions
-------------------------------------

1. read the sentence word by word and push each word onto the stack until we encounter a full stop. 
2. when we encounter a full stop, we stop reading and push the last word (if it ends with a full stop) onto the stack.

i
--
think
--
this
--
is
--
the
--
best.

stack currentIndex = 5 

3. To count the number of words and character , first u make a copy of the stack and two variables for holding the count of words and 
characters then u start popping it untill it is empty and on each pop increase the word count 
and then loop on that word to count the number of characters and increment
them . 

4. to reverse print the senctence we make copy of the stack and pop each word and print it since stack is LIFO it will print the words in reverse order and then print a full stop at the end.

best
--
the
--
is
--
this
--
.

5. to calculate the frequency of each word we make two stacks one for holding the unique words and 
one for holding the frequency of those words then we make a copy of the original stack and start 
popping it and for each popped word we check if it is already in the unique words stack if it is 
then we increment its frequency in the frequency stack if it is not then we push it onto the unique 
words stack and push 1 onto the frequency stack since it is the first occurrence of that word.

Stack only solution with functions
-------------------------------------
Functions to use:
1. readSentence(MyStack<string> *s , istream& in)
this function will read the sentence from the user and push each word onto the stack until it encounters a full stop.

this
--
is
--
the
--
best.

2. countWordsAndChars(MyStack<string> *s)
this prints the words and chars count

3. reverse(MyStack<string> *s)
this prints the reverse of the sentence with full stop at the end.

best
--
the
--
is
--
this
--
.

4. freq(MyStack<string> *s)
this calculates the frequency of each word and prints it on the screen.


##################################################################

Queue only solution without functions
-------------------------------------
1. read the sentence word by word and enqueue each word onto the queue until we encounter a full stop.

this->is->the->best.

2. when we encounter a full stop, we stop reading and enqueue the last word (if it ends with a full stop) onto the queue.

3. To count the number of words and character , first u make a copy of the queue and two 
variables for holding the count of words and characters then u start dequeuing it untill it 
is empty and on each dequeue increase the word count and then loop on that word to count the number of characters and increment them .

4. to reverse print the senctence we make copy of the queue and dequeue each word and push it onto a stack since stack is 
LIFO it will print the words in reverse order and then print a full stop at the end.

best->the->is->this.

5. to calculate the frequency of each word we make two queues one for holding the unique words and one for holding the frequency of those 
words then we make a copy of the original queue and start deque uing it and for each dequeued word 
we check if it is already in the unique words queue if it is then we increment its frequency in the 
frequency queue if it is not then we enqueue it onto the unique words queue and enqueue 
1 onto the frequency queue since it is the first occurrence of that word.


Queue only solution with functions
-------------------------------------
Functions to use:

1. readSentnce(MyQueue<string> *q , istream &in)
this function will read the sentence from the user and enqueue each word onto the queue until it encounters a full stop.

this->is->the->best.
2. countWordsAndChars(MyQueue<string> *q)
this prints the words and chars count

3. reverse(MyQueue<string> *q)
    best->the->is->this.

4. freq(MyQueue<string> *q)
this calculates the frequency of each word and prints it on the screen.

*/

/*
------------- CHANGE IN THE COPY CONSTRUCTOR OF STACK CLASS -------------
I changed the current index from -1 to s.currentindex because if we dont it will check the isEmpty function and it will always shows the stack empty.
Stack::Stack(const Stack & s) {
    maxCapacity = s.maxCapacity;
    currentIndex = s.currentIndex;
    values = new int[maxCapacity]{0};
    for(int i = 0; i < maxCapacity; i++)
    {
        values[i] = s.values[i];
    }
}
*/

/********* GLOBAL FUNCTION PROTOTYPES *********/
const int MAX_SIZE = 100;
void readSentence(MyStack<string> *s , istream& in);
void countWordsAndChars(MyStack<string> *s);
void reverse(MyStack<string> *s);
void freq(MyStack<string> *s);

void readSentnce(MyQueue<string> *q , istream &in);
void countWordsAndChars(MyQueue<string> *q);
void reverse(MyQueue<string> *q);
void freq(MyQueue<string> *q);

/********* MAIN FUNCTION *********/
int main () {
    MyStack<string> s(MAX_SIZE);
    readSentence(&s , cin);
    countWordsAndChars(&s);
    reverse(&s);
    freq(&s);

    MyQueue<string> q(MAX_SIZE);
    readSentnce(&q , cin);
    countWordsAndChars(&q);
    reverse(&q);
    freq(&q);
     return 0;
}

/********* FUNCTION DEFINITIONS *********/

// writing this function i realized that my class is not a template class so i went back and refactored the previous files and previous questions.
void readSentence(MyStack<string> *s , istream& in) {
    string word;
    cout << "Enter your sentence: ";
    while(in >> word){
        if(word == ".") return;
        if(word.back() == '.'){
            word.pop_back();
            s->push(word);
            return;
        }
        s->push(word);
    }
}

void countWordsAndChars(MyStack<string> *s){
    MyStack<string> temp(*s);
    int characters = 0 , words = 0;

    string word;
    while(!temp.isEmpty()){
       temp.pop(word); 
       words++;
       int i = 0;
       while(word[i] != '\0'){
        characters++;
        i++;
       }
    }
    cout << "\nTotal number of words: " << words;
    cout << "\nTotal number of characters: " << characters;
    cout << endl;
}

void reverse(MyStack<string> *s){
    MyStack<string> temp(*s);
    string word;
    cout << "\nReversed sentence: ";
    while(!temp.isEmpty()){
       temp.pop(word); 
       cout << word << " ";
    }
    cout << "." << endl;
}

void freq(MyStack<string> *s){

    MyStack<string> words(MAX_SIZE);   
    MyStack<string> freq(MAX_SIZE);   
    MyStack temp(*s);

    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);
        if(word == ".") continue;

        MyStack checkWords(words);
        MyStack checkFreq(freq);
        MyStack<string> newWords(MAX_SIZE);
        MyStack<string> newFreq(MAX_SIZE);

        string w, f;
        bool found = false;

        while (!checkWords.isEmpty()) {
            checkWords.pop(w);
            checkFreq.pop(f);
            if (w == word) {
                found = true;
                int count = stoi(f) + 1;
                newWords.push(w);
                newFreq.push(to_string(count));
            } else {
                newWords.push(w);
                newFreq.push(f);
            }
        }

        if (!found) {
            newWords.push(word);
            newFreq.push("1");
        }

        words = MyStack<string>(MAX_SIZE);
        freq  = MyStack<string>(MAX_SIZE);
        MyStack tempNew(newWords);
        MyStack tempFreq(newFreq);

        MyStack<string> revWords(MAX_SIZE);
        MyStack<string> revFreq(MAX_SIZE);
        while (!tempNew.isEmpty()) {
            tempNew.pop(w);
            tempFreq.pop(f);
            revWords.push(w);
            revFreq.push(f);
        }
        words = revWords;
        freq  = revFreq;
    }

    cout << "Word Frequencies:" << endl;
    MyStack dispWords(words);
    MyStack dispFreq(freq);
    string w, f;
    while (!dispWords.isEmpty()) {
        dispWords.pop(w);
        dispFreq.pop(f);
        cout << w << " : " << f << endl;
    }
}


void readSentnce(MyQueue<string> *q , istream &in){
    string word;
    cout << "Enter your sentence: ";
    while(in >> word){
        if(word == ".") return;
        if(word.back() == '.'){
            word.pop_back();
            q->enqueue(word);
            return;
        }
        q->enqueue(word);
    }
}
void countWordsAndChars(MyQueue<string> *q){
    MyQueue<string> temp(*q);
    int characters = 0 , words = 0;

    string word;
    while(!temp.isEmpty()){
       word = temp.dequeue(); 
       words++;
       int i = 0;
       while(word[i] != '\0'){
        characters++;
        i++;
       }
    }
    cout << "\nTotal number of words: " << words;
    cout << "\nTotal number of characters: " << characters;
    cout << endl;
}

void reverse(MyQueue<string> *q){
    MyQueue<string> temp(*q);
    MyStack<string> s(MAX_SIZE);

    string word;
    while(!temp.isEmpty()){
       word = temp.dequeue(); 
       s.push(word);
    }
    cout << "\nReversed sentence: ";
    while(!s.isEmpty()){
        s.pop(word);
        cout << word << " ";
    }
    cout << "." << endl;
}

void freq(MyQueue<string> *q){
    MyQueue <string> words(MAX_SIZE);   
    MyQueue <string> freq(MAX_SIZE);   
    MyQueue temp(*q);

    string word;
    while (!temp.isEmpty()) {
        word = temp.dequeue();
        if(word == ".") continue;

        MyQueue checkWords(words);
        MyQueue checkFreq(freq);
        MyQueue <string> newWords(MAX_SIZE);
        MyQueue <string> newFreq(MAX_SIZE);

        string w, f;
        bool found = false;

        while (!checkWords.isEmpty()) {
            w = checkWords.dequeue();
            f = checkFreq.dequeue();
            if (w == word) {
                found = true;
                int count = stoi(f) + 1;
                newWords.enqueue(w);
                newFreq.enqueue(to_string(count));
            } else {
                newWords.enqueue(w);
                newFreq.enqueue(f);
            }
        }

        if (!found) {
            newWords.enqueue(word);
            newFreq.enqueue("1");
        }

        words = MyQueue<string>(MAX_SIZE);
        freq  = MyQueue<string>(MAX_SIZE);
        MyQueue tempNew(newWords);
        MyQueue tempFreq(newFreq);

        MyQueue<string> revWords(MAX_SIZE);
        MyQueue<string> revFreq(MAX_SIZE);
        while (!tempNew.isEmpty()) {
            w = tempNew.dequeue();
            f = tempFreq.dequeue();
            revWords.enqueue(w);
            revFreq.enqueue(f);
        }
        // i know there is an error here since it is making a shallow copy and and this can be done by making the assignment 
        // operator in the queue class i have done it in my code but i have not added it here since we were explicitly told not to change the class.
        words = revWords;
        freq  = revFreq;
    }

    cout << "Word Frequencies:" << endl;
    MyQueue dispWords(words);
    MyQueue dispFreq(freq);
    string w, f;
    while (!dispWords.isEmpty()) {
        w = dispWords.dequeue();
        f = dispFreq.dequeue();
        cout << w << " : " << f << endl;
    }
}
