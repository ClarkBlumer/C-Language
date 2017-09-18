#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utility.h"

#define MAX_SPLIT_SIZE 50

//tokenizer function takes in a string pointer and specified delimiters for strtok() 
StringArray* tokenizer (char *string, const char* delimiters)
{
	int i;
	StringArray **stringArrayPtr = calloc(MAX_SPLIT_SIZE, sizeof(char*));//allocates the array of pointers
	StringArray *pch = NULL;//token reference, pointer to a character
	
	//Creates MAX_SPLIT_SIZE strings that are MAX_BUFF_SIZE in length
	//In this example, 50 strings that are 50 characters long.
	for(i = 0; i < MAX_SPLIT_SIZE; ++i)
	{
		stringArrayPtr[i] = calloc((MAX_BUFF_SIZE + 1), sizeof(char)); //MAX_BUFF_SIZE + 1 to account for string terminator character
		pch = strtok(stringArrayPtr[i].strings, delimiters);
		while(pch != NULL)//while the string does not point to a the null terminator
		{
			strcpy(stringArrayPtr[i]->strings, pch->strings);
			pch = strtok(NULL, delimiters);
		}
	}
	
}

void free_string_array(StringArray *sr) 
{
	int i;
	for(i = 0; i < MAX_BUFF_SIZE; ++i)
	{
		free(sr[i].strings);
	}
	free(sr);
}
