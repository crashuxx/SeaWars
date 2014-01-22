#include "ShipMenu.h"
#include "ShipPlacer.h"
#include "ShipSolid.h"
#include <string>

ShipMenu::ShipMenu(World* world) {
    this->world = world;
    pos = 0;
    enabled = true;

    m[0] = 1;
    m[1] = 2;
    m[2] = 3;
    m[3] = 4;
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

    for (int i = 0; i < 18; i++) {
        world->getConsole()->write(2 + i, 4, '=', 10);
        world->getConsole()->write(2 + i, 9, '=', 10);
    }

    for (int i = 1; i <= 4; i++) {
        world->getConsole()->write(2, 4 + i, '|', 10);
        world->getConsole()->write(19, 4 + i, '|', 10);
    }

    std::string blank("                ");

    std::string mast4(" 4-masztowy     ");
    world->getConsole()->writeString(3, 4 + 1, m[0] > 0 ? mast4 : blank, pos == 0 ? 27 : 12);

    std::string mast3(" 3-masztowy     ");
    world->getConsole()->writeString(3, 4 + 2, m[1] > 0 ? mast3 : blank, pos == 1 ? 27 : 12);

    std::string mast2(" 2-masztowy     ");
    world->getConsole()->writeString(3, 4 + 3, m[2] > 0 ? mast2 : blank, pos == 2 ? 27 : 12);

    std::string mast1(" 1-masztowy     ");
    world->getConsole()->writeString(3, 4 + 4, m[3] > 0 ? mast1 : blank, pos == 3 ? 27 : 12);
}

void ShipMenu::enable() {
    enabled = true;

    bool empty = true;
    for (int i = 0; i < 4; i++) {
        if (m[i] > 0) empty = false;
    }
    
    if( empty ) {
        world->removeEntity(this);
        delete this;
    }
}

bool ShipMenu::collidesWith(Entity* entity) {
    return false;
}
