#include "main.h"
using namespace std;

// Don't change these. My code isn't as modular as it looks.
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 50

// CONSTRUCTORS AND CLASS FUNCTIONS
cPlayer::cPlayer() {
    mapDataHandle = new mapData();
    myColor = TCODColor::white;
    int i;
    for (i=0;i<2;i++) {
        pos[i] = 1;
        cell[i] = 0;
    }
}

cPlayer::~cPlayer() {
    delete mapDataHandle;
}

mapData::mapData() {
    int i,j;
    for (i=0;i<SCREEN_WIDTH;i++) {
        for (j=0;j<SCREEN_HEIGHT;j++) {
            // Set the default char to whatever the fuck
            int test = (rand() % 3);
            if (test == 0)
                mapHandlerMaster[i][j] = '.';
            else if (test == 1)
                mapHandlerMaster[i][j] = ',';
            else if (test == 2)
                mapHandlerMaster[i][j] = ' ';
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

int main() {
    srand((int)time(NULL));
    cPlayer *mainPlayer = new cPlayer;
    entity *test = mainPlayer->mapDataHandle->masterList->insert();
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
        
        // Get keypresses
        TCOD_key_t key = TCODConsole::waitForKeypress(true);
        if (key.vk == TCODK_ESCAPE)
            break;
        if (key.vk == TCODK_LEFT)
            mainPlayer->pos[0]--;
        if (key.vk == TCODK_RIGHT)
            mainPlayer->pos[0]++;
        if (key.vk == TCODK_UP)
            mainPlayer->pos[1]--;
        if (key.vk == TCODK_DOWN)
            mainPlayer->pos[1]++;
    }

    delete mainPlayer;
    return 0;
}