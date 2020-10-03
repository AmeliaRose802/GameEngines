#include "System.h"


void System::removeComponent(int id) {
	components.erase(id);
}
void System::addComponent(int id, Component *component) {
	components[id] = component;
}

Component *System::getComponent(int id) {
	return components[id];
}


void System::regesterEntity(Entity* entity) {
	entities.push_back(entity);
}
