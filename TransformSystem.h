#pragma once
#include "System.h"
#include "TransformComponent.h"
#include <map>

class TranformSystem : public System {
public:
	TranformSystem() {

	}


	void update(float deltaTime);
};
