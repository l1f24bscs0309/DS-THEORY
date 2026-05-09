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
 *The base case of this function is when n is less than or equal to 1, 
 *in which case it returns false, indicating that n is not a prime number. 
 *If n is equal to 2, it returns true, indicating that n is a prime number. 
 *For other values of n, the function uses a static variable i to 
 *check for divisibility starting from 2. If n is divisible by i, 
 *it resets i to 2 and returns false. If i squared is greater than n, 
 *it resets i to 2 and returns true, indicating that n is a prime number. 
 *Otherwise, it increments i and continues checking recursively.
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
 * This function calculates the average, maximum, and minimum of an array of integers.
 * It uses static variables to keep track of the current index and the sum of the elements.
 * The function recursively processes each element of the array until it reaches the end.
 * When the index reaches the size of the array, it calculates the average by dividing the sum
 * by the size, resets the sum and index for future calls, and returns.
 * During the recursive calls, it updates the maximum and minimum values based on the current element.
 * The maximum is updated if the current element is greater than the current maximum, and the minimum is updated
 * if the current element is less than the current minimum.
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
 * This function copies elements from a source array (src) to a destination array (dst) recursively.
 * It takes three parameters: the source array, the destination array, and the size of the arrays.
 * The base case of the recursion is when the size is zero, in which case the function returns without doing anything.
 * For each recursive call, it copies the last element of the source array to the corresponding position in the destination array,
 * and then calls itself with a reduced size (size - 1) to copy the remaining elements.
 */
void copy(int src[], int dst[], int size){
    if (size == 0) return;

    dst[size-1] = src[size-1];
    copy(src, dst, size-1);
}


/*
 * This function removes duplicate elements from an array of integers. 
 * It takes a reference to a pointer to the array and a reference to the size of the array as parameters.
 * The function uses static variables i and j to keep track of the current indices being compared.
 * The base case of the recursion is when the size of the array is less than or equal to 1, or when i has reached the end of the array.
 * If j has reached the end of the array, it increments i and resets j to be one position ahead of i, then calls itself recursively.
 * If a duplicate is found (i.e., a[i] == a[j]), it shifts all elements after j one position to the left, effectively removing the duplicate,
 * decrements the size of the array, and calls itself recursively without incrementing j (to check for any further duplicates at the same position).
 * If no duplicate is found, it simply increments j and continues checking for duplicates.
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

// THSE ARE HELPER FUNCTIONS FOR THE FREQUENCIES FUNCTION
/*
 * this function checks if the value passed in it already exists in the array
 * to the current index. it uses recursion to check all the elements before the current index
 * if it finds the value it returns true otherwise it returns false after checking all the elements before the current index
 */
bool alreadySeen(int a[] , int currentIndex , int value , int checkIndex = 0){
    if(checkIndex >= currentIndex) return false;
    if(a[checkIndex] == value) return true;

    return alreadySeen(a , currentIndex , value , checkIndex+1);
}

/*
 * this function counts the occurrences of a value in the array starting from the current index
 * it uses recursion to check all the elements in the array and count how many times the value appears
 * if it finds the value it adds 1 to the count and continues checking the rest of the array
 * if it doesn't find the value it just continues checking the rest of the array without adding to the count
 * when it reaches the end of the array it returns the total count of occurrences
 */
int countOccurrneces(int a[], int size, int value, int index = 0){
    if (index >= size) return 0;

    if(a[index] == value) 
        return 1 + countOccurrneces(a , size , value , index+1);
    else
        return countOccurrneces(a , size , value , index+1);
}

/*
 * this function builds the frequencies of unique elements in the array
 * it uses recursion to check each element in the array and count its occurrences
 * if the element has not been seen before (checked using alreadySeen function) it counts its occurrences and adds it to the freq array
 * it also keeps track of the count of unique elements found so far and updates it accordingly
 * when it reaches the end of the array it returns and the freq array will contain the frequencies of all unique elements in the original array
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
 * this function initializes the freq array and calls the buildFrequencies function to fill it with the frequencies of unique elements in the input array
 * it also returns the freq array and updates the noOfFrequencies variable with the count of unique elements found
 */

int * frequencies(int a[], int size, int & noOfFrequencies){
    int* freq = new int[size];
    noOfFrequencies = 0;
    buildFrequencies(a , size ,freq , noOfFrequencies);
    return freq;
}

/*
 * this function inserts a value at a specified position in the array by shifting elements to the right
 * it takes the array, its size, the value to be inserted, and the position where the value should be inserted as parameters
 * the base case of the recursion is when the size is less than or equal to the position, in which case it directly inserts the value at the specified position
 * if the size is greater than the position, it shifts the last element of the array to the right (size - 1) and then calls itself recursively with a reduced 
 * size (size - 1) to continue shifting elements until it reaches the position where the new value should be inserted
 * once the position is reached, the new value is inserted and the function returns, resulting in the array being updated 
 * with the new value at the specified position and all subsequent elements shifted to the right
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
 * this function deletes a value at a specified position in the array by shifting elements to the left
 * it takes the array, its size, and the position of the value to be deleted as parameters
 * the base case of the recursion is when the position is greater than or equal to size - 1, in which case it simply returns without doing anything
 * if the position is valid, it shifts the element at pos + 1 to pos, effectively overwriting the value at pos with the next value in the array
 * then it calls itself recursively with an incremented position (pos + 1) to continue shifting elements to the left until it reaches the end of the array
 * once it reaches the end of the array, all elements after the deleted position will have been shifted left, 
 * and the last element will be duplicated (but can be ignored since size is reduced)
 */

void deleteValue(int a[], int size, int pos){
    if (pos >= size - 1)
        return;

    a[pos] = a[pos + 1];
    deleteValue(a, size, pos + 1);
}
