#include "BallSystem.h"
#include "Enums.h"
#include "EventSystem.h"

BallSystem::BallSystem(EventSystem *eventSystem, PongNode *thePongNode) {
	eventSystem->subscribe(EventType::EVENT_WALL_COLLISON, this);
	pongNode = thePongNode;
};

void BallSystem::receiveEvent(Event* event) {
	switch (event->getType()) {
		case EVENT_WALL_COLLISON:
			handleWallCollsion(static_cast<WallCollisionEvent *>(event));
	}
}

void BallSystem::handleWallCollsion(WallCollisionEvent* event) {
	Component *component = pongNode->getComponent(event->entityID, TRANSFORM_COMPONENT);
	if (component != NULL) {
		LoseComponent *loseComponent = static_cast<LoseComponent *>(pongNode->getComponent(event->entityID, LOSE_COMPONENT));

		if (loseComponent != NULL) {
			if (event->wallLoc == loseComponent->badWall) {
				std::cout << "****You lose\n";
			}
		}
	} else {
	}
	


	
	

	
}
