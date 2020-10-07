#include "PhysicsSystem.h"
#include "EventSystem.h"
#include "PongNode.h"
#include "Enums.h"
#include "Component.h"


PhysicsSystem::PhysicsSystem(EventSystem *eventSystem, PongNode * pongNode) : System(eventSystem, pongNode)
{
	//Subscribe to important events
	eventSystem->subscribe(EventType::EVENT_COLLISION, this);
	eventSystem->subscribe(EventType::EVENT_WALL_COLLISON, this);
}

//Do basic movement with velocity and acceleration
void PhysicsSystem::update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent)
{
	transformComponent->location += physicsComponent->velocity * deltaTime + (.5) * physicsComponent->acceleration * (deltaTime * deltaTime);
}

void PhysicsSystem::receiveEvent(Event *event)
{
	switch (event->getType())
	{
		case EventType::EVENT_COLLISION:
			reflectCollision(static_cast<CollisionEvent *>(event));
			break;
		case EVENT_WALL_COLLISON:
			reflectWallCollision(static_cast<WallCollisionEvent *>(event));
	}
	
};

void PhysicsSystem::reflectWallCollision(WallCollisionEvent *event)
{
	PhysicsComponent * physicsComponent = static_cast<PhysicsComponent*>(pongNode->getComponent(event->entityID, COMPONENT_PHYSICS));
	
	//Do dumb collision with walls
	if (physicsComponent != NULL) {
		if (event->wallLoc == WALL_LEFT || event->wallLoc == WALL_RIGHT)
		{
			physicsComponent->velocity.x = -physicsComponent->velocity.x;
			physicsComponent->acceleration.x = -physicsComponent->acceleration.x;
		}

		if (event->wallLoc == WALL_TOP || event->wallLoc == WALL_BOTTOM)
		{
			physicsComponent->velocity.y = -physicsComponent->velocity.y;
			physicsComponent->acceleration.y = -physicsComponent->acceleration.y;
		}
	}
};

//Do weird pong collision between objects
void PhysicsSystem::reflectCollision(CollisionEvent *event)
{
	PhysicsComponent *aPhysicsComponent = static_cast<PhysicsComponent *>(pongNode->getComponent(event->aID, ComponentID::COMPONENT_PHYSICS));
	TransformComponent *aTransform = static_cast<TransformComponent *>(pongNode->getComponent(event->aID, ComponentID::COMPONENT_TRANSFORM));
	PhysicsComponent *bPhysicsComponent = static_cast<PhysicsComponent *>(pongNode->getComponent(event->bID, ComponentID::COMPONENT_PHYSICS));
	TransformComponent *bTransform = static_cast<TransformComponent *>(pongNode->getComponent(event->bID, ComponentID::COMPONENT_TRANSFORM));

	//Calc for 
	if (aPhysicsComponent)
	{
		setPongReflection(aPhysicsComponent, aTransform, bPhysicsComponent, bTransform);
	}

	if (bPhysicsComponent)
	{
		setPongReflection(bPhysicsComponent, bTransform, aPhysicsComponent, aTransform);
	}
}

//Adapted from accepted answer:
//https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
void PhysicsSystem::setPongReflection(PhysicsComponent * aPhysicsComponent, TransformComponent * aTransform, PhysicsComponent * bPhysicsComponent, TransformComponent * bTransform) {
	float relativeIntersectY = (bTransform->location.y + (bTransform->size.y / 2)) - aTransform->location.y;
	float normalizedRelativeIntersectionY = (relativeIntersectY / (bTransform->size.y / 2));
	float bounceAngle = normalizedRelativeIntersectionY * aPhysicsComponent->MAX_BOUNCE_ANGLE;
	aPhysicsComponent->velocity.y = aPhysicsComponent->getSpeed() * cos(bounceAngle);
	aPhysicsComponent->velocity.x = aPhysicsComponent->getSpeed() * sin(bounceAngle);
}

PhysicsSystem ::~PhysicsSystem() {
}
