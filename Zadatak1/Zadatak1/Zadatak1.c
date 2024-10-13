// Zadatak1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
//zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
//studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova / max_br_bodova * 100


#define _CRT_SECURE_NO_WARNINGS
#define ERROR_WHILE_OPENING_FILE 1
#define ERROR_WHILE_ALLOCATING_MEMORY 2
#define BUFFER_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
//#include "stdafx.h"

typedef struct {
	char name[50];
	char surname[50];
	int points;
} Student;



int countRows(char *filename);
void readStudentsData(char* filename, Student* students, int numberOfStudents);
int positionOfTheBestStudent(Student* students, int numberOfStudents);
void outputData(Student* students, int numberOfStudents, int positionOfMaxPoints);

//const char* inputFile = "..\\..\\Zadatak1\\data\\students.txt";
const char* inputFile = "C:\\Users\\lukas\\git\\StrukturePodataka\\Zadatak1\\Zadatak1\\data\\students.txt";


int main()
{
	Student* students = NULL;
	int numberOfStudents;
	int i;
	int positionOfMaxPoints;

	numberOfStudents = countRows(inputFile);

	students = (Student*)malloc(numberOfStudents * sizeof(Student));
	if (students == NULL) 
	{
		printf("Memory not allocated.\n");
		return ERROR_WHILE_ALLOCATING_MEMORY;
	}

	readStudentsData(inputFile, students, numberOfStudents);

	positionOfMaxPoints = positionOfTheBestStudent(students, numberOfStudents);

	outputData(students, numberOfStudents, positionOfMaxPoints);

	free(students);

	return 0;
}

int countRows(char *filename)
{
	FILE *fp = NULL;
	char buffer[BUFFER_SIZE];
	int row_counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error while opening file!\n");
		return ERROR_WHILE_OPENING_FILE;
	}

	while (!feof(fp))
	{
		char* line = fgets(buffer, BUFFER_SIZE, fp);
		if (line == NULL)
			break;
		++row_counter;
	}
	fclose(fp);

	return row_counter;
}

void readStudentsData(char* filename, Student* students, int numberOfStudents)
{
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int i;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error while opening file!\n");
		return ERROR_WHILE_OPENING_FILE;
	}

	//rewind(fp);

	for(i = 0; i < numberOfStudents; i++)
	{
		fscanf(fp, "%s %s %d", students[i].name, students[i].surname, &students[i].points);
	}
	
	fclose(fp);

	return 0;
}

int positionOfTheBestStudent(Student* students, int numberOfStudents)
{
	int positionOfMaxPoints = 0;
	int i;

	for (i = 1; i < numberOfStudents; i++)
	{
		if (students[positionOfMaxPoints].points < students[i].points)
		{
			positionOfMaxPoints = i;
		}
	}
	return positionOfMaxPoints;
}

void outputData(Student* students, int numberOfStudents, int positionOfMaxPoints)
{
	int i;

	printf("IME I PREZIME\t\t\tBODOVI\t\tRELATIVNI BODOVI\n");

	for (i = 0; i < numberOfStudents; i++)
	{
		printf("%s %s\t\t\t%d\t\t", students[i].name, students[i].surname, students[i].points);
		printf("%f\n", (float)students[i].points / students[positionOfMaxPoints].points * 100);
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
