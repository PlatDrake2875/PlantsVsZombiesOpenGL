#pragma once
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Colors.h"
#include <GL/glew.h>  
#include "GenericNPC.h"

// Clasa pentru un obiect de tip zombie "fizic"
class Zombie : public GenericNPC
{
	// Numarul de puncte ale obiectului
	static GLuint nrPoints;

	// Offset-ul obiectului in array-ul de vertices
	static GLuint offset;

	// Culoarea interioara a oricarui zombie va fi mereu aceeasi
	static int interiorColor;
	static float step;
	float currentXPosition;
	bool killer = false;
public:
	// xCenter, yCenter, zCenter - coordonatele centrului obiectului
	Zombie(int color, float xCenter, float yCenter, float zCenter = 0.f);
	Zombie();
	// Seteaza offset-ul in array-ul de vertices pentru zombie "generic"
	static void setOffset(int offset);
	// Functia care deseneaza un zombie "fizic"
	void draw() override;
	// Punem in Vertices punctele care deseneaza un zombie centrat in (0, 0) (mai intai partea exterioara, apoi cea interioara)
	void loadVertices(GLfloat Vertices[], int& poz) override;
	// Muta zombie-ul la noile coordonate pentru deplasarea la stanga
	void move();
	bool isActive() const;
	void setKiller();
	// Verificam daca obiectul este un zombie care a ajuns la linia de baza
	bool isKiller();
	~Zombie();

};

