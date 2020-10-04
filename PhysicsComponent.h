#pragma once
#include "modules/ECSModule/Component.h"
#include "core/math/vector2.h"

class PhysicsComponent : public Component {
public:
	Vector2 velocity;
	Vector2 acceleration;

	PhysicsComponent(Vector2 vel, Vector2 acc) {
		velocity = vel;
		acceleration = acc;

		
	}
};
