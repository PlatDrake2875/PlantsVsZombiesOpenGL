#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include "glm/gtc/matrix_transform.hpp"
#pragma once


class Shared
{
public:
	static GLuint myMatrixLocation;
	static GLuint codColLocation;
	static glm::mat4 resizeMatrix;
};

