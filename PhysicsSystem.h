#pragma once
#include "PhysicsComponent.h"
#include "System.h"
#include "TransformComponent.h"


class PhysicsSystem : public System {

	const Vector2 SCREEN_SIZE = Vector2(1020, 600);

public:
	void update(float deltaTime, PhysicsComponent *physicsComponent, TransformComponent *transformComponent) {
		transformComponent->location += physicsComponent->velocity * deltaTime + (.5) * physicsComponent->acceleration * (deltaTime * deltaTime);

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
		}
	}
};
