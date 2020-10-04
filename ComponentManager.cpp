#include "ComponentManager.h"


void ComponentManager::addComponent(int entityID, ComponentID componentID, Component *component) {
	entitiesAndComponents[entityID][componentID] = component;
}
Component * ComponentManager::getComponent(int entityID, ComponentID componentID) {
	return entitiesAndComponents[entityID][componentID];
}

std::map<int, std::map<int, Component*> > ComponentManager::getMap() {
	return entitiesAndComponents;
}
