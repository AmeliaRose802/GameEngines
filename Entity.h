#pragma once
#include "scene/main/node.h"
#include <iostream>

class Entity
{

private:
	int id;
	static int nextID;

public:
	Entity();

	int getID() {
		return id;
	}
};
