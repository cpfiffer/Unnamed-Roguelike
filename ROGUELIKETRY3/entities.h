#pragma once
#include "main.h"

class entity {
public:
    entity();
    ~entity();

    int pos[2];
    int size[2]; // Like if you wanted cars or something (2x2 bricks)
    char myChar;
    TCODColor myColor;

    entity *next;
};

class entityList {
public:
    entityList();
    ~entityList();

    entity *head;

    int size;

    // Returns a pointer to a fresh entity
    entity *insert();
    // Pass this function an entity
    void remove(entity *removeMe);
};