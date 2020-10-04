#pragma once
#include <vector>
#include <map>
#include "Component.h"
#include "Enums.h"

class ComponentManager {
private:
	//TODO: Figure out better way of storing these
	std::map<int, std::map<int, Component *> > entitiesAndComponents;

public:
	void addComponent(int entityID, ComponentID componentID, Component *component);
	Component * getComponent(int entityID, ComponentID componentID);

	std::map<int, std::map<int, Component *> > getMap();
};
