#pragma once
#include "glm/glm.hpp"	
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>

class Bullet
{
	int color;
	// Pozitia curenta a glontului "fizic"
	glm::vec3 position;
	float currentXPosition, currentRotation;
	// Offset-ul pentru punctele din vertices unde se gasesc coordonatele initiale ale unui glont generic
	static GLuint offset;
	// Numarul de puncte al unui glont generic
	static GLuint nrPoints;
	static float step, angleStep;
public:
	Bullet(int color, float xCenter, float yCenter, float zCenter = 0.f);
	// Deseneaza glontul la pozitia si rotatia curenta
	void draw();
	// Muta glontul la pozitia si rotatia curenta
	void move();
	// Seteaza offset-ul pentru punctele din vertices unde se gasesc coordonatele initiale ale unui glont generic
	static void setOffset(int offset);
	// Seteaza o noua pozitie pentru un glont "fizic"
	void setPosition(glm::vec3& newPosition);
	// Returneaza pozitia curenta a glontului "fizic"
	glm::vec3 getPosition() const;
	int getColor() const;
	// Returneaza true daca glontul este in scena, false altfel
	bool isActive() const;
	~Bullet();
};

