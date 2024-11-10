// Zadatak4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024
#define ERROR_WHILE_OPENING_FILE 1

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
void PrintPolynom(position head);
int ReadFromFile(position head1, position head2, char* filename);
int ReadLine(position head, char* line);
int AddPolynoms(position P1, position P2, position result);
int MultiplyPolynoms(position P1, position P2, position result);


int main()
{
    polynom head1 = { 0, 0, NULL }, head2 = { 0, 0, NULL };
    ReadFromFile(&head1, &head2, "polinomi.txt");

    PrintPolynom(&head1);
    PrintPolynom(&head2);


    //treba osloboditi memoriju
}

position CreatePolynom(position head, int coefficient, int exponent)
{
    position newPolynom = NULL;

    newPolynom = (position)malloc(sizeof(polynom));

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
            DeleteAfter(temp);
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

int DeleteAfter(position current)
{
    position temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void PrintPolynom(position head)
{
    position temp = head;

    while (temp)
    {
        printf("%dx^%d", temp->coefficient, temp->exponent);
        if (temp->next)
            printf(" + ");
        temp = temp->next;
    }
}


int ReadFromFile(position head1, position head2, char* filename)
{
    char buffer[MAX_LINE_SIZE];
    FILE* fp = NULL;
    position newElement;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error while opening file!");
        return ERROR_WHILE_OPENING_FILE;
    }

    fgets(buffer, MAX_LINE_SIZE, fp);
    ReadLine(head1, buffer);
    fgets(buffer, MAX_LINE_SIZE, fp);
    ReadLine(head2, buffer);

    fclose(fp);
}

int ReadLine(position head, char* line)
{
    int coefficient, exponent, numberOfBytes;
    char* linePosition = line;
    position newElement;

    while (strlen(line) > 0)
    {
        sscanf(line, " %d %d%n", &coefficient, &exponent, &numberOfBytes);
        newElement = CreatePolynom(head, coefficient, exponent);
        InsertSorted(head, newElement);
        linePosition += numberOfBytes;
    }
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
