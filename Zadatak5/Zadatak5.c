// Zadatak5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _stack* position;
typedef struct _stack
{
    int value;
    position next;
}stack;

position CreateStack(position head, int value);
int PushElement(position head, int element);
int PopElement(position head);
int EvaluatePostfix(char* postfix);

int main()
{
    
}

position CreateStack(position head, int value)
{
    position newElement = NULL;

    newElement = (position)malloc(sizeof(stack));

    if (!newElement)
    {
        printf("Malloc failed in function CreateElement!");
        return NULL;
    }

    newElement->value = value;
    newElement->next = NULL;

    return newElement;
}

int PushElement(position head, int element)
{
    position temp = head->next;

    temp->value = element;
    temp->next = head->next->next;
    head->next = temp;
}

int PopElement(position head)
{
    position temp = head->next;
    head->next = temp->next;
    return(temp->value);
}

int EvaluatePostfix(char* postfix)
{
    position newStack = CreateStack()
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
