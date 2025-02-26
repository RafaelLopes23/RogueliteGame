#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
public:
    Entity(float x, float y, const std::string& name);
    virtual ~Entity();
    
    virtual void update();
    virtual void render(); // In a real implementation, would take a renderer param
    
    float getX() const { return x; }
    float getY() const { return y; }
    void setPosition(float newX, float newY);
    
protected:
    float x, y;
    std::string name;
};

#endif // ENTITY_H