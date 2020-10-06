#include "BallSystem.h"
#include "Enums.h"
#include "EventSystem.h"

BallSystem::BallSystem(EventSystem *eventSystem, PongNode *thePongNode) {
	eventSystem->subscribe(EventType::EVENT_WALL_COLLISON, this);
};

void BallSystem::receiveEvent(Event* event) {
	std::cout << "Ball System receved event\n";
	switch (event->getType()) {
		case EVENT_WALL_COLLISON:
			handleWallCollsion(static_cast<WallCollisionEvent *>(event));
	}
}

void BallSystem::handleWallCollsion(WallCollisionEvent* event) {
	Component *component = pongNode->getComponent(event->entityID, LOSE_COMPONENT);
	std::cout << "Component: " << component << "\n";
	if (component != NULL) {
		LoseComponent *loseComponent = static_cast<LoseComponent *>(pongNode->getComponent(event->entityID, LOSE_COMPONENT));

		if (loseComponent != NULL) {
			if (event->wallLoc == loseComponent->badWall) {
				std::cout << "You lose\n";
			}
		}
	} else {
		std::cout << "Returned null\n";
	}
	


	
	

	
}
