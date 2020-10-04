#pragma once
#include "Component.h"
#include "core/math/vector2.h"

class TransformComponent : public Component {
public:
	Vector2 location;
	Vector2 size;

	TransformComponent(Vector2 loc, Vector2 siz) {
		location = loc;
		size = siz;
	}
};
