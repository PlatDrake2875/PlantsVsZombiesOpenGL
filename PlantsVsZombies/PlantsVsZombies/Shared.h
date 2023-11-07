#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include "glm/gtc/matrix_transform.hpp"
#include <list>
#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"
#pragma once


class Shared
{
public:
	static const float PI;
	static int lives;
	static GLuint myMatrixLocation;
	static GLuint codColLocation;
	static glm::mat4 resizeMatrix;
	static std::list<Plant*> plants;
	static std::list<Zombie*> zombies;
	static std::list<Bullet*> bullets;
};

