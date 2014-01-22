/* 
 * File:   Message.h
 * Author: c
 *
 * Created on 22 styczeń 2014, 21:45
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "world.h"
#include "Entity.h"

class Message : public Entity {
public:
    Message(World*, const char *);
    ~Message();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void update();
    void render();
    bool isSolid();

    bool collidesWith(Entity* entity);
private:
    std::string text;
    World* world;
};

#endif	/* MESSAGE_H */

