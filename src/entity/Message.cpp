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
    return 22 / 2 - (text.size() / 2) - 2;
}

int Message::getY() {
    return 14 / 2 - 1;
}

int Message::getWidth() {
    return text.size() + 2;
}

int Message::getHeight() {
    return 3;
}

void Message::update() {

    if (world->getKeyboard().has()) {
        world->getKeyboard().clear();
        world->removeEntity(this);
        delete this;
    }
}

void Message::render() {

    iConsole* c = world->getConsole();

    int size = text.size();
    for (int i = -1; i <= size + 1; i++) {
        c->write(getX() + i, getY() - 1, '-', 26);
        c->write(getX() + i, getY(), ' ', 26);
        c->write(getX() + i, getY() + 1, '-', 26);
    }

    c->write(getX() - 1, getY(), '|', 28);
    c->write(getX() + size + 1, getY(), '|', 28);
    c->writeString(getX(), getY(), text, 31);
}

bool Message::isSolid() {
    return false;
}

bool Message::collidesWith(Entity* entity) {
    return false;
}

