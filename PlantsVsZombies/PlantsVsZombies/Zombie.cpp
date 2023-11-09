#include "Zombie.h"
#include "Shared.h"

Zombie::Zombie(int color, float xCenter, float yCenter, float zCenter): 
	GenericNPC(color, xCenter, yCenter, zCenter) {
	currentXPosition = xCenter;
}

Zombie::Zombie() {};

GLuint Zombie::nrPoints = 12;

GLuint Zombie::offset = 0;

int Zombie::interiorColor = DARK_GREEN;

float Zombie::step = 0.05f;

void Zombie::draw() {
	// Construim matricea de translatie pentru desenarea zombie-ului "fizic" mutat la coordonatele specificate
	glm::mat4 translateMatrix = glm::translate(this->getPosition());
	glm::mat4 myMatrix = Shared::resizeMatrix * translateMatrix;
	// Transmitem catre shader matricea de translatie si culoarea exterioara a zombie-ului
	glUniformMatrix4fv(Shared::myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(Shared::codColLocation, this->getColor());
	glDrawArrays(GL_POLYGON, offset, nrPoints / 2);
	// Transmitem catre shader culoarea interioara a zombie-ului
	glUniform1i(Shared::codColLocation, interiorColor);
	glDrawArrays(GL_POLYGON, offset + nrPoints / 2, nrPoints / 2);
}

void Zombie::move() {
	// Setam noua coordonata x a zombie-ului 
	this->currentXPosition -= step*Shared::render_duration;
	glm::vec3 newPosition = glm::vec3(this->currentXPosition, this->getPosition().y, this->getPosition().z);
	this->setPosition(newPosition);
}

void Zombie::setOffset(int offset) {
	Zombie::offset = offset;
}

bool Zombie::isActive() const {
	return this->getPosition().x > 50.f;
}

Zombie::~Zombie() {}

void Zombie::loadVertices(GLfloat Vertices[], int& poz) {
	float rBig = 40.f, rSmall = 25.f;
	const int n = 6;

	// Punctele pentru exterior
	for (int k = 0; k < n; ++k) {
		float angle = 2 * k * Shared::PI / n;
		GLfloat x = rBig * cos(angle), y = rBig * sin(angle);
		Vertices[++poz] = x;
		Vertices[++poz] = y;
		Vertices[++poz] = 1.0f; // 1.0f pentru a fi desenat deasupra
		Vertices[++poz] = 1.0f;
	}

	// Punctele pentru interior
	for (int k = 0; k < n; ++k) {
		float angle = 2 * k * Shared::PI / n;
		GLfloat x = rSmall * cos(angle), y = rSmall * sin(angle);
		Vertices[++poz] = x;
		Vertices[++poz] = y;
		Vertices[++poz] = 1.0f; // 1.0f pentru a fi desenat deasupra
		Vertices[++poz] = 1.0f;
	}
}

void Zombie::setKiller() {
	this->killer = true;
}

bool Zombie::isKiller() {
	return this->killer;
}