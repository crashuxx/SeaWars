/* 
 * File:   Message.cpp
 * Author: c
 * 
 * Created on 22 styczeń 2014, 21:45
 */

#include <string>

#include "Message.h"
#include "world.h"

Message::Message(World* world, const char *msg) : Entity(), text(msg) {
    this->world = world;
}

Message::~Message() {
}

int Message::getX() {
    return 0 - (text.size() / 2) - 2;
}

int Message::getY() {
    return 0;
}

int Message::getWidth() {
    return text.size() + 2;
}

int Message::getHeight() {
    return 3;
}

void Message::update() {

    if (world->getKeyboard()->has()) {
        world->getKeyboard()->clear();
        world->removeEntity(this);
        delete this;
    }
}

void Message::render() {

    iConsole* c = world->getMessageConsole();
    
    int size = text.size()+4;
    
    int x = (c->getWidth()/2)-(size/2);
    int y = (c->getHeight()/2)-1;

    for (int i = -1; i < size+1; i++) {
        c->write(x + i, y - 1, '-', 26);
        c->write(x + i, y, ' ', 26);
        c->write(x + i, y + 1, '-', 26);
    }

    c->write(x - 1, y, '|', 28);
    c->write(x + size, y, '|', 28);
    c->writeString(x+1, y, text, 31);
    
    delete c;
}

bool Message::isSolid() {
    return false;
}

bool Message::collidesWith(Entity* entity) {
    return false;
}

