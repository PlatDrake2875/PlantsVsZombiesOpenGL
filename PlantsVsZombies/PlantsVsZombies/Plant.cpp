#include "Plant.h"
#include "Shared.h"
#include <iostream>

GLuint Plant::nrPoints = 7;
GLuint Plant::offset = 0;

Plant::Plant(int color, float xCenter, float yCenter, float zCenter): 
	GenericNPC(color, xCenter, yCenter, zCenter) {}

Plant::Plant(float xCenter, float yCenter, float zCenter) :
	GenericNPC(xCenter, yCenter, zCenter) {}


void Plant::draw() {
	glm::mat4 translateMatrix = glm::translate(this->getPosition());
	glm::mat4 myMatrix = Shared::resizeMatrix * translateMatrix;
	glUniformMatrix4fv(Shared::myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(Shared::codColLocation, this->getColor());
	//glDrawElements(GL_POLYGON, nrPoints, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	glDrawArrays(GL_POLYGON, offset, nrPoints);
}

void Plant::setOffset(int offset) {
	Plant::offset = offset;
}

void Plant::setColor(int color) {
	this->color = color;
}

void Plant::toString() {
	std::cout << "Plant: " << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << " " << this->getColor() << "\n";
}

Plant::~Plant() {}

void Plant::loadVertices(GLfloat Vertices[], int& poz) {
	float x = this->getPosition().x;
	float y = this->getPosition().y;

	Vertices[++poz] = x + 25.f;
	Vertices[++poz] = y + 50.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 50.f;
	Vertices[++poz] = y + 0.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 75.f;
	Vertices[++poz] = y + 33.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 100.f;
	Vertices[++poz] = y + 33.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 100.f;
	Vertices[++poz] = y + 67.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 75.f;
	Vertices[++poz] = y + 67.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 50.f;
	Vertices[++poz] = y + 100.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;
}

int Plant::getPrice() const {
	switch (this->color)
	{
	case Colors::MAGENTA:
		return 1;
	case Colors::YELLOW:
		return 2;
	case Colors::CYAN:
		return 3;
	case Colors::ORANGE:
		return 4;
	default:
		return 1;
	}
}
