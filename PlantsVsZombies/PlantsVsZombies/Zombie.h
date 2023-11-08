#pragma once
#include "glm/glm.hpp"		
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
	static float step;
	float currentXPosition;
public:
	// xCenter, yCenter, zCenter - coordonatele centrului obiectului
	Zombie(int color, float xCenter, float yCenter, float zCenter = 0.f);
	Zombie();
	static void setOffset(int offset);
	void draw() override;
	// Punem in Vertices punctele care deseneaza un zombie centrat in (0, 0) (mai intai partea exterioara, apoi cea interioara)
	void loadVertices(GLfloat Vertices[], int& poz) override;
	void move();
	bool isActive() const;
	~Zombie();

};

