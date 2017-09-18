//Name:			Clark Blumer
//Pawprint:		cjbq4f
//Date:			7-06-2014
//Assignment:	Prelab 6
/*
	Program creates a linked list of linked lists. Effectively a 2D linked list.
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct MatrixNode_
{
	int value;
	struct MatrixNode_ *next_row;
	struct MatrixNode_ *next_col;
}MatrixNode;

void create_linked_list_matrix(MatrixNode**, const int rows, const int cols);
MatrixNode* create_node();
void display_matrix(MatrixNode*);
void destroy_linked_list_matrix(MatrixNode**);

int main (int argc, char *argv[]) 
{
	if (argc < 3) {
		exit(1);
	}
	srand(time(NULL));
	const int rows = atoi(argv[1]);
	const int cols = atoi(argv[2]);
	MatrixNode* head_a = NULL;
	printf("Matrix A\n");
	create_linked_list_matrix(&head_a,rows,cols);
	display_matrix(head_a);
	destroy_linked_list_matrix(&head_a);
}

void create_linked_list_matrix(MatrixNode **head, const int rows, const int cols)
{
	MatrixNode *currentRowNode = *head;
	MatrixNode *newRowNode = NULL;
	MatrixNode *currentColNode = currentRowNode;
	MatrixNode *newColNode = NULL;
	int i, j;
	currentRowNode = malloc(sizeof(MatrixNode));

	for(i = 0; i < rows; ++i)
	{
		currentRowNode = create_node();
		for(j = 0; j < cols; ++j)
			currentColNode = create_node();
	}

	
}

MatrixNode* create_node()
{
	MatrixNode *newNode = malloc(sizeof(MatrixNode));
	if(newNode == NULL)
	{
		//newNode->next_col = newNode;
		newNode->next_col = NULL;
		newNode->next_row = NULL;
		newNode->value = rand() % 100 + 1;
		return newNode;
		
	}
	else
	{
		while(newNode->next_col != NULL)
			newNode = newNode->next_col;
			newNode->value = rand() % 100 + 1;
			return newNode;
			
	}
}

void display_matrix(MatrixNode* head)
{
	MatrixNode *ptr = NULL;
	
	// Check for empty list
	if(head == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	// if first isnt null, ptr will store the address of the first node
	ptr = head;
	while(ptr != NULL)
	{
		printf(" %d \n", ptr->value);
		ptr = ptr->next_col; // ptr will move to next node, if first->next is NULL, NULL condition
	}			 // will be met and break the while loop
}

void destroy_linked_list_matrix(MatrixNode** head)
{

/*	MatrixNode *freeMe = head;
	MatrixNode *holdMe = NULL;
	while(freeMe != NULL)
	{
		holdMe = freeMe->next;
		free(freeMe);
		freeMe = holdMe;
	}
*/
}
