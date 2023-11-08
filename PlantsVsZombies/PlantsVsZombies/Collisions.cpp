#include "Collisions.h"
#include "Shared.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void Collisions::ZombieBullet()
{
	for (auto& zombie : Shared::zombies)
	{
		for (auto& bullet : Shared::bullets)
		{
			if (zombie->getPosition().x < bullet->getPosition().x)
			{
				glm::vec3 new_pos(glm::vec3(-10.0f, 0.0f, 0.0f));
				zombie->setPosition(new_pos);
			}
		}
	}
}