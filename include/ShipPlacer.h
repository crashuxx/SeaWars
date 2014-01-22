#ifndef PLACESHIP_H
#define PLACESHIP_H

#include "Message.h"
#include "ShipMenu.h"
#include "Ship.h"

class ShipPlacer : public Ship
{
    public:
        ShipPlacer(World*, int, int, ShipMenu*);
        ~ShipPlacer();

        void update();
    protected:
        bool checkColision();
        ShipMenu* menu;
    private:
};

#endif // PLACESHIP_H
