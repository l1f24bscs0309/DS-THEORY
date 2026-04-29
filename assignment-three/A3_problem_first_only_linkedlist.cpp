#include "MySortedFirstOnlyCircularLinkedList.h"
using namespace std;

// FIRST ONLY CIRCULAR LINKED LIST GLOBAL FUNCTIONS

void copy(MySortedFirstOnlyCircularLinkedList &source,
          MySortedFirstOnlyCircularLinkedList &destination)
{
    MySortedFirstOnlyCircularLinkedList temp;

    while (!source.isEmpty())
    {
        int value = source.removeFromFirst();
        destination.insertSorted(value);
        temp.insertSorted(value);
    }

    while (!temp.isEmpty())
    {
        source.insertSorted(temp.removeFromFirst());
    }
}

bool compare(MySortedFirstOnlyCircularLinkedList &A,
             MySortedFirstOnlyCircularLinkedList &B)
{
    MySortedFirstOnlyCircularLinkedList tempA, tempB;
    bool equal = true;

    while (!A.isEmpty() && !B.isEmpty())
    {
        int a = A.removeFromFirst();
        int b = B.removeFromFirst();

        tempA.insertSorted(a);
        tempB.insertSorted(b);

        if (a != b)
            equal = false;
    }

    if (!A.isEmpty() || !B.isEmpty())
        equal = false;

    while (!tempA.isEmpty())
        A.insertSorted(tempA.removeFromFirst());

    while (!tempB.isEmpty())
        B.insertSorted(tempB.removeFromFirst());

    return equal;
}

void deleteValues(MySortedFirstOnlyCircularLinkedList &values,
                  const int &noOfValues,
                  const int &index)
{
    MySortedFirstOnlyCircularLinkedList temp;
    int currentIndex = 0;

    while (!values.isEmpty())
    {
        int val = values.removeFromFirst();

        if (currentIndex < index || currentIndex >= index + noOfValues)
        {
            temp.insertSorted(val);
        }

        currentIndex++;
    }

    while (!temp.isEmpty())
    {
        values.insertSorted(temp.removeFromFirst());
    }
}

void insert(MySortedFirstOnlyCircularLinkedList &source,
            MySortedFirstOnlyCircularLinkedList &destination,
            const int &index)
{
    MySortedFirstOnlyCircularLinkedList temp;
    int currentIndex = 0;

    while (!destination.isEmpty())
    {
        if (currentIndex == index)
        {
            MySortedFirstOnlyCircularLinkedList restore;

            while (!source.isEmpty())
            {
                int val = source.removeFromFirst();
                temp.insertSorted(val);
                restore.insertSorted(val);
            }

            while (!restore.isEmpty())
                source.insertSorted(restore.removeFromFirst());
        }

        temp.insertSorted(destination.removeFromFirst());
        currentIndex++;
    }

    while (!temp.isEmpty())
        destination.insertSorted(temp.removeFromFirst());
}

MySortedFirstOnlyCircularLinkedList* frequency(
    MySortedFirstOnlyCircularLinkedList &source)
{
    MySortedFirstOnlyCircularLinkedList *freq =
        new MySortedFirstOnlyCircularLinkedList();

    MySortedFirstOnlyCircularLinkedList temp;

    while (!source.isEmpty())
    {
        int current = source.removeFromFirst();
        int count = 1;

        while (source.search(current))
        {
            source.deleteValue(current);
            count++;
        }

        freq->insertSorted(current);
        freq->insertSorted(count);

        for (int i = 0; i < count; i++)
            temp.insertSorted(current);
    }

    while (!temp.isEmpty())
        source.insertSorted(temp.removeFromFirst());

    return freq;
}

int main () {
    MySortedFirstOnlyCircularLinkedList list1, list2;

    list1.insertSorted(5);
    list1.insertSorted(3);
    list1.insertSorted(8);
    list1.insertSorted(5);
    list1.insertSorted(2);

    cout << "List 1: ";
    list1.display();

    MySortedFirstOnlyCircularLinkedList *freq = frequency(list1);

    cout << "Frequency List: ";
    freq->display();

    delete freq;

    return 0;
}
