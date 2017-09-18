/*
* Name:			Clark Blumer
* Pawprint:		cjbq4f
* Section:		A
* Assignment:		Homework 2
* Date:			6-30-2014
* */

/* Program takes a list of 30493 names and sorts them using two different sort algorithms:
 * a bubble sort and a merge sort. The program also tracks how long each algorithm takes
 * to sort desired list length inputed by the user in the command prompt. Helps illustrate
 * how dataset size can determine which algorithms to use. */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<sys/time.h>
#include<string.h>

#define MAX_STR_LEN 25

typedef struct Data_ {

	char *name;
	struct Data_ *nextData;	

}Data;

// KEEP THIS STRUCTURE
typedef struct Timer_ {
	double start;
	double end;
}Timer;

// USED FOR BUBBLE SORT
Data* bubble_sort(Data *list);
//USED FOR MERGE SORT
int length(Data* list);
void move_node(Data** destRef, Data** sourceRef);
void split_in_half(Data *source, Data **frontRef, Data** backRef);
Data* merge(Data *a, Data* b);
void merge_sort(Data **list);
// USED FOR creating out list
void push(Data **head, char *name);
//USED FOR freeing our list
void destroy(Data *list);
//Allows us to open a file and create our linked list
Data* read_from_file(const char* file, const int size);
// shows to the user the linked list
void display(Data *list);
// USED FOR TIMING OUR CODE
void start_timer(Timer* t);
double get_time_diff(Timer* t);
void end_timer(Timer *t);
Data* swap(Data*, Data*);

int main (int argc, char **argv) {
	/*
	 * Error checking the number of passed in parameters
	 * */
	if (argc < 3) {
		printf("Not enough parameters bub!\n");
		exit(0);
	}
	/*
	 * Opening file for writng the timing output
	 * */
	FILE* fp = fopen("timing.out", "w");
	
	
	Data *head = NULL;
	// Pulling the number of names needed to read into my program
	const int size = atoi(argv[2]);
	
	/*
	 * Setting up timer structure
	 * */
	Timer *t = malloc(sizeof(Timer));
	t->start = 0;
	t->end = 0;

	/*
	 * Timing read from file
	 * */
	start_timer(t);
	head = read_from_file(argv[1], size);
	end_timer(t);
	fprintf(fp,"\nReading from the %s %d took %lf msecs\n\n", argv[1], size,get_time_diff(t));
	
	/*
	 * Timing the time taken to sort with bubble sort
	 * */
	printf("Bubble Sort\n");
	fprintf(fp,"Bubble Sort\n");
	start_timer(t);
	head = bubble_sort(head);
	end_timer(t);
	fprintf(fp,"Sorting the linked list with bubble sort\ntook %lf msecs for %d nodes\n\n", get_time_diff(t), size);
	display(head);
	/*
	 * Destroying current head and reassigning back to NULL
	 * */
	destroy(head);
	head = NULL;
	head = read_from_file(argv[1], size);
	
	/*
	 * Timing the time taken to sort with merge sort
	 * */
	printf("\nMerge Sort\n");
	fprintf(fp,"\nMerge Sort\n");
	start_timer(t);	
	merge_sort(&head);
	end_timer(t);
	fprintf(fp,"Sorting the linked list with merge sort\ntook %lf msecs for %d nodes\n\n", get_time_diff(t), size);
	display(head);

	/*
	 * Clean up of allocations and open files
	 * */
	destroy(head);
	free(t);
	fclose(fp);
	// destroy list
	return 0;
}

/*
 * Timing functions (DO NOT DELETE THEM!)
 **/
void start_timer(Timer *t) {
  struct timeval tp;
  int rtn;
  rtn=gettimeofday(&tp, NULL);
  t->start =  (double)tp.tv_sec+(1.e-6)*tp.tv_usec;
}

double get_time_diff(Timer *t) {

	return t->end - t->start;
}

void end_timer(Timer *t) {
  struct timeval tp;
  int rtn;
  rtn=gettimeofday(&tp, NULL);
  t->end =  (double)tp.tv_sec+(1.e-6)*tp.tv_usec;
}

void destroy(Data* list) {

	Data *current = list;
	Data *freeMe = NULL;
	while(current)
	{
		freeMe = current;
		current = current->nextData;
		free(freeMe->name);
		free(freeMe);		
	}
}

Data* read_from_file(const char *file, const int size){
	
	int i;
	char names[MAX_STR_LEN];
	Data *head = NULL;
	FILE *namesFile = fopen(file, "r");
	if(!namesFile)
	{
		printf("\nCould not open file!\n");
		return;
	}

	for(i = 0; i < size; ++i)
	{
		fscanf(namesFile, "%s", names);
		push(&head, names);

	}
	fclose(namesFile);
	return head;
}

void push(Data **head, char *name) {

	Data *temp = malloc(sizeof(Data));
	temp->name = malloc(MAX_STR_LEN * sizeof(char));
	if(!temp)//malloc check -- looking for NULL value
	{
		printf("\nFailed to allocate memory in push()\n");
		return;
	}
	strcpy(temp->name, name);
	temp->nextData = *head;
	*head = temp;
}

Data* bubble_sort(Data *list) {

	if(!list)
		return NULL;
	int size = 0;
	size = length(list);
	Data *temp = list;
	int i, j; //indexes

	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size - 1; ++j)
		{
			if(strcmp(temp->name, temp->nextData->name) >= 0)
			{
				char *cp;			  //Basic swap action
				cp = temp->name;		  //cp takes temp->name
				temp->name = temp->nextData->name;//temp->name gets next's name
				temp->nextData->name = cp;	  //next name gets cp
			}//end if
		}//end inner for loop
	}//end outer for loop
	return temp;

}

Data* swap(Data *left, Data *right) {

	left->nextData = right->nextData;
	right->nextData = left;
	return right;
	
}

void display(Data *list) {

	Data *current = NULL;
	
	// Check for empty list
	if(list == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	// if list isnt null, current will store the address of the head node
	current = list;
	while(current != NULL)
	{
		printf("%s\n", current->name);
		current = current->nextData; // current will move to next node, if list->next is NULL, NULL condition
	}			 // will be met and break the while loop

}

/*
 * Used to find the length of an linked list useful inside split_in_half function
 * */
int length(Data* list) {
	int count = 0;
	Data *current = list;
	while(current) {//while current != NULL //while current == something
		current = current->nextData;//current takes the value of the next node
		++count;//increment count by 1
	}
	return count;//return number of nodes as length
}

void split_in_half(Data *source, Data **frontRef, Data** backRef) {

	Data *frontHalf;
	Data *backHalf;
	int size = 0;
	size = length(source);

	//checks to make sure list is bigger than 2
	if(size < 2)
	{
		*frontRef = source; //if size is less than 2, frontRef gets source
		*backRef = NULL;
	}
	else //else backHalf gets source and frontHalf gets source->nextData
	{
		backHalf = source;
		frontHalf = source->nextData;

		//Moes frontHalf two nodes and backHalf one node
		while (frontHalf != NULL)
		{
			frontHalf = frontHalf->nextData;//move one forward
			if (frontHalf != NULL)
			{
				backHalf = backHalf->nextData;//move one forward
				frontHalf = frontHalf->nextData;//move two forward
		}
    }

	//backHalf is before the midpoint in the list so split in two at that point
    *frontRef = source;
    *backRef = backHalf->nextData;
    backHalf->nextData = NULL;
  }
}

/*
 * Take the node from the front of the source, and move it to the front 
 * of the dest. It is an error to call this with the sourceRef list is empty.
 *
 * before calling move_node():
 * source == {1,2,3}
 * dest == {1,2,3}
 *
 * After calling move_node():
 * source == {2,3}
 * dest == {1,1,2,3}
 * */
void move_node(Data** destRef, Data** sourceRef) {
	Data* newData = *sourceRef;
	*sourceRef = newData->nextData;
	newData->nextData = *destRef;
	*destRef = newData;
}

Data* merge(Data *a, Data* b) {

	Data *result = NULL;

	//Base cases
	if (a == NULL)//if a is NULL return b
		return(b);
	else if (b==NULL)//if b is NULL return a
		return(a);

	//compares the two names and then does recursion based on result
	if (strcmp(a->name, b->name) >= 0)
	{
		result = a;
		result->nextData = merge(a->nextData, b);
	}
	else
	{
		result = b;
		result->nextData = merge(a, b->nextData);
	}
	return(result);
}

void merge_sort(Data **list) {

	Data *head = *list;
	Data *a;
	Data *b;
	
	//Base case check
	if ((head == NULL) || (head->nextData == NULL))
	{
		return;
	}

	//split head into the a and b lists
	split_in_half(head, &a, &b); 

	//recursive calls to sort the lists
	merge_sort(&a);
	merge_sort(&b);

	//merge the two sorted lists together
	*list = merge(a, b);
		
}

