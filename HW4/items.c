//Name:			Clark Blumer
//PawPrint:		cjbq4f
//Date:			7-22-2014
//Assignment:	Homework 4 - Section A

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "items.h"
#include "utility.h"

void insert_into_items_tree(Item **node, char** data) 
{
	/*	Similar to the insert_into_commands_tree function except
		there is an additional check that looks for repeats. */
	if(*node == NULL)
	{
		*node = create_item(data);
	}
	else if(strcmp(data[1], (*node)->name) == 0)
		(*node)->occurances += (*node)->occurances;
	else if(strcmp(data[1], (*node)->name) < 0)
		insert_into_items_tree(&((*node)->left), data);
	else							
		insert_into_items_tree(&((*node)->right), data);
}

Item* create_item(char **strings)
{
	//Allocates and initializes values for an Item node
	//to be inserted into a Binary Tree of Item nodes.
	Item *node = malloc(sizeof(Item));
	strcpy(node->name, strings[1]);
	node->occurances = atoi(strings[2]);
	node->left = NULL;
	node->right = NULL;
	return node;
}

void destroy_items_tree(Item* node) 
{
	if(node)
	{
		//recursive call adds nodes to the stack and then
		//frees each node as it goes through the stack.
		destroy_items_tree(node->left);
		destroy_items_tree(node->right);
		free(node);
	}
}

Item* load_saved_items(const char *file) 
{	
	/* 	Similar to the create_commands_tree function except 
		load_saved_items returns an Item* */
	FILE *savedItemsFile = fopen(file, "r");
	char buffer[MAX_BUFF_SIZE];
	Item **itemsPtr = NULL;
	StringArray *ptr;
	if(!savedItemsFile)
	{
		printf("\nFailed to open saved items file!\n");
		exit(1);
	}
	
	while(fgets(buffer, MAX_BUFF_SIZE, savedItemsFile)) {
		ptr = tokenizer(buffer, ",\n");
		//printf("%s %s\n", ptr->strings[0], ptr->strings[1]);
		insert_into_items_tree(itemsPtr, ptr->strings);
		free_string_array(ptr);
	}
	
	//close file and return Item*
	fclose(savedItemsFile);
	return *itemsPtr;
}

void display_items_tree(Item *node) 
{
	if(node == NULL)
		return;
	display_items_tree(node->left);
	printf("%s %d\n", node->name, node->occurances);
	display_items_tree(node->right);
}
