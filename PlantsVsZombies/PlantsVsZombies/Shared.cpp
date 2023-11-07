#include "Shared.h"

GLuint Shared::myMatrixLocation = 0;
GLuint Shared::codColLocation = 0;
glm::mat4 Shared::resizeMatrix = glm::mat4(1.f);
std::list<Plant*> Shared::plants;
std::list<Zombie*> Shared::zombies;
std::list<Bullet*> Shared::bullets;
const float Shared::PI = 3.14159265358979323846f;
int Shared::lives = 3;