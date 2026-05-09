// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FOUR
// Name of Student: Muhammad Ikram ul haq
// Registration of Student: L1F24BSCS0309

#include <iostream>
using namespace std;

bool isPrime(int n);
void stats(int a[], int size, float & average, int & maximum, int & minimum);
void copy(int src[], int dst[], int size);
void removeDuplicates(int * & a, int & size);
int * frequencies(int a[], int size, int & noOfFrequencies);
void insert(int a[], int size, int value, int pos); // insert value at the given pos(ition) by shifting right
void deleteValue(int a[], int size, int pos);

int main () {
    cout << "================ Testing isPrime Function ================\n";
    int testNum = 37;
    if(isPrime(testNum))
        cout << testNum << " is a prime number \n";
    else
        cout << testNum << " is not a prime number \n";

    cout << "\n================ Testing stats Function ================\n";
    int arr[] = {1, 2, 3, 4, 5};
    float average;
    int maximum, minimum;
    stats(arr, 5, average, maximum, minimum);
    cout << "Average: " << average << "\n";
    cout << "Maximum: " << maximum << "\n";
    cout << "Minimum: " << minimum << "\n";

    cout << "\n================ Testing copy Function ================\n";
    int src[] = {10, 20, 30, 40, 50};
    int dst[5];
    copy(src, dst, 5);
    cout << "Copied array: ";
    for (int i = 0; i < 5; i++) {
        cout << dst[i] << " ";
    }
    cout << "\n";

    cout << "\n================ Testing removeDuplicates Function ================\n";
    int size = 7;
    int *arrWithDuplicates = new int[size]{1, 2, 2, 3, 4, 4, 5};

    cout << "Before removeDuplicates: ";
    for (int i = 0; i < size; i++) {
        cout << arrWithDuplicates[i] << " ";
    }
    cout << "\n";

    removeDuplicates(arrWithDuplicates, size);
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < size; i++) {
        cout << arrWithDuplicates[i] << " ";
    }
    cout << "\n";

    delete[] arrWithDuplicates;

    cout << "\n================ Testing frequencies Function ================\n";
    int arrForFreq[] = {1, 2, 2, 3, 3, 3, 4};
    int noOfFrequencies;
    int* freq = frequencies(arrForFreq, 7, noOfFrequencies);
    cout << "Frequencies of unique elements: ";
    for (int i = 0; i < noOfFrequencies; i++) {
        cout << freq[i] << " ";
    }
    cout << "\n";

   cout << "\n================ Testing insert Function ================\n"; 
    int arrForInsert[6] = {1, 2, 3, 4, 5}; // size is 6 to accommodate the new element
    int valueToInsert = 10;
    int positionToInsert = 2; // inserting at index 2 (3rd position)
    insert(arrForInsert, 6, valueToInsert, positionToInsert);
    cout << "Array after insertion: ";
    for (int i = 0; i < 6; i++) {
        cout << arrForInsert[i] << " ";
    }
    cout << "\n";

    cout << "\n================ Testing deletevalue Function ================\n";
    int positionToDelete = 2; // deleting the element at index 2 (which is now 10 after insertion)
    deleteValue(arrForInsert, 6, positionToDelete);
    cout << "Array after deletion: ";
    for (int i = 0; i < 5; i++) { // size is now 5 after deletion
        cout << arrForInsert[i] << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
 * - Purpose: Checks whether n is prime using recursive divisor testing.
 * - Base case: n <= 1 -> false, n == 2 -> true, or i*i > n -> true.
 * - Recursive case: If n is not divisible by i, increment i and recurse on n
 *   until a divisor is found or the square-root limit is crossed.
 */
bool isPrime(int n){
    if (n <= 1) return false;
    if (n == 2) return true;

    static int i = 2;

    if (n % i == 0){
        i = 2;
        return false;
    }

    if (i*i > n){
        i = 2;
        return true;
    }
    i++;
    return isPrime(n);
}

/*
 * - Purpose: Computes average, maximum, and minimum of array elements.
 * - Base case: When index reaches size, compute average and reset static state.
 * - Recursive case: Process a[index], update sum/max/min, increment index, and
 *   recurse until all elements are handled.
 */

void stats(int a[], int size, float & average, int & maximum, int & minimum){
    static int index = 0;
    static int sum = 0;

    if (index == size){
        average = float(sum) / size;
        sum = 0;
        index = 0;
        return;
    }

    if(index == 0){
        maximum = a[0];
        minimum = a[0];
    }

    sum += a[index];
    if(a[index] > maximum){
        maximum = a[index];
    }

    if(a[index] < maximum){
        minimum = a[index];
    }

    index++;

    stats(a, size, average, maximum, minimum);
}

/*
 * - Purpose: Copies source array into destination recursively.
 * - Base case: If size is 0, nothing remains to copy.
 * - Recursive case: Copy element at size-1, then recurse with size-1 to copy
 *   the remaining prefix of the array.
 */
void copy(int src[], int dst[], int size){
    if (size == 0) return;

    dst[size-1] = src[size-1];
    copy(src, dst, size-1);
}


/*
 * - Purpose: Removes duplicate values in-place from the array.
 * - Base case: Stop when size <= 1 or when i reaches the last compare position.
 * - Recursive case: Compare a[i] and a[j]; if equal, shift left and reduce size;
 *   otherwise advance j, and when j ends move to next i and recurse again.
 */
void removeDuplicates(int * & a, int & size){
    static int i = 0, j = 1;

    if (size <= 1 || i >= size - 1){
        i = 0;
        j = 1;
        return;
    }

    if (j >= size){
        i++;
        j = i + 1;
        return removeDuplicates(a, size);
    }

    if (a[i] == a[j]){
        for (int k = j; k < size - 1; k++){
            a[k] = a[k + 1];
        }
        size--;
        return removeDuplicates(a, size);
    }

    j++;
    removeDuplicates(a, size);
}

// THESE ARE HELPER FUNCTIONS FOR THE FREQUENCIES FUNCTION
/*
 * - Helper for buildFrequencies.
 * - Purpose: Checks whether value already appeared before currentIndex.
 * - Base case: If checkIndex reaches currentIndex, value was not seen before.
 * - Recursive case: Compare current slot; if unmatched, recurse with checkIndex+1.
 */
bool alreadySeen(int a[] , int currentIndex , int value , int checkIndex = 0){
    if(checkIndex >= currentIndex) return false;
    if(a[checkIndex] == value) return true;

    return alreadySeen(a , currentIndex , value , checkIndex+1);
}

/*
 * - Helper for buildFrequencies.
 * - Purpose: Counts total occurrences of value in the full array.
 * - Base case: If index reaches size, return 0.
 * - Recursive case: Add 1 when a[index] matches value, then recurse at index+1
 *   and accumulate the count from the remaining elements.
 */
int countOccurrneces(int a[], int size, int value, int index = 0){
    if (index >= size) return 0;

    if(a[index] == value) 
        return 1 + countOccurrneces(a , size , value , index+1);
    else
        return countOccurrneces(a , size , value , index+1);
}

/*
 * - Helper for frequencies.
 * - Purpose: Builds freq[] for unique values only.
 * - Base case: If index reaches size, building is complete.
 * - Recursive case: For each value, if unseen before, compute its occurrence
 *   count, store it, increment unique counter, then recurse to next index.
 */
void buildFrequencies(int a[] , int size , int freq[] , int &count , int index = 0){
    if (index >= size) return;

    if(!alreadySeen(a, index, a[index])){
        freq[count] = countOccurrneces(a , size , a[index]);
        count++;
    }
    buildFrequencies(a , size , freq , count , index + 1);
}

/*
 * - Purpose: Allocates frequency array and starts recursive build.
 * - Base/recursive flow: Recursion is handled by buildFrequencies; this
 *   function initializes noOfFrequencies and returns the filled array.
 */

int * frequencies(int a[], int size, int & noOfFrequencies){
    int* freq = new int[size];
    noOfFrequencies = 0;
    buildFrequencies(a , size ,freq , noOfFrequencies);
    return freq;
}

/*
 * - Purpose: Inserts value at pos by shifting elements right recursively.
 * - Base case: When size <= pos, place value at a[pos].
 * - Recursive case: Move a[size-1] to a[size], then recurse with size-1
 *   until the insertion position is reached.
 */
void insert(int a[], int size, int value, int pos){
    if (size <= pos){
        a[pos] = value;
        return;
    }

    a[size] = a[size - 1];
    insert(a, size - 1, value, pos);
}

/*
 * - Purpose: Deletes value at pos by shifting following elements left.
 * - Base case: If pos reaches size-1, shifting is complete.
 * - Recursive case: Copy a[pos+1] into a[pos], then recurse with pos+1 to
 *   keep left-shifting until the end.
 */

void deleteValue(int a[], int size, int pos){
    if (pos >= size - 1)
        return;

    a[pos] = a[pos + 1];
    deleteValue(a, size, pos + 1);
}
