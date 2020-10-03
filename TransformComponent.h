#pragma once
#include "Component.h"
#include "core/math/vector2.h"

class TransformComponent : public Component {
public:
	Vector2 location;
	TransformComponent(Vector2 loc) {
		location = loc;
	}
};
