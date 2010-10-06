#include "main.h"
using namespace std;

// Don't change these. My code isn't as modular as it looks.
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 50

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

// CONSTRUCTORS AND CLASS FUNCTIONS
cPlayer::cPlayer() {
    collides = "#-_|";
    mapDataHandle = new mapData();
    myColor = TCODColor::white;
    int i;
    for (i=0;i<2;i++) {
        pos[i] = 25;
        cell[i] = 0;
    }
}

cPlayer::~cPlayer() {
    delete mapDataHandle;
}

entity *cPlayer::checkEntCollides(int direction) {
    entity *loop = this->mapDataHandle->masterList->head;
    while (loop != NULL) {
        switch(direction) {
        case(LEFT):
            if (loop->pos[0] == (pos[0]-1) &&
                loop->pos[1] == pos[1]) {
                return loop;
            }
            break;
        case(RIGHT):
            if (loop->pos[0] == (pos[0]+1) &&
                loop->pos[1] == pos[1]) {
                return loop;
            }
            break;
        case(UP):
            if (loop->pos[1] == (pos[1]-1) &&
                loop->pos[0] == pos[0]) {
                return loop;
            }
            break;
        case(DOWN):
            if (loop->pos[1] == (pos[1]+1) &&
                loop->pos[0] == pos[0]) {
                return loop;
            }
            break;
        }
        loop = loop->next;
    }
    return 0;
}

int cPlayer::checkStaticCollides(int dest[2]) {
    char test = this->mapDataHandle->mapHandlerMaster[dest[0]][dest[1]];
    int i = 0;
    for (;i<sizeof(collides);i++) {
        if (test == collides[i])
            return 1;
    }
    return 0;
}

mapData::mapData() {
    int newType = rand() % 2;
    if (newType == 0)
        myType = woods;
    else
        myType = brick;
    int i,j;
    for (i=0;i<SCREEN_WIDTH;i++) {
        for (j=0;j<SCREEN_HEIGHT;j++) {
            // Set the default char to whatever the fuck
            if (myType == woods) {
                int test = (rand() % 4);
                if (test == 0)
                    mapHandlerMaster[i][j] = '.';
                else if (test == 1)
                    mapHandlerMaster[i][j] = ',';
                else if (test == 2)
                    mapHandlerMaster[i][j] = ' ';
                else if (test == 3)
                    mapHandlerMaster[i][j] = '|';
                /*else if (test == 4)
                    mapHandlerMaster[i][j] = '-';
                else if (test == 5)
                    mapHandlerMaster[i][j] = '|';
                else if (test == 6)
                    mapHandlerMaster[i][j] = '_';
                else if (test == 7)
                    mapHandlerMaster[i][j] = ',';
                else if (test == 8)
                    mapHandlerMaster[i][j] = '.';*/
            } else if (myType == brick) {
                int test = (rand() % 4);
                if (test == 0)
                    mapHandlerMaster[i][j] = '=';
                else if (test == 1)
                    mapHandlerMaster[i][j] = '=';
                else if (test == 2)
                    mapHandlerMaster[i][j] = '=';
                else if (test == 3)
                    mapHandlerMaster[i][j] = '#';
            }
        }
    }

    changed = false;
    loaded = true;

    masterList = new entityList;
}

mapData::~mapData() {
    delete masterList;
}

// END CONSTRUCTORS AND CLASS FUNCTIONS

void render(cPlayer *mainPlayer) {
    // Shorten this shit up a bit:
    mapData *mpShort = mainPlayer->mapDataHandle;

    TCODConsole *offscreenConsole = new TCODConsole(SCREEN_WIDTH,SCREEN_HEIGHT);
    offscreenConsole->setBackgroundColor(TCODColor::black);
    offscreenConsole->clear(); // Flush the new changes to the offscreen console

    // Map renderer:
    int i,j;
    for (i=0;i<SCREEN_WIDTH;i++) {
        for (j=0;j<SCREEN_HEIGHT;j++) {
            // Grass
            if (mpShort->mapHandlerMaster[i][j] == '.')
                offscreenConsole->setFore(i, j, TCODColor::green);
            if (mpShort->mapHandlerMaster[i][j] == ',')
                offscreenConsole->setFore(i, j, TCODColor::darkerGreen);
            if (mpShort->mapHandlerMaster[i][j] == '#')
                offscreenConsole->setFore(i, j, TCODColor::darkerCrimson);
            if (mpShort->mapHandlerMaster[i][j] == '_')
                offscreenConsole->setFore(i, j, TCODColor::darkerCrimson);
            if (mpShort->mapHandlerMaster[i][j] == '-')
                offscreenConsole->setFore(i, j, TCODColor::darkerCrimson);
            if (mpShort->mapHandlerMaster[i][j] == '|')
                offscreenConsole->setFore(i, j, TCODColor::darkSepia);
            if (mpShort->mapHandlerMaster[i][j] == '=')
                offscreenConsole->setFore(i, j, TCODColor::darkerGrey);

            // Place that character onscreen
            offscreenConsole->setChar(i, j, mpShort->mapHandlerMaster[i][j]);
        }
    }

    // Entity renderer:
    entity *loop = mainPlayer->mapDataHandle->masterList->head;
    while (loop != NULL) {
        // We have entities to render:
        offscreenConsole->setFore(loop->pos[0], loop->pos[1], loop->myColor);
        offscreenConsole->setChar(loop->pos[0], loop->pos[1], loop->myChar);
        
        loop = loop->next;
    }
    
    // Render the player last
    offscreenConsole->setFore(mainPlayer->pos[0], mainPlayer->pos[1], mainPlayer->myColor);
    offscreenConsole->setChar(mainPlayer->pos[0], mainPlayer->pos[1], '@');

    // Blit all that crap on-screen
    TCODConsole::blit(offscreenConsole,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,TCODConsole::root,0,0, 1.0f, 1.0f);

    // Flip it
    TCODConsole::flush();

    delete offscreenConsole;
}

void attack(entity *enemy)
{
	int enemyDodge = enemy->dodgeValue;
	int hitValue = mainPlayer->fisticuffs + mainPlayer->dex + (rand()%10);
	int damageValue = mainPlayer->fisticuffs + (mainPlayer->str / 2) + (rand()%5);
	if (hitValue >= enemyDodge)
	{
		enemy->health = enemy->health - damageValue;
	}
}

int keyHandler(cPlayer *mainPlayer) {
    TCOD_key_t key = TCODConsole::waitForKeypress(true);
    // Special keys:
    if (key.vk == TCODK_ESCAPE)
        return -1;
    // Movement:
    int moveflags = -1;
    switch(key.vk) {
    case(TCODK_LEFT):
        moveflags = LEFT;
        break;
    case(TCODK_RIGHT):
        moveflags = RIGHT;
        break;
    case(TCODK_UP):
        moveflags = UP;
        break;
    case(TCODK_DOWN):
        moveflags = DOWN;
        break;
    }

    // Check if our movement flag has been tripped
    if (moveflags != -1) {
        int dest[2];
        dest[0] = mainPlayer->pos[0];
        dest[1] = mainPlayer->pos[1];
		entity *enemy = NULL;
        switch(moveflags) {
        case(LEFT):
            dest[0]--;
            if ((enemy=mainPlayer->checkEntCollides(LEFT)) == 0 &&
                mainPlayer->checkStaticCollides(dest) == 0) {
                mainPlayer->pos[0]--;
            } else {
                // Testing of remove(). Works correctly.
                //mainPlayer->mapDataHandle->masterList->remove(mainPlayer->checkEntCollides(LEFT));
				attack(enemy);
                cout<<"Collision!"<<endl;
            }
            break;
        case(RIGHT):
            dest[0]++;
            if (mainPlayer->checkEntCollides(RIGHT) == 0 &&
                mainPlayer->checkStaticCollides(dest) == 0) {
                mainPlayer->pos[0]++;
            } else {
                cout<<"Collision!"<<endl;
            }
            break;
        case(UP):
            dest[1]--;
            if (mainPlayer->checkEntCollides(UP) == 0 &&
                mainPlayer->checkStaticCollides(dest) == 0) {
                mainPlayer->pos[1]--;
            }else {
                cout<<"Collision!"<<endl;
            }
            break;
        case(DOWN):
            dest[1]++;
            if (mainPlayer->checkEntCollides(DOWN) == 0 &&
                mainPlayer->checkStaticCollides(dest) == 0) {
                mainPlayer->pos[1]++;
            } else {
                cout<<"Collision!"<<endl;
            }
            break;
        }
    }
    return 0;
}
int main() {
    srand((int)time(NULL));
    cPlayer *mainPlayer = new cPlayer;
    entity *test = mainPlayer->mapDataHandle->masterList->insert();
    test->pos[0] = 24;
    test->pos[1] = 24;
    if (test == NULL) {
        return 1;
    }

    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "DAT ROGUEISH", false, TCOD_RENDERER_SDL);

    // Main loop
    while(1) {
        // See if we should be closed
        if (TCODConsole::isWindowClosed())
            break;
        
        // Render everything
        render(mainPlayer);
        
        // Handle keyboard input
        if (keyHandler(mainPlayer) == -1)
            break;
    }

    delete mainPlayer;
    return 0;
}