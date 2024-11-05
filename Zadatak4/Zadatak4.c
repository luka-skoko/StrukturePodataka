// Zadatak4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

typedef struct _polynom* position;
typedef struct _polynom
{
    int coefficient;
    int exponent;
    position next;
}polynom;

position CreatePolynom(position head, int coefficient, int exponent);
int InsertSorted(position head, position newElement);
int InsertAfter(position current, position newElement);
int DeleteAfter(position current);
position FindPrevious(position first, position current);
int ReadFromFile(char* filename);
int AddPolynoms(position P1, position P2, position result);
int MultiplyPolynoms(position P1, position P2, position result);


int main()
{
    //treba osloboditi memoriju
}

position CreatePolynom(position head, int coefficient, int exponent)
{
    position newPolynom = NULL;

    newPolynom = (position*)malloc(sizeof(polynom));

    if (!newPolynom)
    {
        printf("Malloc failed in function CreatePolynom!");
        return NULL;
    }

    newPolynom->coefficient = coefficient;
    newPolynom->exponent = exponent;
    newPolynom->next = NULL;

    return newPolynom;
}

int InsertSorted(position head, position newElement)
{
    position temp = head;

    while (temp->next && temp->next->exponent < newElement->exponent)
    {
        temp = temp->next;
    }

    if (temp->next == NULL || temp->next->exponent != newElement->exponent)
    {
        InsertAfter(temp, newElement);
    }
    else
    {
        int resultCoefficient = newElement->coefficient + temp->next->coefficient;

        if (resultCoefficient == 0)
        {
            DeleteAfter(head, temp);
            free(newElement);
        }
        else
        {
            temp->next->coefficient = resultCoefficient;
            free(newElement);
        }
    }
}

int InsertAfter(position current, position newElement)
{
    newElement->next = current->next;
    current->next = newElement;

    return EXIT_SUCCESS;
}

int DeleteAfter(position head, position current)
{
    position previous = FindPrevious(head->next, current);
    position temp = previous->next;

    previous->next = previous->next->next;
    free(temp);
}

position FindPrevious(position first, position current)
{
    position temp = first;

    while (temp->next)
    {
        if (temp->next == current)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

int ReadFromFile(char* filename)
{
    char buffer[MAX_LINE_SIZE];
    FILE* fp;
    int status;
    //status treba biti 2
    int coefficient, exponent, numberOfBytes;

    fp = fopen(filename, "r");

    fgets(buffer, MAX_LINE_SIZE, fp);

    while (strlen(buffer) > 0)
    {
        status = sscanf(buffer, "%d %d %n", &coefficient, &exponent, &numberOfBytes);
    }
    buffer += numberOfBytes;
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
