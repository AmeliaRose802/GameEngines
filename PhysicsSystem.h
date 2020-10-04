#pragma once
#include "System.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

class PhysicsSystem : public System {
public:
	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent)
	{
		transformComponent->location += physicsComponent->velocity * deltaTime + (.5) * physicsComponent->acceleration * (deltaTime * deltaTime);
	}
};
