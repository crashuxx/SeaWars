#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "world.h"


class Ship : public Entity
{
    public:
        /** Default constructor */
        Ship(World*, int, int);
        /** Default destructor */
        ~Ship();

        void render();

        bool isHorizontal();

        int getX();
        int getY();

        int getWidth();
        int getHeight();
        
        bool isSolid();

        bool collidesWith(Entity* entity);
    protected:
        World *world;
        int length;
        int dir;
        int baseColor;
    private:
};

#endif // SHIP_H
