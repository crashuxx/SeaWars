#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "Ship.h"

class ShipSolid : public Ship
{
    public:
        ShipSolid(World*, int, int, int, int);
        ~ShipSolid();
        
        void update();
        
        bool isSolid();
        
        bool collidesWith(Entity* entity);
    protected:
    private:
};

#endif // PLAYERSHIP_H
