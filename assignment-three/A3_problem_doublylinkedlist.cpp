#include "DoublyLinkedList.h"
using namespace std;

// COPY
void copy(DoublyLinkedList &source, DoublyLinkedList &destination)
{
    DoublyLinkedList temp;

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

// COMPARE
bool compare(DoublyLinkedList &A, DoublyLinkedList &B)
{
    DoublyLinkedList tempA, tempB;
    bool equal = true;

    while (!A.isEmpty() && !B.isEmpty())
    {
        int a = A.removeFromFirst();
        int b = B.removeFromFirst();

        tempA.insertAtLast(a);
        tempB.insertAtLast(b);

        if (a != b)
            equal = false;
    }

    if (!A.isEmpty() || !B.isEmpty())
        equal = false;

    while (!tempA.isEmpty())
        A.insertAtLast(tempA.removeFromFirst());

    while (!tempB.isEmpty())
        B.insertAtLast(tempB.removeFromFirst());

    return equal;
}

// DELETE VALUES FROM INDEX
void deleteValues(DoublyLinkedList &values,
                  const int &noOfValues,
                  const int &index)
{
    DoublyLinkedList temp;
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

// INSERT SOURCE INTO DESTINATION AT INDEX
void insert(DoublyLinkedList &source,
            DoublyLinkedList &destination,
            const int &index)
{
    DoublyLinkedList temp;
    int currentIndex = 0;

    while (!destination.isEmpty())
    {
        if (currentIndex == index)
        {
            DoublyLinkedList restore;

            while (!source.isEmpty())
            {
                int val = source.removeFromFirst();
                temp.insertAtLast(val);
                restore.insertAtLast(val);
            }

            while (!restore.isEmpty())
            {
                source.insertAtLast(restore.removeFromFirst());
            }
        }

        temp.insertAtLast(destination.removeFromFirst());
        currentIndex++;
    }

    // If index is at end
    if (currentIndex == index)
    {
        DoublyLinkedList restore;

        while (!source.isEmpty())
        {
            int val = source.removeFromFirst();
            temp.insertAtLast(val);
            restore.insertAtLast(val);
        }

        while (!restore.isEmpty())
        {
            source.insertAtLast(restore.removeFromFirst());
        }
    }

    while (!temp.isEmpty())
    {
        destination.insertAtLast(temp.removeFromFirst());
    }
}

// FREQUENCY FUNCTION
DoublyLinkedList* frequency(DoublyLinkedList &source)
{
    DoublyLinkedList *freq = new DoublyLinkedList();
    DoublyLinkedList temp;

    while (!source.isEmpty())
    {
        int current = source.removeFromFirst();
        int count = 1;

        DoublyLinkedList remaining;

        while (!source.isEmpty())
        {
            int val = source.removeFromFirst();

            if (val == current)
                count++;
            else
                remaining.insertAtLast(val);
        }

        freq->insertAtLast(current);
        freq->insertAtLast(count);

        for (int i = 0; i < count; i++)
            temp.insertAtLast(current);

        while (!remaining.isEmpty())
            source.insertAtLast(remaining.removeFromFirst());
    }

    while (!temp.isEmpty())
    {
        source.insertAtLast(temp.removeFromFirst());
    }

    return freq;
}

int main () {
    DoublyLinkedList list1;
    list1.insertAtLast(1);
    list1.insertAtLast(2);
    list1.insertAtLast(3);

    DoublyLinkedList list2;
    copy(list1, list2);

    cout << "List 1: ";
    list1.display();
    cout << "List 2: ";
    list2.display();

    cout << "Are the lists equal? " << (compare(list1, list2) ? "Yes" : "No") << endl;

    deleteValues(list1, 2, 0);
    cout << "List 1 after deleting values from index 0: ";
    list1.display();

    insert(list1, list2, 0);
    cout << "List 2 after inserting List 1 at index 0: ";
    list2.display();

    DoublyLinkedList *freq = frequency(list2);
    cout << "Frequency of elements in List 2: ";
    freq->display();

    delete freq; // Clean up dynamically allocated memory

    return 0;
}
