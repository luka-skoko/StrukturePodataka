// Zadatak2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _person* position;
typedef struct _person
{
    char fname[32], lname[32];
    int birth_year;
    position next;

}person;

position create_person(char* fname, char* lname, int birt_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int append_list(position head, char* fname, char* lname, int birth_year);
int insert_after(position previous, position to_);
void print_list(position first);
position find_last(position head);
position find_by_lname(position first, char* lname);
//position find_previous();

int main()
{
    person head = {"","",0, NULL};
    person *searchedName;

    prepend_list(&head, "Leo", "Pavlovic", 1998);
    prepend_list(&head, "Lucija", "Pavlic", 1998);
    append_list(&head, "Marko", "Bulic", 2006);
    prepend_list(&head, "Ante", "Baric", 2001);
    append_list(&head, "Mate", "Matic", 1980);
    print_list(head.next);

    searchedName = find_by_lname(head.next, "Pavlovic");
    printf("Trazena osoba: %s %s\n", searchedName->fname, searchedName->lname);
}

position create_person(char* fname, char* lname, int birth_year)
{
    position new_person = NULL;

    new_person = (position*)malloc(sizeof(person));
    if (!new_person)
    {
        printf("Malloc failed in function create_person!");
        return NULL;
    }

    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int birth_year)
{
    position new_person = NULL;

    new_person = create_person(fname, lname, birth_year);
    if (!new_person)
        return -1;

    new_person->next = head->next;
    head->next = new_person;

    return EXIT_SUCCESS;

}

int append_list(position head, char* fname, char* lname, int birth_year)
{
    position new_person = NULL, last = NULL;
    
    new_person = create_person(fname, lname, birth_year);
    if (!new_person)
        return -1;

    last = find_last(head);
    //new_person = last->next;
    //last->next = new_person;
    insert_after(last, new_person);

}

void print_list(position first)
{
    position temp = first;

    while(temp)
    {
        printf("First name: %s\nLast name: %s\nBirth year: %d\n\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
}

position find_last(position head)
{
    position temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int insert_after(position previous, position to_)
{
    to_->next = previous->next;
    previous->next = to_;
}

position find_by_lname(position first, char* lname)
{
    position temp = first;

    while (temp)
    {
        if (strcmp(temp->lname, lname) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
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
