#pragma once
#include "PhysicsComponent.h"
#include "System.h"
#include "TransformComponent.h"
#include "Events.h"


class EventSystem;
class PongNode;
class CollisionEvent;

class PhysicsSystem : public System {

	
	PongNode *pongNode;

public:
	PhysicsSystem(EventSystem *eventSystem, PongNode * pongNode);

	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent);

	void receiveEvent(Event *event);


	void ReflectWallCollision(WallCollisionEvent *event);
	void ReflectCollision(CollisionEvent *event);
};
