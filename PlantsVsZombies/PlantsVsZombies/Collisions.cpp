#include <iostream>
#include "Collisions.h"
#include "Shared.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Functie care verifica daca un zombie a fost lovit de o bila
// Daca da, il elimina din lista de zombie
void Collisions::ZombieBullet()
{
	for (auto& zombie : Shared::zombies)
		for (auto& bullet : Shared::bullets)
		{
			if (zombie->getPosition().x < bullet->getPosition().x 
				&& zombie->getColor() == bullet->getColor()
				&& abs(zombie->getPosition().y - bullet->getPosition().y) < 50)
			{
				glm::vec3 outside(glm::vec3(-200.0f, -200.0f, 0.0f));
				// setrgem bullet-ul
				bullet->setPosition(outside);

				float new_health = zombie->getHealth() - 40.f;
				zombie->setHealth(new_health);
				if (zombie->getHealth() <= 0)
					zombie->setPosition(outside);
			}
		}
}

// Functie care verifica daca un zombie distruge o planta
// Daca da, o elimina din lista de plante
void Collisions::ZombiePlant()
{
	for (auto& plant : Shared::plants)
	{
		for (auto& zombie : Shared::zombies)
		{
			if (zombie->getPosition().x < plant->getPosition().x
				&& abs(zombie->getPosition().y - plant->getPosition().y) < 50)
			{
				//Shared::plants.erase(std::remove(Shared::plants.begin(), Shared::plants.end(), plant), Shared::plants.end());

				glm::vec3 outside(glm::vec3(-200.0f, -200.0f, 0.0f));
				plant->setPosition(outside);
			}
		}
	}
}

void Collisions::ZombieHome()
{
	for (auto& zombie : Shared::zombies)
	{
		if (zombie->getPosition().x < 100.f && zombie->getPosition().x > 90.f && zombie->getPosition().y > 25 && zombie->getPosition().y < 1000)
		{
			// delete zombie
			//Shared::zombies.erase(std::remove(Shared::zombies.begin(), Shared::zombies.end(), zombie), Shared::zombies.end());

			glm::vec3 outside(glm::vec3(-200.0f, -200.0f, -200.0f));
			std::cout << "Position: " << zombie->getPosition().x << " " << zombie->getPosition().y << std::endl;

			zombie->setPosition(outside);
			std::cout<<"A zombie has reached your home!"<<std::endl;

			//Shared::lives--;
			zombie->setKiller();
			std::cout<<"Lives: "<<Shared::lives<<std::endl;
		}
	}
}