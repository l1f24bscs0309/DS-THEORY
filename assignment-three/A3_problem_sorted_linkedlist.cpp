#include "SortedLinkedList.h"

void copy(SortedLinkedList &source, SortedLinkedList &destination)
{
    SortedLinkedList temp;

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

void deleteValues(SortedLinkedList &values, const int &noOfValues, const int &index)
{
    SortedLinkedList temp;
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


bool SortedLinkedList::search(int value)
{
    if (first == nullptr && last == nullptr)
    {
        return false;
    }

    Node* t = first;

    while (t != nullptr)
    {
        if (t->data == value)
        {
            return true;
        }

        t = t->next;
    }

    return false;
}

bool compare(SortedLinkedList &A, SortedLinkedList &B)
{
    SortedLinkedList tempA, tempB;
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

SortedLinkedList* frequency(SortedLinkedList &source)
{
    SortedLinkedList *freq = new SortedLinkedList();
    SortedLinkedList temp;

    while (!source.isEmpty())
    {
        int current = source.removeFromFirst();
        int count = 1;

        while (!source.isEmpty() && source.search(current))
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

int main ()
{
    SortedLinkedList list;
    list.insertSorted(5);
    list.insertSorted(3);
    list.insertSorted(8);
    list.insertSorted(5);
    list.insertSorted(2);

    SortedLinkedList *freq = frequency(list);
    freq->display(); // Should display pairs of (value, frequency)

    delete freq; // Clean up dynamically allocated memory
    return 0;
}
