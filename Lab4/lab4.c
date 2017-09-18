//Name:		Clark Blumer
//PAwprint:	cjbq4f
//Date:		6-23-2014
//Lab Code:	Farscape

/* Had a lot of trouble with this lab 
   and pre-lab. Most everything doesn't work */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STR_LEN 25

typedef struct FreightCars_
{
	char *name;
	int number;
	struct FreightCars_ *next_car;
	
}FreightCar;

void add_car(FreightCar *engine);
void free_cars(FreightCar *engine);
void update_car(FreightCar *engine);
void remove_next_car(FreightCar *engine);
void display_train(FreightCar *engine);

int main(int argc, char **argv)
{
	/* Checking for corrent number of command line arguments  */
	if(argc != 2)
	{
		printf("\nInvalid number of arguments!\n");
		return(0);
	}

	/* Getting size from 2nd command line argument (argv[1])  */
	int size = atoi(argv[1]);
	int i;
	FreightCar *engine = malloc(sizeof(FreightCar));//head node
	//engine->name = malloc(MAX_STR_LEN * sizeof(char));
	engine->name = "Union Pacific Train";
	engine->number = 10;
	engine->next_car = NULL;
	
	for(i = 0; i < size; i++)
	{
		add_car(engine);
	}

	free_cars(engine);	
	free(engine);
	return(0);
}

void add_car(FreightCar *engine)
{
	FreightCar *newCar = NULL;
	FreightCar *currentCar = NULL;
	FreightCar *head = engine;
	
	newCar = malloc(sizeof(FreightCar)); //create the node newCar
	newCar->name = malloc(MAX_STR_LEN * sizeof(char));//allocate space for string
	newCar->next_car = NULL;//set the next pointer to NULL
	currentCar = engine;
	
	printf("Freight car name and number: ");
	scanf(" %s %d", newCar->name, &newCar->number);
	
	
}

void free_cars(FreightCar *engine)
{
	FreightCar *curr_car = engine->next_car;
	FreightCar *needs_freeing;
	while(curr_car != NULL)
	{
		needs_freeing = curr_car;
		curr_car = curr_car->next_car;
		free(needs_freeing->name);
		free(needs_freeing);
	}
	curr_car = NULL;
}

void update_car(FreightCar *engine)
{

}

void remove_next_car(FreightCar *engine)
{

}

void display_train(FreightCar *engine)
{

}
