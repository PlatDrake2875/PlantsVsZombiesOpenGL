#pragma once
#include "Plant.h"
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <list>

class Placing : public Plant
{
	GLuint pressedNumber;
public:
	Placing(GLuint pressedNumber, Plant plant);
	void setPressedNumber(GLuint pressedNumber);
	static void addPlant(Plant* p);
	static void addPlants(std::list<Plant*> plants);
	static void drawAllPlants();
	~Placing();
};

