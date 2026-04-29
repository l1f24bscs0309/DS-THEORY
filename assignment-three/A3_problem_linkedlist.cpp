#include "myLinkedList.h"
using namespace std;

void copy(LinkedList &source, LinkedList &destination)
{
    myLinkedList temp;

    while (!source.isEmpty())
    {
        int value = source.removeFromFirst();
        destination.insertAtLast(value);
        temp.insertAtLast(value);
    }

    while (!temp.isEmpty())
    {
        source.insertAtLast(temp.removeFromFirst());
    }
}

bool compare(LinkedList &A, LinkedList &B)
{
    myLinkedList tempA, tempB;
    bool equal = true;

    while (!A.isEmpty() && !B.isEmpty())
    {
        int valA = A.removeFromFirst();
        int valB = B.removeFromFirst();

        tempA.insertAtLast(valA);
        tempB.insertAtLast(valB);

        if (valA != valB)
        {
            equal = false;
        }
    }

    if (!A.isEmpty() || !B.isEmpty())
    {
        equal = false;
    }

    while (!tempA.isEmpty())
    {
        A.insertAtLast(tempA.removeFromFirst());
    }

    while (!tempB.isEmpty())
    {
        B.insertAtLast(tempB.removeFromFirst());
    }

    return equal;
}

void deleteValues(LinkedList &values, const int &noOfValues, const int &index)
{
    myLinkedList temp;
    int currentIndex = 0;

    while (!values.isEmpty())
    {
        int val = values.removeFromFirst();

        if (currentIndex < index || currentIndex >= index + noOfValues)
        {
            temp.insertAtLast(val);
        }

        currentIndex++;
    }

    while (!temp.isEmpty())
    {
        values.insertAtLast(temp.removeFromFirst());
    }
}

void insert(LinkedList &source, LinkedList &destination, const int &index)
{
    myLinkedList temp;
    int currentIndex = 0;

    while (!destination.isEmpty())
    {
        if (currentIndex == index)
        {
            myLinkedList restoreSource;

            while (!source.isEmpty())
            {
                int val = source.removeFromFirst();
                temp.insertAtLast(val);
                restoreSource.insertAtLast(val);
            }

            while (!restoreSource.isEmpty())
            {
                source.insertAtLast(restoreSource.removeFromFirst());
            }
        }

        temp.insertAtLast(destination.removeFromFirst());
        currentIndex++;
    }

    if (index >= currentIndex)
    {
        myLinkedList restoreSource;

        while (!source.isEmpty())
        {
            int val = source.removeFromFirst();
            temp.insertAtLast(val);
            restoreSource.insertAtLast(val);
        }

        while (!restoreSource.isEmpty())
        {
            source.insertAtLast(restoreSource.removeFromFirst());
        }
    }

    while (!temp.isEmpty())
    {
        destination.insertAtLast(temp.removeFromFirst());
    }
}

LinkedList* frequency(LinkedList &source)
{
    myLinkedList *freqList = new myLinkedList();
    myLinkedList temp;

    while (!source.isEmpty())
    {
        int current = source.removeFromFirst();
        int count = 1;

        myLinkedList remaining;

        while (!source.isEmpty())
        {
            int val = source.removeFromFirst();

            if (val == current)
            {
                count++;
            }
            else
            {
                remaining.insertAtLast(val);
            }
        }

        freqList->insertAtLast(current);
        freqList->insertAtLast(count);

        temp.insertAtLast(current);
        for (int i = 1; i < count; i++)
        {
            temp.insertAtLast(current);
        }

        while (!remaining.isEmpty())
        {
            source.insertAtLast(remaining.removeFromFirst());
        }
    }

    while (!temp.isEmpty())
    {
        source.insertAtLast(temp.removeFromFirst());
    }

    return freqList;
}

int main (){
    myLinkedList list1, list2;

    list1.insertAtLast(1);
    list1.insertAtLast(2);
    list1.insertAtLast(3);

    copy(list1, list2);
    cout << "List 1: ";
    list1.display();
    cout << "List 2: ";
    list2.display();

    cout << "Are the lists equal? " << (compare(list1, list2) ? "Yes" : "No") << endl;

    deleteValues(list1, 2, 0);
    cout << "List 1 after deletion: ";
    list1.display();

    insert(list1, list2, 0);
    cout << "List 2 after insertion: ";
    list2.display();

    LinkedList* freqList = frequency(list2);
    cout << "Frequency List: ";
    freqList->display();

    delete freqList;
    
    return 0;
}
