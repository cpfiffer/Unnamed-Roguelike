#include "entities.h"

entity::entity() {
    int i;
    for (i=0;i<2;i++) {
        pos[i] = 0;
        size[i] = 1; //1x1 for default
    }

    myChar = 'D';
    myColor = TCODColor::blue;

    nextEntity = NULL;
    firstEntity = NULL;
}

stats::stats()
{
	//basic stats and stuff
	int str=0;
	int con=0;
	int intel=0;
	int foc=0;
	int dex=0;
	//these are the skills
	int science=0;
	int guns=0;
	int fisticuffs=0;
	int sticks=0;
	int driving=0;
}
// *entity::insertNew() {
    //entity *newEnt;
    //return newEnt;
//}

void entity::deleteOld(entity *oldEnt) {
}