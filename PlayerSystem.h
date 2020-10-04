#pragma once
#include "System.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "PlayerComponent.h"
#include "core\os\input.h"

class PlayerSystem : public System {
private:
	Input *input;
	const Vector2 SCREEN_SIZE = Vector2(1020, 600);

public:
	PlayerSystem() {
		input = Input::get_singleton();
	}
	void ApplyUserInput(TransformComponent * transform, PlayerComponent * playerComponent) {
		if (transform->location.y > 0 && input->is_action_pressed("ui_up")) {
			transform->location.y -= playerComponent->moveAmount.y;
		}
		if (transform->location.y < SCREEN_SIZE.y && input->is_action_pressed("ui_down")) {
			transform->location.y += playerComponent->moveAmount.y;
		}
	}
};
