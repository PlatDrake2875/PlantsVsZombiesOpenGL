#include "Placing.h"
#include "Colors.h"
#include "Shared.h"
#include "Plant.h"
#include <iostream>

Placing::Placing(GLuint pressedNumber, Plant plant) : Plant(plant.getColor(), plant.getPosition().x, plant.getPosition().y, plant.getPosition().z) {
	this->pressedNumber = pressedNumber;
}

void Placing::setPressedNumber(GLuint pressedNumber) {
	this->pressedNumber = pressedNumber;
}

void Placing::addPlant(Plant* p) {
	auto it = Shared::usedSquares.begin();
	while (it != Shared::usedSquares.end()) {
		if (it->x == p->getPosition().x && it->y == p->getPosition().y) {
			return;
		}
		++it;
	}
	Shared::plants.push_back(p);
}

void Placing::addPlants(std::list<Plant*> plants) {
	Shared::plants.insert(Shared::plants.end(), plants.begin(), plants.end());
}

void Placing::drawAllPlants() {
	auto it = Shared::plants.begin();
	while (it != Shared::plants.end()) {
		(*it)->toString();
		Plant p = **it;


		//(*it)->draw();
		++it;
	}
}

Placing::~Placing() {}