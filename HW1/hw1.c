//name:		Clark Blumer
//Pawprint:	cjbq4f
//Date:		6-17-2014
//Assignment:	Homework1


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING_LEN 25

void insert_data(char ***strings, const char *filename, int size);		//DONE
int file_line_count(const char *filename);					//DONE
void allocate(char ***strings, int size);					//DONE
void destroy(char ***strings, int size);					//DONE
void histogram(char **strings, int *hist, int size);
void sort_data(char **strings, int size);					//DONE
int find_number_of_prefixs(char **strings, int size);				//DONE
int find_number_of_suffixs(char **strings, int size);				//DONE
int binary_search(char **strings, char *target, int start_idx, int end_idx);	//DONE
void write_data(char **strings, char *filename, int size);

/*****************************************************************************/
/*                                     MAIN                                  */
/*****************************************************************************/

int main(int argc, char **argv)
{
	//Check to correct amount of command line arguments
	//Needs ./a.out count people.txt output.txt
	if(argc < 4)
	{
		printf("\nMissing arguments\n\n");
		return(0);
	}
	//Check to make sure filenames are correct
	//Needs to be people.txt and output.txt in their respective positions
	if(strcmp(argv[2], "people.txt") != 0 || strcmp(argv[3], "output.txt") != 0)
	{
		printf("\nInvalid file names! Use people.txt and output.txt\n\n");
		return(0);
	}

	//Gets size from commandline unless input is MAX_SIZE
	//Then gets size from number of lines in the people.txt file
	int size = 0;
	if(strcmp(argv[1], "MAX_SIZE") != 0)
	{
		size = atoi(argv[1]);
	}
	else 
	{
		size = file_line_count("people.txt");
	}

	/* INITIAL ERROR CHECKING DONE AND SIZE DETERMINED. BEGIN PROGRAM */

	char **localPtr = NULL;
	int hist[MAX_STRING_LEN] = {0};
	char target[MAX_STRING_LEN];
	char choice;
	allocate(&localPtr, size);
	insert_data(&localPtr, "people.txt", size);
	sort_data(localPtr, size);	
	
	/* SORTED ARRAY CHECK *//* 
	int i;
	for(i = 0; i < size; ++i)
		printf("%s \n", localPtr[i]);		
	*/

	
	/* SEARCH DATASET AND WHILE LOOP TO CONTINUE UNTIL USER ENDS */
	printf("\nSearching for: ");
	scanf("%s", &target);
	getchar();
	if((binary_search(localPtr, target, 1, size - 1)) > 0)
		printf("%s is in this dataset\n", target);
	else //if((binary_search(localPtr, target, 0, size)) > 0)
		printf("Not in the dataset!\n", target);
	printf("Continue? (y / n): ");
	scanf("%c", &choice);
	while(choice = 'y' && choice != 'n')
	{
		printf("\nSearching for: ");
        	scanf("%s", &target);
		getchar();
        	if((binary_search(localPtr, target, 1, size - 1)) > 0)
                	printf("%s is in this dataset\n", target);
        	else //if((binary_search(localPtr, target, 0, size)) > 0)
                	printf("Not in the dataset!\n", target);
        	printf("Continue? (y / n): ");
        	scanf("%c", &choice);
		getchar();
	}

	write_data(localPtr, "output.txt", size);
	
	//Frees allocated memory. 
	destroy(&localPtr, size);
	return(0);
}

/*****************************************************************************/
/*                                     FILE_LINE_COUNT                       */
/*****************************************************************************/

int file_line_count(const char *filename)
{
	unsigned int line_count = 0;				//Unsigned int to prevent negative values
	char c;							//character to check for newline character
	FILE *filePeople = fopen(filename, "r");		
	if(filePeople == NULL)					//Check to see if file is NULL	
		printf("\nUnable to open people.txt!\n\n");

	while(!feof(filePeople))	//while not end of file
	{				//c gets character from file with fgetc()
		c = fgetc(filePeople);	//if c is equal to newline character
		if(c == '\n')		//increment line count by 1
			line_count++;
	}

	fclose(filePeople);		//close file
	return(line_count);		//return line_count value for number of lines(size)
}

/*****************************************************************************/
/*                                     ALLOCATE                              */
/*****************************************************************************/

void allocate(char ***strings, int size)
{
	int i;//Index variable
	*strings = malloc(size * (sizeof(**strings)));
	if(*strings == NULL)//Check to make sure malloc returned an address and not NULL
	{
		printf("\nUnable to calloc strings memory!\n");
		exit(1);
	}
	for(i = 0; i < size; ++i)//for loop to calloc space for the strings in the pointer array
	{
		(*strings)[i] = calloc(MAX_STRING_LEN + 1, sizeof*((*strings)[i]));
		if((*strings)[i] == NULL)//check to make sure calloc returned addresses and not NULLS
		{
			printf("\nOut of memory!\n");
			exit(1);
		}
	}
	
}

/*****************************************************************************/
/*                                     DESTROY                               */
/*****************************************************************************/

void destroy(char ***strings, int size)
{
	int i;
	for(i = 0; i < size; ++i)	//for loop to free up space allocated for each string value
		free((*strings)[i]);	//in pointer array
	free(*strings);			//frees up pointer array
}

/*****************************************************************************/
/*                                     INSERT_DATA                           */
/*****************************************************************************/

void insert_data(char ***strings, const char *filename, int size)
{
	int i = 0;						//i used as index variable
	FILE *filePeople = fopen(filename, "r");		//open file to read names
	if(filePeople == NULL)					//check to see if file opened correctly
		printf("\nUnable to open people.txt!\n\n");

	for(i = 0; i < size; ++i)				//for loop that scans in names into the
	{							//strings pointer array.  Uses i to increment
		fscanf(filePeople, "%s", (*strings)[i]);	//placement of where to add name
		/* puts() to test if pointer array was filled */
		//puts((*strings)[i]);
	}	
	
	fclose(filePeople); //Close file when finished
}

/*****************************************************************************/
/*                                     HISTOGRAM                             */
/*****************************************************************************/

void histogram(char **strings, int *hist, int size)
{
	int i, j, length;
	for(i = 0; i < MAX_STRING_LEN; ++i)
	{
		hist[i] = 0;

		for(j = 0; j < size; ++j)
		{
			length = strlen(strings[j]);
			if(length = j)
				hist[j]++;
		}
	}
}

/*****************************************************************************/
/*                                     SORT_DATA                             */
/*****************************************************************************/

void sort_data(char **strings, int size)
{
	/* USES INSERTION SORT TO SORT DATA SET IN ASCENDING ORDER */
	int i, j;
	char *temp;
	for(i = 1; i < size; ++i)
	{
		temp = strings[i];
		j = i;

		while((j > 0) && strcmp(temp, (strings[j - 1])) < 0)
		{
			strings[j] = strings[j - 1];
			j--;
		}
		strings[j] = temp;
	}
}

/*****************************************************************************/
/*                                     FIND_NUMBER_OF_PREFIXS                */
/*****************************************************************************/

int find_number_of_prefixs(char **strings, int size)
{
	int i, count = 0;				//strncmp() compares up to a number of
	for(i = 0; i < size; ++i)			//characters from first string and 2nd string
		if(strncmp(strings[i], "ma", 2) == 0)	//value at end is how many characters to look
			count++;
	return(count);
}

/*****************************************************************************/
/*                                     FIND_NUMBER_OF_SUFFIXS                */
/*****************************************************************************/

int find_number_of_suffixs(char **strings, int size)
{
	int i, count = 0;

	for(i = 0; i < size; ++i)
		if(strncmp(strings[i], "an", 2) < 0)
			count++;
	return(count);

}

/*****************************************************************************/
/*                                     BINARY_SEARCH                         */
/*****************************************************************************/

int binary_search(char **strings, char *target, int start_idx, int end_idx)
{
	/* Recursion method of a binary search function. Binary search takes an
 	   array and splits it in half and then determines which half to look through
	   continues this until it finds (or doesnt find) the target value   */
	
	if(start_idx > end_idx)	//immediate termination condition
		return(-1);
		
	int mid_idx = ((start_idx + end_idx) / 2);	//mid_idx cuts the array in half
	int cmpValue = strcmp(target, strings[mid_idx]);//cmpValue gets value of strcmp of the
							//target and the string at mid_idx
	if(cmpValue == 0)
		return(mid_idx);
	else if(cmpValue < 0)//Search left  half of array
		return(binary_search(strings, target, start_idx, mid_idx - 1));
	else//search right half of array
		return(binary_search(strings, target, mid_idx + 1, end_idx));

}
	

/*****************************************************************************/
/*                                     WRITE_DATA                            */
/*****************************************************************************/

void write_data(char **strings, char *filename, int size)
{
	int hist[MAX_STRING_LEN];
	int suffixCount = find_number_of_suffixs(strings, size);
	int prefixCount = find_number_of_prefixs(strings, size);
	FILE *outFile = fopen(filename, "w");
	if(outFile == NULL)
		printf("\n\nFailed to open output.txt!\n\n");

	/* histograms have been the bane of my programming career forever */	
/*	histogram(strings, hist, size);
	int i, j;
	for(i = 0; i < size; ++i)
	{
		fprintf(outFile, "Number of names with %d characters:", i);
		for(j = 0; j < hist[j]; ++j)
			fprintf(outFile, "*");
		fprintf(outFile, "\n");
	}
*/
	fprintf(outFile, "Number of names with prefix of ma are %d\n", prefixCount);
	fprintf(outFile, "Number of names with suffix of an are %d\n", suffixCount);	
}
