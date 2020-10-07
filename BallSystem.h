#pragma once
#include "System.h"

class WallCollisionEvent;

class BallSystem : public System {

public:
	BallSystem(EventSystem *eventSystem, PongNode *thePongNode);
	~BallSystem(){};
	void receiveEvent(Event *event);
	void handleWallCollsion(WallCollisionEvent *event);
};
