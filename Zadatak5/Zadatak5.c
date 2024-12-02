// Zadatak5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ERROR -1

typedef struct _node* position;
typedef struct _node
{
    int value;
    position next;
}node;

int PushElement(position head, int element);
int PopElement(position head);
int PrintStack(position head);
int EvaluatePostfix(position head, char* postfix);

int main()
{
    position stackHead = (position)malloc(sizeof(node));
    stackHead->next = NULL;

    FILE* fp = NULL;
    fp = fopen("postfix.txt", "r");

    if (fp == NULL)
    {
        printf("Nije moguce otvoriti file!\n");
        return ERROR;
    }

    //int result = EvaluatePostfix(stackHead, fp);
    char postfix[] = "8 3 + 4 2 * +";
    int result = EvaluatePostfix(stackHead, postfix);
    printf("Rjesenje je: %d", result);

    fclose(fp);
    free(stackHead);

    return 0;
        
}

int PushElement(position head, int value)
{
    position temp = (position)malloc(sizeof(node));

    temp->value = value;
    temp->next = head->next;
    head->next = temp;

    return EXIT_SUCCESS;
}

int PopElement(position head)
{
    int valueToReturn = head->next->value;
    position temp = head->next;
    head->next = temp->next;
    free(temp);
    return(valueToReturn);
}

int PrintStack(position head)
{
    while (head->next)
    {
        printf("%d ", head->next->value);
        head = head->next;
    }
    printf("\n");

    return 0;
}

int EvaluatePostfix(position head, char* postfix)
{
    char* token = strtok(postfix, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]))
            PushElement(head, atoi(token));
        else
        {
            int b = PopElement(head);
            int a = PopElement(head);

            switch (token[0])
            {
                case '+':
                    PushElement(head, a + b);
                    break;
                case '-':
                    PushElement(head, a - b);
                    break;
                case '*':
                    PushElement(head, a * b);
                    break;
                case '/':
                    PushElement(head, a / b);
                    break;
                default: 
                    fprintf(stderr, "Invalid operator: %c\n", token[0]); 
                    return EXIT_FAILURE;
            }
            token = strtok(NULL, " ");

        }
    }

    return PopElement(head);
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
