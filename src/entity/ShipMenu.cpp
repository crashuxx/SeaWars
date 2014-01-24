#include "ShipMenu.h"
#include "ShipPlacer.h"
#include "ShipSolid.h"
#include <string>

ShipMenu::ShipMenu(World* world) {
    this->world = world;
    pos = 0;
    enabled = true;

    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
}

ShipMenu::~ShipMenu() {

}

bool ShipMenu::isSolid() {
    return false;
}

void ShipMenu::update() {
    if (!enabled) {
        return;
    }
    
    bool all = true;
    for(int i=0 ; i < 4; i++) {
        if(m[i] > 0) all = false;
    }
    
    if( all ) {
        enabled = false;
        world->ready();
        return;
    }

    if (world->getKeyboard()->fetch('w') || world->getKeyboard()->fetch('W')) {
        if ((pos - 1) >= 0) pos--;
    }

    if (world->getKeyboard()->fetch('s') || world->getKeyboard()->fetch('S')) {
        if ((pos + 1) <= 3) pos++;
    }

    if (world->getKeyboard()->fetch(0x0D) && m[pos] > 0) {
        ShipPlacer* ship = new ShipPlacer(world, 4 - pos, 0, this);
        //        world->removeEntity(this);
        world->addEntity(ship);
        enabled = false;
        m[pos]--;
    }
}

void ShipMenu::render() {
    if (!enabled) {
        return;
    }
    
    iConsole* c = world->getMessageConsole();
    
    int size = 16 + 2;
    int x = (c->getWidth()/2)-(size/2);
    int y = (c->getHeight()/2)-(4/2)-1;

    for (int i = 0; i < size; i++) {
        c->write(x + i, y, '=', 10);
        c->write(x + i, y+5, '=', 10);
    }

    for (int i = 1; i < 5; i++) {
        c->write(x, y + i, '|', 10);
        c->write(x+size-1, y + i, '|', 10);
    }

    std::string blank("                ");

    std::string mast4(" 4-masztowy     ");
    c->writeString(x+1, y + 1, m[0] > 0 ? mast4 : blank, pos == 0 ? 27 : 12);

    std::string mast3(" 3-masztowy     ");
    c->writeString(x+1, y + 2, m[1] > 0 ? mast3 : blank, pos == 1 ? 27 : 12);

    std::string mast2(" 2-masztowy     ");
    c->writeString(x+1, y + 3, m[2] > 0 ? mast2 : blank, pos == 2 ? 27 : 12);

    std::string mast1(" 1-masztowy     ");
    c->writeString(x+1, y + 4, m[3] > 0 ? mast1 : blank, pos == 3 ? 27 : 12);
    
    delete c;
}

void ShipMenu::enable() {
    enabled = true;
}

bool ShipMenu::collidesWith(Entity* entity) {
    return false;
}
