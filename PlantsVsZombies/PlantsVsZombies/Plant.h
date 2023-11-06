#pragma once
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  

class Plant
{
	glm::vec3 position;
	float health;
	int color;
	void erase();
public:
	// Numarul de puncte ale obiectului
	static GLuint nrPoints;

	// Offset-ul obiectului in array-ul de indici
	static GLuint offset; 
	Plant(int color, float x, float y, float z = 0.f);
	void setHealth(float health);
	float getHealth();
	glm::vec3 getPosition();
	int getColor();
	void draw();
	~Plant();
};

