//Name:		Clark Blumer
//Pawprint:	cjbq4f
//Lab:		Lab 3
//Date:		6-16-2014
//LabCode:	FUN LAB


#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

// Definitions
#define INIT_SIZE 8
#define MULTIPLER 2

typedef struct Array_
{
	int data;
	
}DynamicArray;

typedef struct ArrayInfo_
{
	unsigned int max_size;
	unsigned int curr_idx;
}DynamicArrayInfo;

// Global variables
DynamicArrayInfo info;

// Prototypes
void allocate(DynamicArray **v);
void destroy(DynamicArray **v);
int sort(DynamicArray *v, unsigned int size);
void populate(DynamicArray **v, unsigned int size);
void resize(DynamicArray **v);
void append(DynamicArray **v, unsigned int value);
void display(DynamicArray *v, unsigned int size);


int main(int argc, char **argv)
{
	srand(time(NULL));
	if(argc < 2)
	{
		printf("\nFailure to use program right\n");
		return(0);
	}
	
	const unsigned int size = atoi(argv[1]); //converts the number entered on command line into an actual integer
	info.max_size = INIT_SIZE;
	info.curr_idx = 0;
	DynamicArray *localPtr;
	allocate(&localPtr);
	
	populate(&localPtr, size);
		
	sort(localPtr, size);
	

	display(localPtr, size);
	
	printf("\n\nFinal Stats from info [last index: %d current max size: %d]\n", info.curr_idx, info.max_size);

	destroy(&localPtr);
	return(0);
}

void allocate(DynamicArray **v)
{
	//allocates enough memory for max_size number of integers for the array *v points to
	*v = malloc(sizeof(int) * info.max_size);
	if(!*v) //check to see if malloc worked
	{
		printf("\nUnable to allocate memory!\n");
		exit(1);
	}
}

void destroy(DynamicArray **v)
{
	free(*v);//frees memory at address that v points to
}

int sort(DynamicArray *v, unsigned int size)
{
	/* This function uses a selection sort to sort an array passed as pointers */
	
	int i, j, min = 0, temp = 0;

	/* SELECTION SORT USING POINTER NOTATION */
	for( i = 0; i < size - 1; ++i)
        {
                min = i;
                for(j = i + 1; j < size; ++j)
                {
                        if((v + j)->data > (v + min)->data)
                                min = j;
                }
                if(min != i)
                {
                        temp = (v + i)->data;
                        (v + i)->data = (v + min)->data;
                        (v + min)->data = temp;
                }
        } 		
	
}

void resize(DynamicArray **v)
{
	DynamicArray *tempPtr; //pointer
	info.max_size = info.max_size * MULTIPLER;
	allocate(&tempPtr);
	memcpy(tempPtr, *v, sizeof(DynamicArray) * (info.curr_idx + 1));
	destroy(v);
	*v = tempPtr;
}

void append(DynamicArray **v, unsigned int value)
{
	if(info.curr_idx >= info.max_size)
	{
		resize(v);
	}
	DynamicArray *temp = *v; //pointer to hold index
	(temp + info.curr_idx)->data = value;
	info.curr_idx++;
}

void populate(DynamicArray **v, unsigned int size)
{
	int i, res = 0;
	for(i = 0; i < size; ++i)
	{
		res = rand() % 100 + 1;
		append(v, res);
	}
}

void display(DynamicArray *v, unsigned int size)
{
	/*printf("%d\n", (v + size)->data);

	if(info.curr_idx < size)
		display(v, size);
	Couldn't get recursion to work*/ 
	int i;
	for(i = 0; i < size; ++i)
		printf("%d\n", (v + i)->data);
}
