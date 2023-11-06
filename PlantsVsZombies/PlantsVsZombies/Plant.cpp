#include "Plant.h"
#include "Shared.h"

GLuint Plant::nrPoints = 7;
GLuint Plant::offset = 0;

Plant::Plant(int color, float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
	this->health = 100.f;
	this->color = color;
}

void Plant::setHealth(float health) {
	this->health = health;
}

float Plant::getHealth() {
	return this->health;
}

glm::vec3 Plant::getPosition() {
	return this->position;
}

int Plant::getColor() {
	return this->color;
}

void Plant::draw() {
	glm::mat4 translateMatrix = glm::translate(this->position);
	glm::mat4 myMatrix = Shared::resizeMatrix * translateMatrix;
	glUniformMatrix4fv(Shared::myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(Shared::codColLocation, this->color);
	//glDrawElements(GL_POLYGON, nrPoints, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	glDrawArrays(GL_POLYGON, offset, nrPoints);
}


Plant::~Plant() {

}