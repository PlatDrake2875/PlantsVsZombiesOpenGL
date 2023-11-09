#pragma once
#include "GenericNPC.h"
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  

// Clasa pentru obiectul Plant
class Plant : public	GenericNPC
{
	// Numarul de puncte ale obiectului
	static GLuint nrPoints;

	// Offset-ul obiectului in array-ul de vertices
	static GLuint offset;
public:
	// Seteaza offset-ul din array-ul de vertices unde se gasesc coordinatele plantei generice
	static void setOffset(int offset);
	void setColor(int color);
	// xCenter, yCenter, zCenter - coordonatele centrului obiectului
	Plant(int color, float xCenter, float yCenter, float zCenter = 0.f);
	Plant(float xCenter, float yCenter, float zCenter = 0.f);
	//Plant();
	// Functie de desenare a plantei la pozitia actuala
	void draw() override;
	// Functie de incarcare a coordonatelor plantei in array-ul de vertices
	void loadVertices(GLfloat Vertices[], int& poz) override;
	void toString();
	// Intoarce pretul plantei in functie de culoarea acesteia
	int getPrice() const;
	bool isActive() const;
	~Plant();
};

