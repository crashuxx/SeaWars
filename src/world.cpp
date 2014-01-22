#include "world.h"
#include "ShipSolid.h"
#include "ShipPlacer.h"
#include "ShipMenu.h"
#include "output/IndirectConsole.h"

#include <windows.h>

World::World(iConsole* con) {
    console = con;
    addEntity(new ShipMenu(this));
//    addEntity(new Message(this, "Witaj!"));
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

void World::paintMap(iConsole& c) {

    for (int i = 0; i < 24; i++) {
        c.write(i, 0, '=', 7);
        c.write(i, 15, '=', 7);
    }

    for (int i = 0; i < 14; i++) {
        c.write(0, 1+i, '|', 7);
        c.write(23, 1+i, '|', 7);
    }
}

void World::gameLoop() {
    running = true;

    while (running) {
        handleAddEntity();

        getKeyboard()->handle();

        update();
        render();

        console->swapBuffers();

        int l = 0;
        while (running && getKeyboard()->has()) {

            char c = getKeyboard()->read();
            console->write(l++, 0, c, 7);

            if (c == 'q') running = false;
        }

        Sleep(50);
    }
}

iConsole* World::getLeftSheetConsole() {
    return new IndirectConsole(console, 4, 3, 22, 14);
}

iConsole* World::getRightSheetConsole() {
    return new IndirectConsole(console, 36, 3, 22, 14);
}

iConsole* World::getMessageConsole() {
    return new IndirectConsole(console, 3, 2, 22+8+22+4, 16);
}

InputKeyboard* World::getKeyboard() {
    return &keyboard;
}

void World::update() {
    std::vector<Entity*>::reverse_iterator entitiesIterator = entities.rbegin();

    while (entitiesIterator != entities.rend()) {
        (*entitiesIterator)->update();
        ++entitiesIterator;
    }
}

void World::render() {
    
    IndirectConsole* con = new IndirectConsole(console, 3, 2, 24, 16);
    paintMap((*con));
    delete con;

    con = new IndirectConsole(console, 3 + 8 + 24, 2, 24, 16);
    paintMap((*con));
    delete con;
    
    std::vector<Entity*>::iterator entitiesIterator = entities.begin();

    while (entitiesIterator != entities.end()) {
        Entity* e = (*entitiesIterator);
        e->render();
        ++entitiesIterator;
    }
}
