#include "world.h"
#include "WindowsConsole.h"

#include "ShipSolid.h"
#include "ShipPlacer.h"
#include "ShipMenu.h"
#include "IndirectConsole.h"

World::World() {
    console = new WindowsConsole();
    console->setTitle("SeaWars dev");

    addEntity(new ShipMenu(this));
}

World::~World() {
    delete console;
}

void World::addEntity(Entity* entity) {
    entitiesAdd.push_back(entity);
}

void World::removeEntity(Entity* entity) {
    std::vector<Entity*>::iterator entitiesIterator = entities.begin();

    while (entitiesIterator != entities.end()) {

        if ((*entitiesIterator) == entity) {
            entities.erase(entitiesIterator);
            break;
        }

        entitiesIterator++;
    }
}

std::vector<Entity*> World::getAllEntity() {
    return entities;
}

void World::handleAddEntity() {
    std::vector<Entity*>::iterator entitiesIterator = entitiesAdd.begin();

    while (entitiesIterator != entitiesAdd.end()) {
        entities.push_back((*entitiesIterator));
        entitiesIterator++;
    }

    entitiesAdd.clear();
}

void World::paintMap() {
    
    int x = 3;
    int y = 3;
    
    for( int i = 0; i < 24; i++ ) {
        console->write(x + i, y-1, '=', 7);
        console->write(x + i, y+14, '=', 7);
    }

    for( int i = 0; i < 14; i++ ) {
        console->write(x, y+i, '|', 7);
        console->write(x+23, y+i, '|', 7);
    }
}

void World::gameLoop() {
    running = true;

    while (running) {
        handleAddEntity();

        getKeyboard().handle();
        
        paintMap();

        update();
        render();

        console->swapBuffers();

        int l = 0;
        while (running && getKeyboard().has()) {

            char c = getKeyboard().read();
            console->write(l++, 0, c, 7);

            if (c == 'q') running = false;
        }

        //        sleep(100);
    }
}

iConsole* World::getConsole() {
    return new IndirectConsole(console, 4, 3, 22, 14);
}

InputKeyboard& World::getKeyboard() {
    return keyboard;
}

void World::update() {
    std::vector<Entity*>::reverse_iterator entitiesIterator = entities.rbegin();

    while (entitiesIterator != entities.rend()) {
        (*entitiesIterator)->update();
        ++entitiesIterator;
    }
}

void World::render() {
    std::vector<Entity*>::reverse_iterator entitiesIterator = entities.rbegin();

    while (entitiesIterator != entities.rend()) {
        Entity* e = (*entitiesIterator);
        e->render();
        ++entitiesIterator;
    }
}
