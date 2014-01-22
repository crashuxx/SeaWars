#ifndef ASHIPMENU_H
#define ASHIPMENU_H

#include "Entity.h"
#include "world.h"


class ShipMenu : public Entity
{
    public:
        ShipMenu(World*);
        ~ShipMenu();

        void update();
        void render();
        
        void enable();
        bool isSolid();

        bool collidesWith(Entity* entity);
    protected:
    private:
        World *world;
        int pos;
        
        int m[4];
        bool enabled;
};

#endif // ASHIPMENU_H
