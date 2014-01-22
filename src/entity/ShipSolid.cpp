#include "ShipSolid.h"


ShipSolid::ShipSolid(World* world, int length, int dir, int X, int Y) : Ship(world, length, dir) {
    this->X = X;
    this->Y = Y;
    baseColor = 12;
}

ShipSolid::~ShipSolid() {
    //dtor
}

bool ShipSolid::isSolid() {
    return true;
}

void ShipSolid::update() {
}

bool ShipSolid::collidesWith(Entity* entity) {
    if (!isSolid()) {
        return false;
    }

    if (
        ((entity->getX()) >= X-1 && (entity->getX()) <= X + getWidth()+1) ||
        ((entity->getX() + entity->getWidth()) >= X-1 && (entity->getX() + entity->getWidth() ) <= X + getWidth()+1) 
    ) {
        
        if (
            ((entity->getY()) >= Y-1 && (entity->getY()) <= Y + getHeight()+1) ||
            ((entity->getY() + entity->getHeight()) >= Y-1 && (entity->getY() + entity->getHeight()) <= Y + getHeight()+1)
        ) {
            return true;
        }
    }
    

    return false;
}
