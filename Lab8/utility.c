//Name:			Clark Blumer
//PawPrint:		cjbq4f
//Date:			7-21-2014
//Assignment:	Lab8 - A
//LabCode:		Last Lab

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utility.h"

#define MAX_SPLIT_SIZE 50

//tokenizer function takes in a string pointer and specified delimiters for strtok() 
StringArray* tokenizer (char *string, const char* delimiters)
{	
	//allocates space for the structure and the strings field 
	//inside the structure
	StringArray *sr = malloc(sizeof(StringArray));
	sr->strings = malloc(MAX_SPLIT_SIZE * sizeof(char*));
	
	char* hold;//character array to hold the tokens
	
	//allocate specific space for strings[0]
	sr->strings[0] = malloc(MAX_BUFF_SIZE * sizeof(char));
	//hold gets the tokens from the passed in string
	hold = strtok(string, delimiters);
	//copy the token into strings[0]
	strcpy(sr->strings[0], hold);
	int i;
	for(i = 1; i < MAX_SPLIT_SIZE; ++i)
	{
		hold = strtok(NULL, delimiters);
		if(hold == NULL)
		{	//if hold is NULL, size is determined
			//based on the amount of times the for loop ran
			sr->size = i;
			break;
		}
		//if hold is not NULL, allocate space for strings[i]
		sr->strings[i] = malloc(MAX_BUFF_SIZE * sizeof(char));
		//copy hold's token string into strings[i]
		strcpy(sr->strings[i], hold);
	}
	return sr;
}

void free_string_array(StringArray *sr) 
{
	int i;
	for(i = 0; i < sr->size; ++i)
	{
		free(sr->strings[i]);
	}
	free(sr->strings);
	free(sr);
}
