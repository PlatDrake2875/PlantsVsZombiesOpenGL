#include "Plant.h"
#include "Shared.h"

GLuint Plant::nrPoints = 7;
GLuint Plant::offset = 0;

Plant::Plant(int color, float xCenter, float yCenter, float zCenter): 
	GenericNPC(color, xCenter, yCenter, zCenter) {}

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

Plant::~Plant() {}
