







#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdio.h>


typedef struct node *nodePtr;

typedef struct node
{
	int data;
	nodePtr next;
}node;

int main(int argc, char **arvg)
{
	nodePtr first = NULL;//points to first node of link list
	first = malloc(sizeof(node));//allocates memory size of a node
	first->next = NULL;
	first->data = 61;
	
	//Adds another node in the link list
	//first->next = malloc(sizeof(node));
	//(first->next)->next = NULL;
	//(first->next)->data = 62;
	
	//How to insert at beginning of link list
	//Makes a temp instance of nodePtr which
	//copies first NULL pointer to temp
	//
	nodePtr temp;
	temp = malloc(sizeof(node));
	temp->next = first;
	first = temp;
	

	return(0);
}
