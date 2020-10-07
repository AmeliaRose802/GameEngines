#pragma once

#include "System.h"
#include "Events.h"

class CollisionEvent;
class TransformComponent;
class PhysicsComponent;

class PhysicsSystem : public System
{
	void reflectWallCollision(WallCollisionEvent *event);
	void reflectCollision(CollisionEvent *event);
	void setPongReflection(PhysicsComponent * aPhysicsComponent, TransformComponent * aTransform, PhysicsComponent * bPhysicsComponent, TransformComponent  *bTransform);

public:
	PhysicsSystem(EventSystem *eventSystem, PongNode * pongNode);
	~PhysicsSystem() {}
	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent);
	void receiveEvent(Event *event);
	
};
