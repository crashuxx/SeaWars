/* 
 * File:   Targeting.cpp
 * Author: c
 * 
 * Created on 24 styczeń 2014, 09:26
 */

#include "Targeting.h"
#include "mem.h"

Targeting::Targeting(World* world) : Entity() {
    this->world = world;
    enabled = false;
}

Targeting::~Targeting() {
}

void Targeting::enable() {
    enabled = true;
}

void Targeting::update() {
    if(!enabled) return;
    
    if (world->getKeyboard()->fetch('a') || world->getKeyboard()->fetch('A')) {
        if ((X - 1) >= 0) X--;
    }

    if (world->getKeyboard()->fetch('d') || world->getKeyboard()->fetch('D')) {
        if ((X + 1) < 22) X++;
    }

    if (world->getKeyboard()->fetch('w') || world->getKeyboard()->fetch('W')) {
        if ((Y - 1) >= 0) Y--;
    }

    if (world->getKeyboard()->fetch('s') || world->getKeyboard()->fetch('S')) {
        if ((Y + 1) < 14) Y++;
    }
    
    bool colidate = world->checkSpot(X,Y);

    if (world->getKeyboard()->fetch(0x0D)) {
        
        if( !colidate ) {
            world->hitSpot(X,Y);
            world->giveControlToEnemy();
            enabled = false;
        }
    }
}

void Targeting::render() {
    if(!enabled) return;
    iConsole* c = world->getRightSheetConsole();
    c->write(X,Y, 'X', 62);
    delete c;
}

bool Targeting::collidesWith(Entity* entity) {
    return false;
}
