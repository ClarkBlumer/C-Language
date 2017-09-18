//Name:
//Date:
//Lab:


#include <stdio.h>
#include <string.h>

//Definitions
#define MAX_NAME_LEN 25
#define MAX_PEOPLE 10

//Structure
typedef struct Person_
{
	char name[MAX_NAME_LEN];
	int age;
}Person;

//Prototypes
void read_from_file_people(Person *, char *);
void sort_people(Person *);
void write_to_file_people(Person *, char *);


int main(int argc, char **argv)
{
	//Check to make sure sufficient arguments in command line
	if(argc < 3)
	{
		printf("\nInsufficient arguments\n\n");
		return(0);
	}
	
	//Check to make sure file names are correct in command line
	if(strcmp(argv[1], "persons.txt") != 0 || strcmp(argv[2], "sorted_persons.txt") != 0)
	{
		printf("\nInvalid filenames! Use only persons.txt and sorted_persons.txt\n\n");
		return(0);
	}

	//Declarations
	Person array[MAX_PEOPLE];	//Data type of Person array[10]
	
	read_from_file_people(array, "persons.txt");
	sort_people(array);
	write_to_file_people(array, "sorted_persons.txt");
	//int i;
	//for(i = 0; i < MAX_PEOPLE; ++i)
	//	printf("%s %d\n", array[i].name, array[i].age);

	return(0);
}

void read_from_file_people(Person *people, char *filename)
{
	//Loads info from file persons.txt into the Person type array
	int i;
	FILE *file = fopen(filename, "r");
	if(file == NULL)
		printf("\n\nFailed to load file!\n");

	for(i = 0; i < MAX_PEOPLE; ++i)
	{
		fscanf(file, "%s %d\n", people[i].name, &people[i].age);
	}

	fclose(file);
}

void sort_people(Person *people)
{
	int i, j;
	Person temp[MAX_NAME_LEN];

	for(i = 0; i < MAX_PEOPLE - 1; ++i)
	{
		for(j = i + 1; j < MAX_PEOPLE; ++j)
			if(strcmp(people[i].name, people[j].name) > 0)
			{
				strcpy(temp[i].name, people[i].name);
				temp[i].age = people[i].age;
				strcpy(people[i].name, people[j].name);
				people[i].age = people[j].age;
				strcpy(people[j].name, temp[i].name);
				people[j].age = temp[i].age;
			}
	}//End first for loop

}

void write_to_file_people(Person *people, char *filename)
{
	FILE *outFile = fopen(filename, "w");
	if(outFile == NULL)
		printf("\n\nUnable to open output file!\n");

	int i;

	for(i = 0; i < MAX_PEOPLE; ++i)
	{
		fprintf(outFile, "%s %d\n", people[i].name, people[i].age);
	}

	fclose(outFile);
}
