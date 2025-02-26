#include "entities/Entity.h"

Entity::Entity(float x, float y, const std::string& name) 
    : x(x), y(y), name(name) {
}

Entity::~Entity() {
}

void Entity::update() {
    // Default update behavior - can be overridden
}

void Entity::render() {
    // Default render behavior - can be overridden
}

void Entity::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}