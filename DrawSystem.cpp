#pragma once
#include "DrawSystem.h"
#include "Component.h"

DrawSystem::DrawSystem(EventSystem *eventSystem, PongNode *pongNode) : System(eventSystem, pongNode) {}

void DrawSystem::drawEntity(DrawComponent *drawComponent, TransformComponent *transformComponent)
{
	drawComponent->getSprite()->set_position(transformComponent->location);
}
