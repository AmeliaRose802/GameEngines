#include "System.h"
#include "TransformComponent.h"
#include <map>
#include <iostream>

class EventSystem;

class CollisionSystem : public System {
private:
	const Vector2 SCREEN_SIZE = Vector2(1020, 600);
	std::vector<TransformComponent *> collidableTransforms;
	std::vector<int> collidableEntities;
	EventSystem *eventSystem;

public:
	CollisionSystem(EventSystem *eventSystem);

	void addColldable(int id, TransformComponent *transformComponent);
	void checkWallCollision(int id, TransformComponent *transformComponent);

	void update();


//https://www.geeksforgeeks.org/find-two-rectangles-overlap/
	bool checkCollision(TransformComponent *a, TransformComponent *b);
};
