#include "ShipPlacer.h"
#include "ShipSolid.h"

ShipPlacer::ShipPlacer(World* world, int length, int dir, ShipMenu* menu) : Ship(world, length, dir) {
    this->menu = menu;
}

ShipPlacer::~ShipPlacer() {
}

bool ShipPlacer::checkColision() {

    std::vector<Entity*> entityList = world->getAllEntity();
    std::vector<Entity*>::iterator it = entityList.begin();

    while (it != entityList.end()) {

        if ((*it) != this) {
        
            if( (*it)->collidesWith(this) ) {
                return true;
            }
        }
        it++;
    }
    
    return false;
}

void ShipPlacer::update() {
    if (world->getKeyboard()->fetch('a') || world->getKeyboard()->fetch('A')) {
        if ((X - 1) >= 0) X--;
    }

    if (world->getKeyboard()->fetch('d') || world->getKeyboard()->fetch('D')) {
        if ((X + 1) < 22 - getWidth()) X++;
    }

    if (world->getKeyboard()->fetch('w') || world->getKeyboard()->fetch('W')) {
        if ((Y - 1) >= 0) Y--;
    }

    if (world->getKeyboard()->fetch('s') || world->getKeyboard()->fetch('S')) {
        if ((Y + 1) < 14 - getHeight()) Y++;
    }

    if (world->getKeyboard()->fetch(0x20)) {
        dir = !dir;

        if (isHorizontal() && X + getWidth() >= 22) {
            X = X - (X + getWidth() - 22);
        }

        if (!isHorizontal() && Y + getHeight() >= 14) {
            Y = Y - (Y + getHeight() - 14);
        }
    }
    
    bool colidate = checkColision();
    baseColor = colidate ? 0x5D : 0x0E;

    if (world->getKeyboard()->fetch(0x0D)) {
        
        if( !colidate ) {
            ShipSolid* ship = new ShipSolid(world, length, dir, X, Y);
            world->removeEntity(this);
            world->addEntity(ship);
            menu->enable();

            delete this;
        } else {
            Message* msg = new Message(world, "Kolizja!");
            world->addEntity(msg);
        }
    }
}
