#pragma once
#include "Enums.h"

class Component {
public:
	Component() {}
};

class LoseComponent : public Component {
	
public:
	WallLocation badWall;
	LoseComponent(WallLocation theBadWall) {
		badWall = theBadWall;
	}
};
