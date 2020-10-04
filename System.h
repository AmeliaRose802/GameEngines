#pragma once
#include <map>
#include <vector>
#include "Component.h"
#include "Entity.h"

class System {
protected:
	//std::map<int, Component *> components;
	//std::vector<Entity *> entities;

public:
	System() {}

	/*
	virtual void removeComponent(int id);
	virtual void addComponent(int id, Component * component);
	void regesterEntity(Entity * entity);*/

	/*
	virtual Component* getComponent(int id);
	virtual void update(float deltaTime) = 0;*/
	
};
