#include "world.h"
#include "ShipSolid.h"
#include "ShipPlacer.h"
#include "ShipMenu.h"
#include "output/IndirectConsole.h"
#include "Targeting.h"

#include <windows.h>
#include <sstream>
#include <iterator>

#include <time.h>

World::World(iConsole* con) {

    net = Net::factory();

    console = con;
    memset(&hitSpotsMap, 0, sizeof (char)*22 * 14);

    addEntity(new ShipMenu(this));

    imReady = 0;
    enemyReady = 0;

    targeting = new Targeting(this);
    addEntity(targeting);
    
    move = 0;
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
        c.write(0, 1 + i, '|', 7);
        c.write(23, 1 + i, '|', 7);
    }
}

void World::handleNetwork() {
    net->handle();

    std::string* cmd;
    while ((cmd = net->getCommand())) {

        std::stringstream ss(*cmd);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);

        handleNetCommands(vstrings);

        std::vector<std::string>::iterator it = vstrings.begin();

        delete cmd;
    }
}

void World::handleNetCommands(std::vector<std::string>& cmdTokens) {

    if (cmdTokens.size() <= 0) {
        return;
    }

    std::string cmd = cmdTokens.at(0);
    
    const char* cc = cmd.c_str();

    if (cmd.compare("you") == 0) {
        move = 1;
        ((Targeting*)targeting)->enable();
        
    } else if (cmd.compare("ready") == 0) {
        enemyReady = time(0);
    } else if (cmd.compare("h") == 0) {
        if (cmdTokens.size() == 3) {
            int x = atoi(cmdTokens.at(1).c_str());
            int y = atoi(cmdTokens.at(2).c_str());
            hitSpotsMap[x][y] = 2;
        }
    } else {
        if (cmd.compare("t") == 0) {
            if (cmdTokens.size() == 3) {
                int x = atoi(cmdTokens.at(1).c_str());
                int y = atoi(cmdTokens.at(2).c_str());

                std::vector<Entity*>::iterator entitiesIterator = entities.begin();
                while (entitiesIterator != entities.end()) {
                    Entity* e = (*entitiesIterator);
                    if (e->getType() == Entity::SHIP) {

                        if (((ShipSolid*) e)->hit(x, y) > 0) {
                            std::stringstream msg;
                            msg << "h " << x << " " << y << "\r\n";

                            std::string smsg = msg.str();
                            net->write(smsg);
                        }
                    }

                    ++entitiesIterator;
                }
            }
        }
    }

}

void World::giveControlToEnemy() {
    
    if (move == 1) {
        std::string ready("you\r\n");
        getNet().write(ready);

        move = -1;
    }
}

void World::ignition() {

    if (move == 0 && imReady && enemyReady) {

        if( (imReady < enemyReady) ) {
            move = 1;
            ((Targeting*)targeting)->enable();
        } else {
            move = -1;
        }
    }
}

void World::gameLoop() {
    running = true;

    while (running) {

        ignition();

        handleAddEntity();
        handleNetwork();

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
    return new IndirectConsole(console, 3, 2, 22 + 8 + 22 + 4, 16);
}

InputKeyboard* World::getKeyboard() {
    return &keyboard;
}

Net& World::getNet() {
    return *net;
}

void World::ready() {
    if (imReady == 0) {
        std::string ready("ready\r\n");
        getNet().write(ready);
        imReady = time(0);
    }
}

void World::update() {
    std::vector<Entity*>::reverse_iterator entitiesIterator = entities.rbegin();

    while (entitiesIterator != entities.rend()) {
        (*entitiesIterator)->update();
        ++entitiesIterator;
    }
}

void World::paintHitSpots() {
    iConsole* c = getRightSheetConsole();
    for (int x = 0; x < 22; x++) {
        for (int y = 0; y < 14; y++) {

            if (hitSpotsMap[x][y] == 1) {
                c->write(x, y, ' ', 58);
            }

            if (hitSpotsMap[x][y] == 2) {
                c->write(x, y, 'O', 58);
            }
        }
    }

    delete c;
}

void World::render() {

    IndirectConsole* con = new IndirectConsole(console, 3, 2, 24, 16);
    paintMap((*con));
    delete con;

    con = new IndirectConsole(console, 3 + 8 + 24, 2, 24, 16);
    paintMap((*con));
    delete con;

    paintHitSpots();

    std::vector<Entity*>::iterator entitiesIterator = entities.begin();

    while (entitiesIterator != entities.end()) {
        Entity* e = (*entitiesIterator);
        e->render();
        ++entitiesIterator;
    }
}

void World::hitSpot(int x, int y) {

    if (x >= 22 || y >= 14 || x < 0 || y < 0) {
        return;
    }

    hitSpotsMap[x][y] = 1;
    
    std::stringstream msg;
    msg << "t " << x << " " << y << "\r\n";

    std::string smsg = msg.str();
    net->write(smsg);
}

bool World::checkSpot(int x, int y) {

    if (x >= 22 || y >= 14 || x < 0 || y < 0) {
        return false;
    }

    return (hitSpotsMap[x][y] > 0);
}