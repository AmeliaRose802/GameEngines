#pragma once
#include "PhysicsComponent.h"
#include "System.h"
#include "TransformComponent.h"


class EventSystem;
class PongNode;
class CollisionEvent;

class PhysicsSystem : public System {

	const Vector2 SCREEN_SIZE = Vector2(1020, 600);
	PongNode *pongNode;

public:
	PhysicsSystem(EventSystem *eventSystem, PongNode * pongNode);

	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent);

	void receiveEvent(Event *event);

	void ReflectCollision(CollisionEvent *event);
};
