#include "Shared.h"

GLuint Shared::myMatrixLocation = 0;
GLuint Shared::codColLocation = 0;
glm::mat4 Shared::resizeMatrix = glm::mat4(1.f);
std::list<Plant*> Shared::plants;
std::list<Zombie*> Shared::zombies;
std::list<Bullet*> Shared::bullets;
std::list<square> Shared::squares;
std::list<square> Shared::usedSquares;
const float Shared::PI = 3.14159265358979323846f;
int Shared::lives = 3;
GLfloat Shared::winWidth = 0.f;
GLfloat Shared::winHeight = 0.f;
int Shared::render_duration = 0; // in miliseconds
