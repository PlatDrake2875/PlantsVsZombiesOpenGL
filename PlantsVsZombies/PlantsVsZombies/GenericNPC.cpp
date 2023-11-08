#include "GenericNPC.h"


GenericNPC::GenericNPC(int color, float xCenter, float yCenter, float zCenter) {
	this->position = glm::vec3(xCenter, yCenter, zCenter);
	this->health = 100.f;
	this->color = color;
}

void GenericNPC::setHealth(float& health) {
	this->health = health;
}

void GenericNPC::setPosition(glm::vec3& newPosition) {
	this->position = newPosition;
}

float GenericNPC::getHealth() const {
	return this->health;
}

glm::vec3 GenericNPC::getPosition() const {
	return this->position;
}

int GenericNPC::getColor() const {
	return this->color;
}

GenericNPC::~GenericNPC() {}