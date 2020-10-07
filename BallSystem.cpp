#include "BallSystem.h"
#include "Enums.h"
#include "EventSystem.h"
#include "Events.h"
#include "PongNode.h"

BallSystem::BallSystem(EventSystem *eventSystem, PongNode *pongNode) : System(eventSystem, pongNode) {
	eventSystem->subscribe(EventType::EVENT_WALL_COLLISON, this);
};

//Gets events from the event system
void BallSystem::receiveEvent(Event* event) {
	switch (event->getType()) {
		case EVENT_WALL_COLLISON:
			handleWallCollsion(static_cast<WallCollisionEvent *>(event));
	}
}

//When ball hits bad wall lose
void BallSystem::handleWallCollsion(WallCollisionEvent* event) {
	LoseComponent *loseComponent = static_cast<LoseComponent *>(pongNode->getComponent(event->entityID, LOSE_COMPONENT));

	if (loseComponent != NULL) {
		if (event->wallLoc == loseComponent->badWall) {
			pongNode->loadLoseScene();
		}
	}
}

BallSystem ::~BallSystem()
{
}
