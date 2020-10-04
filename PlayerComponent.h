#include "Component.h"
#include "core/math/vector2.h"

class PlayerComponent : public Component {
public:
	Vector2 moveAmount;

	PlayerComponent(Vector2 moveBy) {
		moveAmount = moveBy;
	}
};
