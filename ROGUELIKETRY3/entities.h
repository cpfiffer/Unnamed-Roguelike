#pragma once
#include "main.h"
class stats
{
public:
	stats();
	//basic stats and stuff
	int str;
	int con;
	int intel;
	int foc;
	int dex;
	//these are the skills
	int science;
	int guns;
	int fisticuffs;
	int sticks;
	int driving;
};
class entity:stats {
public:
    entity();
    ~entity();

    int pos[2];
    int size[2]; // Like if you wanted cars or something (2x2 bricks)
    char myChar;
    TCODColor myColor;

    entity *nextEntity; // Linked list of entities
    entity *firstEntity;

    entity *insertNew();
    void deleteOld(entity *oldEnt);
};