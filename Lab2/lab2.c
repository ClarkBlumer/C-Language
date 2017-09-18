//Name:		Clark Blumer
//Pawprint:	cjbq4f
//Lab:		Lab2
//Date:		6-09-2014
//Lab Code:	Binary Searching

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 25
#define MAX_PEOPLE 10

typedef struct Person_
{
	char name[MAX_NAME_LEN];
	int age;
}Person;


void read_from_file_people(Person *, const char *);	//Gets array of type Person and filename
void sort_people(Person *);				//Gets array of type Person
int binary_search(Person *, char *, int, int);		//Gets array of type Person, target, min_idx, max_idx
void display_file_stats(Person *, int);			//Gets array of type Person, size
void write_to_file_people(Person *, char *);		//Gets array of type Person, filename


int main(int argc, char *argv[])
{
	//Error checking to make sure enough arguments were passed on command line
	if(argc < 3)
	{
		printf("\nInsufficient arguments\n\n");
		return(0);
	}	
	
	//Error checking to make sure correct file names were passed
	if(strcmp(argv[1], "persons.txt") != 0 || strcmp(argv[2], "sorted_persons.txt") != 0)
	{
		printf("\nInvalid filenames! Use only persons.txt and sorted_persons.txt\n\n");
		return(0);
	}
	
	Person array[MAX_PEOPLE];

	//Reads people from file persons.txt and fills array 
	read_from_file_people(array, "persons.txt");
	//Sorts people based on name 
	sort_people(array);
	//Writes sorted array to file
	write_to_file_people(array, "sorted_persons.txt");

	//Binary search
	char name[MAX_NAME_LEN];
	char quit;
	int found;

	printf("\n\n");

	printf("Enter a name to search for: ");
        scanf("%s", name);
	getchar();
        found = binary_search(array, name, 0, MAX_PEOPLE);

	if(found == -1)
		printf("%s was not found in this persons.txt\n");
	else
		printf("%s was found at this index %d with this age %d\n", name, found, array[found].age);
	
	printf("Continue searching names?(y/n): ");
        scanf("%c", &quit);
	getchar();	
	while(quit != 'n')
	{
		printf("Enter a name to search for: ");
		scanf("%s", name);
		getchar();
		found = binary_search(array, name, 0, MAX_PEOPLE);
		if(found == -1)
			printf("%s is not in this persons.txt\n", name);
		else
			printf("%s was found at this index %d with this age %d\n", name, found, array[found].age);	
	
		printf("Continue searching names?(y/n): ");
		scanf("%c", &quit);
		getchar();
	}

	display_file_stats(array, MAX_PEOPLE);
	return(0);
}

void read_from_file_people(Person *people, const char *filename)
{
	int i;								//opens file to read
	FILE *file = fopen(filename, "r");				//check to see if file is NULL
	if(file == NULL)
		printf("\nFailed to load file!\n");

	for(i = 0; i < MAX_PEOPLE; ++i)					//fills array with values from file
		fscanf(file, "%s %d\n", people[i].name, &people[i].age);

	fclose(file);
}


void sort_people(Person *people)
{
	int i, j;							//Function sorts array based on 
	Person temp[MAX_NAME_LEN];					//alphabetical names

	for(i = 0; i < MAX_PEOPLE - 1; ++i)
	{
		for(j = i + 1; j < MAX_PEOPLE; ++j)			//compares the values at each index
			if(strcmp(people[i].name, people[j].name) > 0)	//if they are greater than 0
			{						//copy from one string to another
				strcpy(temp[i].name, people[i].name);	//temp[i].age = people[i].age transfer
				temp[i].age = people[i].age;		//the age associated with the name
				strcpy(people[i].name, people[j].name);	
				people[i].age = people[j].age;
				strcpy(people[j].name, temp[i].name);
				people[j].age = temp[i].age;
			}//End string compare if statement
	}//End outer for loop
}


int binary_search(Person *people, char *target, int min_idx, int max_idx)
{
	int mid_idx = 0;					//Function takes the people arry and
	while(max_idx >= min_idx)				//looks for target name in the array
	{							//using binary search to find the index
		mid_idx = (max_idx + min_idx) / 2;		//location if name is found.
								//if the name at people[mid_idx is the
		if(*(people[mid_idx].name) == *target)		//same as the name at target
			return(mid_idx);			//returns that index location.
		else if(*(people[mid_idx].name) < *target)	//else increments the min idx and decrements
			min_idx++;				//the max index to compare the next values
		else
			max_idx--;	
	}
}


void display_file_stats(Person *people, int size)
{
	int i, j, temp = 0, tempAge = 0, minAge = 100;
	Person stats[MAX_NAME_LEN];
	read_from_file_people(stats, "sorted_persons.txt");
	for(i = 0; i < size + 1; ++i)
	{
		for(j = 0; j < size; ++j)
			if(strlen(people[i].name) > strlen(people[j].name))
			{
				*stats[i].name = *people[i].name;
				temp = i;			
			}

	}							
	for(i = 0; i < size; ++i)			//loops through the array			
		if(people[i].age < minAge)		//checking age against minAge
                {					//if the age in the array is < minAge
                        minAge = people[i].age;		//minAge gets that value.  tempAge holds value of index
                        tempAge = i;			
                }
	
	
	printf("\nLongest name is %s with %d characters\n", people[temp].name, strlen(people[temp].name));
	printf("Youngest person is %s at %d\n", stats[tempAge].name, minAge);
	
}


void write_to_file_people(Person *people, char *filename)
{
	FILE *outFile = fopen(filename, "w");			//Opens file to write
	if(outFile == NULL)					//checks to make sure the file opens
		printf("\nUnable to open output file!\n");	//message to indicate problem opening file

	int i;
	for(i = 0; i < MAX_PEOPLE; ++i)
		fprintf(outFile, "%s %d\n", people[i].name, people[i].age);	//prints array to file

	fclose(outFile);//closes file
}
