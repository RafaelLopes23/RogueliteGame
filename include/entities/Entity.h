#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
public:
    Entity(float x, float y, const std::string& name);
    virtual ~Entity();
    
    virtual void update();
    virtual void render();
    
    float getX() const { return x; }
    float getY() const { return y; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }

    bool checkCollision(const Entity* other) const;
    
protected:
    float x, y;
    std::string name;
	float width, height;
};

#endif // ENTITY_H