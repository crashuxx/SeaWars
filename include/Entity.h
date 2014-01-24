#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        enum etype {NONE, SHIP}; 
        
        virtual ~Entity() {};

        virtual int getX();
        virtual int getY();
        virtual int getWidth();
        virtual int getHeight();

        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool collidesWith(Entity* entity) = 0;
        
        Entity::etype getType();

    protected:
        Entity();
        
        Entity::etype type;

        int X;
        int Y;
        int width;
        int height;

    private:
};

#endif // ENTITY_H
