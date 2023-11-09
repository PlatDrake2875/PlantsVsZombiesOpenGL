#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  

// Clasa Generica din care mostenesc Plant si Zombie
class GenericNPC
{
	glm::vec3 position;
	float health = 0.f;
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
	// Functie care deseneaza obiectul si este definita in clasele Plant si Zombie
	virtual void draw() = 0;
	// Functie care seteaza coordonatele varfurilor pentru obiect si este definita in clasele Plant si Zombie
	virtual void loadVertices(GLfloat Vertices[], int& poz) = 0;
	virtual ~GenericNPC() = 0;
};

