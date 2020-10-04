#pragma once
#include "DrawSystem.h"
#include "DrawComponent.h"

DrawSystem::DrawSystem() {
	
}

void DrawSystem::drawEntity(DrawComponent *drawComponent, TransformComponent *transformComponent) {
	drawComponent->getSprite()->set_position(transformComponent->location);
}
