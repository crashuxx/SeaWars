#include "Ship.h"

Ship::Ship(World* world, int length, int dir)  : Entity()
{
    this->length = length;
    this->world = world;
    this->dir = dir;
    
    baseColor = 14;
}

Ship::~Ship()
{
    //dtor
}

bool Ship::isSolid() {
    return false;
}

void Ship::render()
{
    for( int i = 0; i < length; i++ )
    {
        world->getConsole()->write( (isHorizontal() ? i : 0) + getX() , (!isHorizontal() ? i : 0) + getY(), 'o', baseColor);
    }
}

bool Ship::collidesWith(Entity* entity)
{
    return false;
}

bool Ship::isHorizontal()
{
    return (dir == 0);
}

int Ship::getX()     { return X; }
int Ship::getY()     { return Y; }

int Ship::getWidth()
{
    return isHorizontal() ? length-1 : 0;
}

int Ship::getHeight()
{
    return isHorizontal() ? 0 : length-1;
}
