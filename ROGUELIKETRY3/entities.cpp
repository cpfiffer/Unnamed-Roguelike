#include "entities.h"

entity::entity() {
    int i;
    for (i=0;i<2;i++) {
        pos[i] = 0;
        size[i] = 1; //1x1 for default
    }

    myChar = 'D';
    myColor = TCODColor::blue;

    next = NULL;
}

entity::~entity() {
}

entityList::entityList() {
    size=0;
    head = NULL;
}

entityList::~entityList() {
    /*entity *cur = head;
    entity *nextNode = head->next;
 
    while (cur != NULL) {
        nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }*/
}

entity *entityList::insert() {
    entity *newEntity = new entity;

    if (head == NULL) {
        head = newEntity;
        newEntity->next = NULL;
        return newEntity;
    } else { 
        entity *nextEntity = head;
        while(nextEntity != NULL) {
            // If we are at the end of the list:
            if (nextEntity->next == NULL) {
                // Make the old end point to the new end:
                nextEntity->next = newEntity;
                // Make sure the new end is NULL
                newEntity->next = NULL;
                return newEntity;
            } else {
                nextEntity = nextEntity->next;
            }
        }
    }
    return 0;

}

void entityList::remove(entity *removeMe) {
    entity *prev = NULL;
    entity *current = head;

    entity *old;
    while (current != NULL) {
        if (current == removeMe) {
            if (prev == NULL) {
                // If previous is NULL, we're removing the head 
                // of the linked list.
                old = head;
                head = head->next;
                delete old;
            } else {
                prev->next = current->next;
                delete current;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}
