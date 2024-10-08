// Zadatak1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define ERROR_WHILE_OPENING_FILE 1
#define BUFFER_SIZE 1024
#include <stdio.h>

int countRows(char *filename);

//triba provjera malloca
int main()
{
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
		fgets(buffer, BUFFER_SIZE, fp);
		//sscanf - za domaci rad
		++row_counter;
	}
	fclose(fp);

	return 0;
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
