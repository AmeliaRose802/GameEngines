#include "PhysicsSystem.h"
#include "EventSystem.h"
#include "PongNode.h"
#include "Enums.h"


PhysicsSystem::PhysicsSystem(EventSystem *eventSystem, PongNode * aPongNode) {
	eventSystem->subscribe(EventType::EVENT_COLLISION, this);
	eventSystem->subscribe(EventType::EVENT_WALL_COLLISON, this);
	pongNode = aPongNode;
}

void PhysicsSystem::update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent) {
	transformComponent->location += physicsComponent->velocity * deltaTime + (.5) * physicsComponent->acceleration * (deltaTime * deltaTime);

	/*
	//If edge of screen reverse acceleration and velocity?
	if (transformComponent->location.x > SCREEN_SIZE.x || transformComponent->location.x < 20) {
		//std::cout << "Bouncing on a wall in x direction Location: x:" << transformComponent->location.x << "Y: " << transformComponent->location.y << "\n";
		physicsComponent->velocity.x = -physicsComponent->velocity.x;
		physicsComponent->acceleration.x = -physicsComponent->acceleration.x;
		//std::cout << "Velocity: x" << physicsComponent->velocity.x << " y: " << physicsComponent->velocity.y << "\n";
		//std::cout << "Acc: x" << physicsComponent->acceleration.x << " y: " << physicsComponent->acceleration.y << "\n";
	}

	if (transformComponent->location.y > SCREEN_SIZE.y || transformComponent->location.y < 20) {
		physicsComponent->velocity.y = -physicsComponent->velocity.y;
		physicsComponent->acceleration.y = -physicsComponent->acceleration.y;
	}*/
}

void PhysicsSystem::receiveEvent(Event *event) {
	std::cout << "Physics system receved event\n";
	switch (event->getType()) {
		case EventType::EVENT_COLLISION:
			ReflectCollision(static_cast<CollisionEvent *>(event));
			break;
		case EVENT_WALL_COLLISON:
			ReflectWallCollision(static_cast<WallCollisionEvent *>(event));
	}
	
};

void PhysicsSystem::ReflectWallCollision(WallCollisionEvent *event) {
	PhysicsComponent * physicsComponent = static_cast<PhysicsComponent*>(pongNode->getComponent(event->entityID, PHYSICS_COMPONENT));
	std::cout << "Hit a wall\n";
	if (physicsComponent != NULL) {
		if (event->wallLoc == WALL_LEFT || event->wallLoc == WALL_RIGHT) {
			std::cout << "Hit left or right wall\n";
			std::cout << "Velocity: x" << physicsComponent->velocity.x << " y: " << physicsComponent->velocity.y << "\n";
			std::cout << "Acc: x" << physicsComponent->acceleration.x << " y: " << physicsComponent->acceleration.y << "\n";
			physicsComponent->velocity.x = -physicsComponent->velocity.x;
			physicsComponent->acceleration.x = -physicsComponent->acceleration.x;
		}

		if (event->wallLoc == WALL_TOP || event->wallLoc == WALL_BOTTOM) {
			physicsComponent->velocity.y = -physicsComponent->velocity.y;
			physicsComponent->acceleration.y = -physicsComponent->acceleration.y;
		}
	}
};

void PhysicsSystem::ReflectCollision(CollisionEvent *event) {
	PhysicsComponent *aPhysicsComponent = static_cast<PhysicsComponent *>(pongNode->getComponent(event->aID, ComponentID::PHYSICS_COMPONENT));
	if (aPhysicsComponent) {
		aPhysicsComponent->velocity = -aPhysicsComponent->velocity;
		aPhysicsComponent->acceleration = -aPhysicsComponent->acceleration;
	}

	PhysicsComponent *bPhysicsComponent = static_cast<PhysicsComponent *>(pongNode->getComponent(event->bID, ComponentID::PHYSICS_COMPONENT));
	if (bPhysicsComponent) {
		bPhysicsComponent->velocity = -bPhysicsComponent->velocity;
		bPhysicsComponent->acceleration = -bPhysicsComponent->acceleration;
	}
}
