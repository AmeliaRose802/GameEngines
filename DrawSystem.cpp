#pragma once
#include "DrawSystem.h"
#include "DrawComponent.h"

DrawSystem::DrawSystem() {
	
}
void DrawSystem::update(float deltaTime) {
	
	std::map<int, Component *>::iterator it;
	for (it = components.begin(); it != components.end(); ++it) {
		DrawComponent *drawComponent = static_cast<DrawComponent *>(it->second);
		drawComponent->getSprite()->set_position(Point2(40, 40)); //TODO: How in the ever loving fuck am I supposed to get the transform component without causing cirular refrinces?!
	}
}
