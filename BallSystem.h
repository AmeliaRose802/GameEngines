#pragma once
#include "System.h"
#include "PongNode.h"
#include "Events.h"

class BallSystem : public System {
	PongNode *pongNode;

public:
	BallSystem(EventSystem *eventSystem, PongNode *thePongNode);
	
	
	void receiveEvent(Event *event);

	void handleWallCollsion(WallCollisionEvent *event);
};
