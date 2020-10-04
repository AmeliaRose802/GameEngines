#pragma once
#include "modules/ECSModule/Component.h"
#include "core/math/vector2.h"

class PhysicsComponent : public Component {
private:
	Vector2 velocity;
	Vector2 acceleration;

};
