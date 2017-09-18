//Name:		Clark Blumer 
//Date:		6-11-2014
//Assignment:	Pre-Lab 3
//

// Libraries
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

// Definitions
#define INIT_SIZE 8

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

int main()
{
	srand(time(NULL));
	info.max_size = INIT_SIZE;
	info.curr_idx = 0;
	DynamicArray *localPtr;
	allocate(&localPtr);

	//Fills localPtr array with random values and keeps track of curr_idx
	int i;
	for(i = 0; i < info.max_size; ++i)
	{
		localPtr[i].data = (rand() % 100) + 1; //random values between 0 - 99, +1 to make values 1 - 100
		info.curr_idx++;
//		sort(localPtr, info.max_size);
	}
	sort(localPtr, info.max_size);
	// Print test of the randomly filled localPtr array
	int j;
	for(j = 0; j < info.max_size; ++j)
		printf("%d ", localPtr[j].data);
	


	printf("\n\nFinal Stats from info [last index: %d current max size: %d]\n", info.curr_idx, info.max_size);

	destroy(&localPtr);
	return(0);
}

void allocate(DynamicArray **v)
{
	//allocates enough memory for 8 integers for the array *v points to
	*v = malloc(sizeof(info.max_size) * info.max_size);
}

void destroy(DynamicArray **v)
{
	free(*v);//frees memory at address that v points to (localPtr in main)
}

int sort(DynamicArray *v, unsigned int size)
{
	/* This function uses a selection sort to sort an array passed as pointers */
	
	int i, j, min = 0, temp = 0;

	/* THIS WORKS DO NOT DELETE THIS BLOCK - ARRAY NOTATION
	for( i = 0; i < size - 1; ++i)
	{
		min = i;
		for(j = i + 1; j < size; ++j)
		{
			if(v[j].data < v[min].data)
				min = j;
		}
		if(min != i)
		{
			temp = v[i].data;
			v[i].data = v[min].data;
			v[min].data = temp;
		}
	} */


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





