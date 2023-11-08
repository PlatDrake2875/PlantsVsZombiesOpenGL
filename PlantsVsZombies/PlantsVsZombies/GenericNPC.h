#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  
class GenericNPC
{
	glm::vec3 position;
	float health;
protected:	int color;
public:
	// xCenter, yCenter, zCenter - coordonatele centrului obiectului
	GenericNPC(int color, float xCenter, float yCenter, float zCenter = 0.f);
	GenericNPC();
	void setHealth(float& health);
	void setPosition(glm::vec3& newPosition);
	float getHealth() const;
	glm::vec3 getPosition() const;
	int getColor() const;
	virtual void draw() = 0;
	virtual void loadVertices(GLfloat Vertices[], int& poz) = 0;
	virtual ~GenericNPC() = 0;
};

