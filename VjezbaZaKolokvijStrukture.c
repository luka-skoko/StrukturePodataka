// VjezbaZaKolokvijStrukture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

#define FUNCTION_FAIL 1

typedef struct _node* position;

typedef struct _node
{
    int value;
    position previous;
    position next;
}node;

position CreateElement(position head, int value);
int PrependElement(position head, int value);
int AppendElement(position head, int value);
position FindElement(position head, int value);
position FindPrevious(position head, int value);
int EraseElement(position head, int value);
int InsertElementAfter(position head, int valueA, int valueB);
int InsertElementBefore(position head, int valueA, int valueB);
int EraseAll(position head);
int PrintElements(position head);
int EraseMinimal(position head);
int MoveElementToEnd(position head, int value);
int MoveElementToStart(position head, int value);

int main()
{
    node head;
    head.next = NULL; 
    head.previous = NULL;
    PrependElement(&head, 7);
    PrependElement(&head, 9);
    PrependElement(&head, 3);
    AppendElement(&head, 5);
    AppendElement(&head, 2);
    AppendElement(&head, 1);
    PrintElements(&head);

    /*position wantedElement = FindElement(&head, 5);
    printf("\nTrazeni element je: %d", wantedElement->value);
    position previousElement = FindPrevious(&head, 5);
    printf("\nPrethodni element trazenog elementa je je: %d", previousElement->value);*/

    EraseElement(&head, 3);
    EraseElement(&head, 5);
    EraseElement(&head, 6);
    PrintElements(&head);

    InsertElementAfter(&head, 10, 2);
    InsertElementBefore(&head, 0, 10);
    PrintElements(&head);

    EraseMinimal(&head);
    PrintElements(&head);

    MoveElementToEnd(&head, 2);
    PrintElements(&head);

    MoveElementToStart(&head, 10);
    PrintElements(&head);
}

position CreateElement(position head, int value)
{
    position newElement = NULL;
    newElement = (position)malloc(sizeof(node));

    if (!newElement)
    {
        printf("Malloc failed in function!");
        return NULL;
    }

    newElement->value = value;
    newElement->previous = NULL;
    newElement->next = NULL;

    return newElement;
}

int PrependElement(position head, int value)
{
    position newElement = NULL;
    newElement = CreateElement(head, value);

    if (!newElement)
        return FUNCTION_FAIL;

    newElement->next = head->next;
    head->next = newElement;
    newElement->previous = head;

    return EXIT_SUCCESS;
}

int AppendElement(position head, int value)
{
    position newElement = NULL, temp = head;
    newElement = CreateElement(head, value);

    if (!newElement)
        return FUNCTION_FAIL;

    while (temp->next)
    {
        temp = temp->next;
    }

    newElement->next = temp->next;
    temp->next = newElement;
    newElement->previous = temp;

    return EXIT_SUCCESS;
}

position FindElement(position head, int value)
{
    position temp = head->next;

    while (temp)
    {
        if (temp->value == value)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

position FindPrevious(position head, int value)
{
    position current = FindElement(head, value);

    return current->previous;
}

int EraseElement(position head, int value)
{
    position temp = FindElement(head, value);

    if (temp == NULL)
        return 0;

    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    free(temp);
}

int InsertElementAfter(position head, int valueA, int valueB)
{
    position temp = head->next;
    position newElement = CreateElement(head, valueA);

    while (temp)
    {
        if (temp->value == valueB)
        {
            newElement->next = temp->next;
            temp->next = newElement;
            newElement->previous = temp;
            newElement->next->previous = newElement;
        }
        temp = temp->next;
    }
}

int InsertElementBefore(position head, int valueA, int valueB)
{
    position temp = head->next;
    position newElement = CreateElement(head, valueA);

    while (temp)
    {
        if (temp->value == valueB)
        {
            newElement->previous = temp->previous;
            temp->previous = newElement;
            newElement->next = temp;
            newElement->previous->next = newElement;
        }
        temp = temp->next;
    }
}

int EraseAll(position head)
{
    position temp = head->next;

    while (temp)
    {
        temp = temp->next;
        free(temp->previous);
    }
}

int PrintElements(position head)
{
    position temp = head->next;

    while (temp)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int EraseMinimal(position head)
{
    position temp = head->next;
    position minimalPosition = temp;
    int minimalValue = temp->value;
    temp = temp->next;

    while (temp)
    {
        if (temp->value < minimalValue)
        {
            minimalPosition = temp;
            minimalValue = temp->value;
        }
        temp = temp->next;
    }

    minimalPosition->previous->next = minimalPosition->next;
    minimalPosition->next->previous = minimalPosition->previous;
    free(minimalPosition);

}

int MoveElementToEnd(position head, int value)
{
    position wantedElement = FindElement(head, value);
    position last = head->next;

    while (last->next)
    {
        last = last->next;
    }

    wantedElement->next->previous = wantedElement->previous;
    wantedElement->previous->next = wantedElement->next;

    wantedElement->next = last->next;
    last->next = wantedElement;
    wantedElement->previous = last;

}

int MoveElementToStart(position head, int value)
{
    position wantedElement = FindElement(head, value);

    wantedElement->next->previous = wantedElement->previous;
    wantedElement->previous->next = wantedElement->next;

    wantedElement->next = head->next;
    head->next = wantedElement;
    wantedElement->previous = head;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
