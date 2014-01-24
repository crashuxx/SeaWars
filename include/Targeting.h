/* 
 * File:   Targeting.h
 * Author: c
 *
 * Created on 24 styczeń 2014, 09:26
 */

#ifndef TARGETING_H
#define	TARGETING_H

#include "Entity.h"
#include "world.h"

class Targeting : public Entity {
public:
    Targeting(World*);
    ~Targeting();
    
    void enable();
    
    void update();
    void render();

    bool collidesWith(Entity* entity);
private:
    bool enabled;
    World* world;
};

#endif	/* TARGETING_H */

