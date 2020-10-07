#pragma once
#include "System.h"

class DrawComponent;
class TransformComponent;


class DrawSystem : public System {
public:
	DrawSystem(EventSystem * eventSystem, PongNode * pongNode);
	void drawEntity(DrawComponent *drawComponent, TransformComponent *transformComponent);
};
