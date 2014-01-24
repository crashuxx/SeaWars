#ifndef WORLD_H
#define WORLD_H

#include "iConsole.h"
#include "InputKeyboard.h"
#include "Entity.h"
#include "Net.h"

#include <vector>

class World
{
    public:
        World(iConsole*);
        ~World();

        void gameLoop();

        iConsole* getLeftSheetConsole();
        iConsole* getRightSheetConsole();
        InputKeyboard* getKeyboard();
        
        iConsole* getMessageConsole();

        void addEntity(Entity*);
        void removeEntity(Entity*);
        
        std::vector<Entity*> getAllEntity();
        
        void hitSpot(int x, int y);
        bool checkSpot(int x, int y);
                
        void ready();
        
        void giveControlToEnemy();

    protected:
    private:
        Net& getNet();
        
        int imReady;
        int enemyReady;
        
        void handleAddEntity();
        
        void handleNetwork();
        void handleNetCommands(std::vector<std::string>&);
        
        void update();
        void render();
        void paintMap(iConsole& c);
        void paintHitSpots();

        bool running;

        std::vector<Entity*> entities;
        
        std::vector<Entity*> entitiesAdd;
        
        char hitSpotsMap[22][14];
        iConsole* console;
        InputKeyboard keyboard;
        
        Net* net;
        
        Entity* targeting;
        int move;
        
        void ignition();
};

#endif // WORLD_H
