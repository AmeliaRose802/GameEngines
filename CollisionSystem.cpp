#include "CollisionSystem.h"
#include "EventSystem.h"
#include "PongNode.h"
#include "Events.h"
#include "Component.h"

CollisionSystem::CollisionSystem(EventSystem * eventSystem, PongNode * pongNode) : System(eventSystem, pongNode){};

//Make a list of all items that can collide in a given update cycle
void CollisionSystem::addColldable(int id, TransformComponent *transformComponent)
{
	collidableEntities.push_back(id);
	collidableTransforms.push_back(transformComponent);
}

//Check collidable entities for overlap
void CollisionSystem::update() {
	std::map<TransformComponent *, int>::iterator it;

	for (int i = 0; i < collidableTransforms.size(); i++)
	{
		for (int j = i + 1; j < collidableTransforms.size(); j++)
		{
			if (checkCollision(collidableTransforms[i], collidableTransforms[j]))
			{
				eventSystem->dispatchEvent(new CollisionEvent(collidableEntities[i], collidableEntities[j]));
			}
		}
	}

	collidableTransforms.clear();
}

//Check if a given entity has hit any walls
void CollisionSystem::checkWallCollision(int id, TransformComponent* transformComponent)
{
	if (transformComponent->location.x > SCREEN_SIZE.x)
	{
		eventSystem->dispatchEvent(new WallCollisionEvent(WALL_RIGHT, id));
	}
	else if (transformComponent->location.x < 20)
	{
		eventSystem->dispatchEvent(new WallCollisionEvent(WALL_LEFT, id));
	}

	if (transformComponent->location.y > SCREEN_SIZE.y)
	{
		eventSystem->dispatchEvent(new WallCollisionEvent(WALL_BOTTOM, id));
	}
	else if (transformComponent->location.y < 20)
	{
		eventSystem->dispatchEvent(new WallCollisionEvent(WALL_TOP, id));
	}
}

//Collsion code based on:
//https://www.geeksforgeeks.org/find-two-rectangles-overlap/
bool CollisionSystem::checkCollision(TransformComponent *a, TransformComponent *b)
{
	return !(a->location.x >= b->location.x + b->size.x || b->location.x >= a->location.x + a->size.x || a->location.y >= b->location.y + b->size.y || b->location.y >= a->location.y + a->size.y);
}
