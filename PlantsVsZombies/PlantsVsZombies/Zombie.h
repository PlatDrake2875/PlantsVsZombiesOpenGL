#pragma once
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  
#include "GenericNPC.h"

class Zombie : public GenericNPC
{
	// Numarul de puncte ale obiectului
	static GLuint nrPoints;

	// Offset-ul obiectului in array-ul de vertices
	static GLuint offset;

	static int interiorColor;
	float step = 0.1f, currentXPosition;
public:
	// xCenter, yCenter, zCenter - coordonatele centrului obiectului
	Zombie(int color, float xCenter, float yCenter, float zCenter = 0.f);
	static void setOffset(int offset);
	void draw() override;
	void move();
	~Zombie();

};

