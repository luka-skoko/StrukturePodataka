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
void LoadPolynom(position head, const char* line);
position SumPolynoms(position poly1, position poly2);
position MultiplyPolynoms(position poly1, position poly2);
void FreePolynom(position head);


int main()
{
    FILE* file = fopen("polinomi.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    
    char line1[256], line2[256];
    if (fgets(line1, sizeof(line1), file) == NULL || fgets(line2, sizeof(line2), file) == NULL) 
    {
        perror("Error reading lines");
        fclose(file);
        return 1;
    }
    
    position poly1 = (position)malloc(sizeof(polynom)); 
    poly1->next = NULL;

    position poly2 = (position)malloc(sizeof(polynom)); 
    poly2->next = NULL;
    

    LoadPolynom(poly1, line1);
    LoadPolynom(poly2, line2);
    
    fclose(file);

    printf("Polynom 1: \n");
    PrintPolynom(poly1);
    printf("Polynom 2: \n");
    PrintPolynom(poly2);

    printf("Polynoms sum: \n");
    position polySum = SumPolynoms(poly1, poly2);
    PrintPolynom(polySum);

    printf("Polynoms product: \n");
    position polyProduct = MultiplyPolynoms(poly1, poly2);
    PrintPolynom(polyProduct);


    //oslobodi memoriju
    FreePolynom(poly1);
    FreePolynom(poly2);
    FreePolynom(polySum);
    FreePolynom(polyProduct);

    return 0;
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
    printf("\n\n");
}


void LoadPolynom(position head, const char* line) 
{
    int coefficient, exponent;
    const char* ptr = line;
    position newElement = NULL;
    while (sscanf(ptr, "%d %d", &coefficient, &exponent) == 2) 
    {
        newElement = CreatePolynom(head, coefficient, exponent);
        InsertSorted(head, newElement);
        //for (int i = 0; i < 2; i++)
        {
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            while (*ptr == ' ') ptr++;
        }

    }
}

position SumPolynoms(position poly1, position poly2) 
{
    position result = (position)malloc(sizeof(polynom));
    result->next = NULL;
    position temp1 = poly1->next;
    position temp2 = poly2->next;
    position newElement = NULL;


    while (temp1 != NULL && temp2 != NULL) 
    {
        if (temp1->exponent == temp2->exponent) 
        {
            newElement = CreatePolynom(result, temp1->coefficient + temp2->coefficient, temp1->exponent);
            InsertSorted(result, newElement);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->exponent > temp2->exponent) 
        {
            newElement = CreatePolynom(result, temp1->coefficient, temp1->exponent);
            InsertSorted(result, newElement);
            temp1 = temp1->next;
        }
        else 
        {
            newElement = CreatePolynom(result, temp2->coefficient, temp2->exponent);
            InsertSorted(result, newElement);
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) 
    {
        newElement = CreatePolynom(result, temp1->coefficient, temp1->exponent);
        InsertSorted(result, newElement);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) 
    {
        newElement = CreatePolynom(result, temp2->coefficient, temp2->exponent);
        InsertSorted(result, newElement);
        temp2 = temp2->next;
    }

    return result;
}

position MultiplyPolynoms(position poly1, position poly2) 
{
    position result = (position)malloc(sizeof(polynom));
    result->next = NULL;

    for (position temp1 = poly1->next; temp1 != NULL; temp1 = temp1->next) 
    {
        for (position temp2 = poly2->next; temp2 != NULL; temp2 = temp2->next) 
        {
            int newCoefficient = temp1->coefficient * temp2->coefficient;
            int newExponent = temp1->exponent + temp2->exponent;

            position tempResult = result;
            while (tempResult->next != NULL && tempResult->next->exponent > newExponent) 
            {
                tempResult = tempResult->next;
            }

            if (tempResult->next != NULL && tempResult->next->exponent == newExponent) 
            {
                tempResult->next->coefficient += newCoefficient;
            }
            else 
            {
                position newNode = (position)malloc(sizeof(polynom));
                newNode->coefficient = newCoefficient;
                newNode->exponent = newExponent;
                newNode->next = tempResult->next;
                tempResult->next = newNode;
            }
        }
    }

    return result;
}

void FreePolynom(position head) 
{
    position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
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
