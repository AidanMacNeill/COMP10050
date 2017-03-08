/*
 * functions.h
 *
 *  Created on: 4 Mar 2017
 *      Author: aidan
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define MAX_SIZE 50
#include <stdbool.h>

struct player
{
	char name[MAX_SIZE];
	char type[MAX_SIZE];
	int health;
	int magic;
	int smartness;
	int strength;
	int dexterity;
	int luck;
	int pos;
};

struct slot
{
	int id;
	char type[MAX_SIZE];
	bool occupied;
};

void assignSlots(int numSlots, char* slotsType[], struct slot slots[]); //TODO test

void playerPosition(int numPlayers, int numSlots, struct player players[], struct slot slots[]);

void playerInit(int numPlayers, struct player players[], char* playerType[]);

void playerStats(struct player players[], char* playerType[], int numPlayers);

void playerMove(struct player players[], struct slot slots[], int numSlots, int c, int i);
#endif /* FUNCTIONS_H_ */
