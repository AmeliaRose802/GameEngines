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
	
	//std::cout << "Hit a wall\n";
	if (physicsComponent != NULL) {
		if (event->wallLoc == WALL_LEFT || event->wallLoc == WALL_RIGHT) {
			//std::cout << "Hit left or right wall\n";
			//std::cout << "Velocity: x" << physicsComponent->velocity.x << " y: " << physicsComponent->velocity.y << "\n";
			//std::cout << "Acc: x" << physicsComponent->acceleration.x << " y: " << physicsComponent->acceleration.y << "\n";
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
	TransformComponent *aTransform = static_cast<TransformComponent *>(pongNode->getComponent(event->aID, ComponentID::TRANSFORM_COMPONENT));
	PhysicsComponent *bPhysicsComponent = static_cast<PhysicsComponent *>(pongNode->getComponent(event->bID, ComponentID::PHYSICS_COMPONENT));
	TransformComponent *bTransform = static_cast<TransformComponent *>(pongNode->getComponent(event->bID, ComponentID::TRANSFORM_COMPONENT));

	//Calc for 
	if (aPhysicsComponent) {
		//aPhysicsComponent->velocity = -aPhysicsComponent->velocity;
		//aPhysicsComponent->acceleration = -aPhysicsComponent->acceleration;
		//https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
		float relativeIntersectY = (bTransform->location.y + (bTransform->size.y / 2)) - aTransform->location.y;
		float normalizedRelativeIntersectionY = (relativeIntersectY / (bTransform->size.y / 2));
		float bounceAngle = normalizedRelativeIntersectionY * aPhysicsComponent->MAX_BOUNCE_ANGLE;
		aPhysicsComponent->velocity.y = aPhysicsComponent->getSpeed() * cos(bounceAngle);
		aPhysicsComponent->velocity.x = aPhysicsComponent->getSpeed() * sin(bounceAngle);
		
		std::cout << "A: velocity x: " << aPhysicsComponent->velocity.x << " y: " << aPhysicsComponent->velocity.y << "\n";
		std::cout << "YIntersect: " << relativeIntersectY << "Normalized Relitive Y: " << normalizedRelativeIntersectionY << "\n";
	}

	
	if (bPhysicsComponent) {
		//bPhysicsComponent->velocity = -bPhysicsComponent->velocity;
		//bPhysicsComponent->acceleration = -bPhysicsComponent->acceleration;
		float relativeIntersectY = (aTransform->location.y + (aTransform->size.y / 2)) - bTransform->location.y;
		float normalizedRelativeIntersectionY = (relativeIntersectY / (aTransform->size.y / 2));
		float bounceAngle = normalizedRelativeIntersectionY * bPhysicsComponent->MAX_BOUNCE_ANGLE;
		bPhysicsComponent->velocity.y = bPhysicsComponent->getSpeed() * cos(bounceAngle);
		bPhysicsComponent->velocity.x = bPhysicsComponent->getSpeed() * sin(bounceAngle);

		
		std::cout << "B: velocity x: " << bPhysicsComponent->velocity.x << " y: " << bPhysicsComponent->velocity.y << "\n";
		std::cout << "YIntersect: " << relativeIntersectY << "Normalized Relitive Y: " << normalizedRelativeIntersectionY << "\n";
	}
}
