#include "Entity.h"

Entity::Entity()
{
    X = 0;
    Y = 0;
    width = 0;
    height = 0;
    type = Entity::NONE;
}

Entity::etype Entity::getType() {
    return type;
}

int Entity::getX()     { return X; }
int Entity::getY()     { return Y; }
int Entity::getWidth()  { return width; }
int Entity::getHeight() { return height; }
