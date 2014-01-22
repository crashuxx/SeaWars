#ifndef WORLD_H
#define WORLD_H

#include "iConsole.h"
#include "InputKeyboard.h"
#include "Entity.h"

#include <vector>

class World
{
    public:
        World();
        ~World();

        void gameLoop();

        iConsole* getConsole();
        InputKeyboard &getKeyboard();

        void addEntity(Entity*);
        void removeEntity(Entity*);
        
        std::vector<Entity*> getAllEntity();

    protected:
    private:
        void handleAddEntity();
        void update();
        void render();
        void paintMap();

        bool running;

        std::vector<Entity*> entities;
        
        std::vector<Entity*> entitiesAdd;
        
        iConsole* console;
        InputKeyboard keyboard;
};

#endif // WORLD_H