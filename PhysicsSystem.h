#pragma once
#include "PhysicsComponent.h"
#include "System.h"
#include "TransformComponent.h"


class EventSystem;

class PhysicsSystem : public System {

	const Vector2 SCREEN_SIZE = Vector2(1020, 600);

public:
	PhysicsSystem(EventSystem *eventSystem);

	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent);

	void receiveEvent(Event *event);
};
