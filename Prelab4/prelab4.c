//Name:
//Date:
//Description:


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
void printList(FreightCar *engine);

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
	
	/* Delcarations of variables  */
	int i;
	//char name[MAX_STR_LEN];
	//int carNum = 0;
	FreightCar *engine = NULL; //First node of struct FreightCar
	engine = malloc(sizeof(FreightCar)); //allocate enough memory for the FreightCar node
	engine->name = malloc(MAX_STR_LEN * sizeof(char)); 		
	

	for(i = 0; i < size; i++)
	{
		printf("Enter in freight car name and number: ");
		scanf("%s %d", engine->name, &engine->number);
		printf("\n");
		//engine->name = name;
		//engine->number = carNum;
		add_car(engine);
	}

	free_cars(engine);
	free(engine);
	return(0);
}

void add_car(FreightCar *engine)
{
	FreightCar *head = NULL, *newCar = NULL, *currentCar = NULL, *nextCar = NULL, *previousCar = NULL;
	int i;
	newCar = malloc(sizeof(FreightCar));
	newCar->name = malloc(MAX_STR_LEN * sizeof(char));
	
	if((newCar = malloc(sizeof(FreightCar))) == NULL)
	{
		printf("\nMemory allocation failed!\n");
		exit(1);
	}

	currentCar = head;
	previousCar = NULL;
	newCar->name = engine->name;
	newCar->number = engine->number;
	newCar->next_car = currentCar;

	if(previousCar == NULL)
		head = newCar;
	else
		previousCar->next_car = newCar;
	
	currentCar = head;
	printf("%s %d\n", currentCar->name, currentCar->number);


/*	currentCar = head;
	while(currentCar != NULL)
	{
		nextCar = currentCar->next_car;
		free(currentCar);
		currentCar = nextCar;
	}
*/
}


void free_cars(FreightCar *engine)
{
	FreightCar *curr_car = engine->next_car;
	FreightCar *needs_freeing;
	while(curr_car)
	{
		needs_freeing = curr_car;
		curr_car = curr_car->next_car;
		free(needs_freeing->name);
		free(needs_freeing);
	}
}
