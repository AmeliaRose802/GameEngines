#pragma once
#include "System.h"
#include "DrawComponent.h"
#include "TransformComponent.h"


class DrawSystem : public System {
public:
	DrawSystem();
	void drawEntity(DrawComponent *drawComponent, TransformComponent *transformComponent);
};
