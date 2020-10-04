#include "Modules/ECSModule/Entity.h"

int Entity::nextID = 0;

Entity::Entity() {
	id = nextID;
	nextID++;
	std::cout << "Created a new entity with ID + " << id<<"\n";
}
