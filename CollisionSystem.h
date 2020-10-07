#include "System.h"
#include <map>
#include <iostream>

class TransformComponent;

class CollisionSystem : public System {
private:
	const Vector2 SCREEN_SIZE = Vector2(1000, 580);

	std::vector<TransformComponent *> collidableTransforms;
	std::vector<int> collidableEntities;


public:
	CollisionSystem(EventSystem *eventSystem, PongNode * thePongNode);
	~CollisionSystem() {}
	void addColldable(int id, TransformComponent *transformComponent);
	void checkWallCollision(int id, TransformComponent *transformComponent);
	void update();
	bool checkCollision(TransformComponent *a, TransformComponent *b);
};
