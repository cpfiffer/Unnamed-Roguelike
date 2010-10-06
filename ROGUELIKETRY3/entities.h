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
	//health, mind, body
	int health;
	int mind;
	int body;
	//hidden stats
	int dodgeValue;
};

class entity:stats {
public:
    entity();
    //~entity();

    int pos[2];
    int size[2]; // Like if you wanted cars or something (2x2 bricks)
    char myChar;
    TCODColor myColor;

    entity *next;
};

class entityList {
public:
    entityList();
    //~entityList();

    entity *head;

    int size;

    // Returns a pointer to a fresh entity
    entity *insert();
    // Pass this function an entity
    void remove(entity *removeMe);
};