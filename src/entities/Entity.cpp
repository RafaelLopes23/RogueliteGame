#include "entities/Entity.h"

Entity::Entity(float x, float y, const std::string& name) 
    : x(x), y(y), width(32), height(32), name(name) {
}

Entity::~Entity() {
}

void Entity::update() {
    // Default update behavior - can be overridden
}

void Entity::render() {
    // Default render behavior - can be overridden
}

bool Entity::checkCollision(const Entity* other) const {
	return (x < other->x + other->width &&
		x + width > other->x &&
		y < other->y + other->height &&
		y + height > other->y);
}
    