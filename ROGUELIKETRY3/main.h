#pragma once
#include <libtcod.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

#include "config.h"
#include "entities.h"

// WEIRD THINGS
enum mapType { woods, brick };
typedef char mapArray[80][50];

// CLASSES
class mapData;
class entity;
class entityList;

class cPlayer {
public:
    cPlayer();
    ~cPlayer();

    entity *checkEntCollides(int direction);
    int checkStaticCollides(int dest[2]);

    int pos[2];
    int cell[2];
    TCODColor myColor;
    char *collides;

    mapData *mapDataHandle;
};

class mapData {
public:
    mapData();
    ~mapData();

    bool changed;
    bool loaded;

    // Master array of the map
    mapArray mapHandlerMaster;
    entityList *masterList;

    mapType myType;
};

// GLOBAL FUNCS (Why so C?)
void render(cPlayer *mainPlayer);

void attack(entity *enemy);