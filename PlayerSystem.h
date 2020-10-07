#pragma once
#include "System.h"

class Input;

class PlayerSystem : public System
{
private:
	Input *input;
	const Vector2 SCREEN_SIZE = Vector2(1020, 600);

public:
	PlayerSystem(EventSystem * eventSystem, PongNode * pongNode);
	void applyUserInput(TransformComponent *transform, PlayerComponent *playerComponent);
};
