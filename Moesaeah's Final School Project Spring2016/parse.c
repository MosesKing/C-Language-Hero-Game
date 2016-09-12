#include "game.h"
//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again.

/*
Input: a (ALREADY MALLOCED) shield/sword, and the OPEN file pointer
Return: none
These functions are identical except for one line: the defense value vs the
attack value. The file pointer passed into the function is pointing at the next
line in the file to be read. You will have to get that line and, from that,
fill the shield/sword with its information. DO NOT USE FSCANF!
A suggestion would be to start with fgets(), since you can specify the maximum
number of characters to read from the line.
This way, you can guarantee to read the entire line that you need to parse.


*/


void ParseShieldInfo(Shield* s, FILE* fp)
{
	// So we're gunna make our variables that will hold our shields (s) information
	char name[50];
	char cost[10];
	char defense[10];
	// looking at the struct in game.h the max size for the description is only 100 characters long
	// hence, I made what the array that will store the description from the file also 100 characters long
	char shieldDescription[100];
	// our buffer which will hold the string line from the file
	char buffer[MAXFILELINELENGTH];
	fgets(buffer, MAXFILELINELENGTH, fp); // used fgets like the instructions ^^ above said to use

	// So, instead of using strtok and having to figure how to tokenize the line, while not being able to use the ctype.h library
	//  i thought it'd be easier to use sscanf and then set our intialized variable to pieces of the string
	sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^\n]\n", name, cost, defense, shieldDescription);
	// setting the strings stuff equal to what it actually is
	strcpy(s->name, name);

	// changing the string to numbers
	s->cost = atoi(cost);
	s->defense = atoi(defense);
	//putting the description of shieldDescription into the s->description
	strcpy(s->description, shieldDescription);

}

void ParseSwordInfo(Sword* s, FILE* fp)
{
	//My logic will be the same for the swords
	char name[50];
	char cost[10];
	char attack[10];

	char swordDescription[100];

	char buffer[150];

	fgets(buffer, 150, fp);

	sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^\n]\n", name, cost, attack, swordDescription);
	strcpy(s->name, name);

	s->cost = atoi(cost);
	s->attack = atoi(attack);

	strcpy(s->description, swordDescription);

}
