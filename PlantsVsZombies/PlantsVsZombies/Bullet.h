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
	glm::vec3 position;
	float currentXPosition, currentRotation;
	static GLuint offset;
	static GLuint nrPoints;
	static float step, angleStep;
public:
	Bullet(int color, float xCenter, float yCenter, float zCenter = 0.f);
	void draw();
	void move();
	static void setOffset(int offset);
	void setPosition(glm::vec3& newPosition);
	glm::vec3 getPosition() const;
	int getColor() const;
	bool isActive() const;
	~Bullet();
};

