#include "Bullet.h"
#include "Shared.h"

GLuint Bullet::nrPoints = 10;

GLuint Bullet::offset = 0;

float Bullet::step = 0.3f;

float Bullet::angleStep = -0.001f;

Bullet::Bullet(int color, float xCenter, float yCenter, float zCenter) {
	this->position = glm::vec3(xCenter, yCenter, zCenter);
	this->color = color;
	this->currentXPosition = xCenter;
	this->currentRotation = 0.f;
}

void Bullet::setOffset(int offset) {
	Bullet::offset = offset;
}

void Bullet::draw() {
	glm::mat4 translateMatrix = glm::translate(this->getPosition());
	glm::mat4 rotateMatrix = glm::rotate(this->currentRotation, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 myMatrix = Shared::resizeMatrix * translateMatrix * rotateMatrix;
	glUniformMatrix4fv(Shared::myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(Shared::codColLocation, this->getColor());
	glDrawArrays(GL_POLYGON, offset, nrPoints);
}

void Bullet::move() {
	this->currentXPosition += this->step * Shared::render_duration;
	this->currentRotation += this->angleStep;
	glm::vec3 newPosition = glm::vec3(this->currentXPosition, this->getPosition().y, this->getPosition().z);
	this->setPosition(newPosition);
}

void Bullet::setPosition(glm::vec3& newPosition) {
	this->position = newPosition;
}	

glm::vec3 Bullet::getPosition() const {
	return this->position;
}

int Bullet::getColor() const {
	return this->color;
}

bool Bullet::isActive() const {
	return this->getPosition().x < Shared::winWidth + 50.f;
}

Bullet::~Bullet() {}
