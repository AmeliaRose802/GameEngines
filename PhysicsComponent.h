#pragma once
#include "modules/ECSModule/Component.h"
#include "core/math/vector2.h"

class PhysicsComponent : public Component {
public:
	Vector2 velocity;
	Vector2 acceleration;
	const float MAX_BOUNCE_ANGLE = 5 * (3.14) / 12;

	PhysicsComponent(Vector2 vel, Vector2 acc) {
		velocity = vel;
		acceleration = acc;
	}

	float getSpeed() {
		return velocity.length();
	}
};
