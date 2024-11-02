// Zadatak2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

#define ERROR_WHILE_OPENING_FILE 1

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
position find_previous(position first, char* lname);
int erase_person(position first, char* lname);
int append_person(position head, char* specific_lname, char* fname, char* lname, int birth_year);
int prepend_person(position head, char* specific_lname, char* fname, char* lname, int birth_year);
int write_in_file(position first);
int read_from_file(char* filename);

int sort_list(position first);

int main()
{
    person head = {"","",0, NULL};
    position searchedName, previous; 

    prepend_list(&head, "Leo", "Pavlovic", 1998);
    prepend_list(&head, "Lucija", "Pavlic", 1998);
    append_list(&head, "Marko", "Bulic", 2006);
    prepend_list(&head, "Ante", "Baric", 2001);
    append_list(&head, "Mate", "Matic", 1980);
    print_list(head.next);

    /*searchedName = find_by_lname(head.next, "Pavlovic");
    printf("Trazena osoba: %s %s\n", searchedName->fname, searchedName->lname);

    previous = find_previous(head.next, "Pavlovic");
    printf("Prethodnik: %s %s\n\n", previous->fname, previous->lname);*/
    printf("\n");
    erase_person(head.next, "Pavlovic");

    append_person(&head, "Baric", "Jure", "Matkovic", 1997);
    print_list(head.next);
    printf("\n");

    prepend_person(&head, "Matkovic", "Luka", "Barisic", 2002);
    print_list(head.next);

    write_in_file(head.next);
    read_from_file("lista.txt");
    print_list(head.next);
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
    return EXIT_SUCCESS;

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

    while(temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int insert_after(position previous, position to_)
{
    to_->next = previous->next;
    previous->next = to_;
    return EXIT_SUCCESS;
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

position find_previous(position first, char* lname)
{
    position temp = first;

    while(temp->next)
    {
        if (strcmp(temp->next->lname, lname) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int erase_person(position first, char* lname)
{
    position previous = find_previous(first, lname);
    position temp = previous->next;

    previous->next = previous->next->next;
    free(temp);
    return EXIT_SUCCESS;
}

int append_person(position head, char* specific_lname, char* fname, char* lname, int birth_year)
{
    position new_person = NULL, specific;

    new_person = create_person(fname, lname, birth_year);
    if (!new_person)
        return -1;
    
    specific = find_by_lname(head->next, specific_lname);
    new_person->next = specific->next;
    specific->next = new_person;
    return EXIT_SUCCESS;
    
}

int prepend_person(position head, char* specific_lname, char* fname, char* lname, int birth_year)
{
    position new_person = NULL, previous;

    new_person = create_person(fname, lname, birth_year);
    if (!new_person)
        return -1;

    previous = find_previous(head->next, specific_lname);
    new_person->next = previous->next;
    previous->next = new_person;
    return EXIT_SUCCESS;
}

int write_in_file(position first)
{
    FILE* fp = NULL;
    position temp = first;

    fp = fopen("lista.txt", "w");
    
    if (fp == NULL)
    {
        printf("Error while opening file!");
        return ERROR_WHILE_OPENING_FILE;
    }
        

    while (temp)
    {
        fprintf(fp, "First name: %s\nLast name: %s\nBirth year: %d\n\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int read_from_file(char* filename)
{
    FILE* fp = NULL;
    person new_head = { "","",0, NULL };
    char* buffer = "", current_fname, current_lname;
    int current_birth_year;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error while opening file!");
        return ERROR_WHILE_OPENING_FILE;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s", buffer);
        sscanf(buffer, "%s %s %d", current_fname, current_lname, &current_birth_year);
        append_list(&new_head, current_fname, current_lname, current_birth_year);
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
