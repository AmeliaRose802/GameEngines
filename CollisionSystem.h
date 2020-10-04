#include "System.h"
#include "TransformComponent.h"
#include <map>
#include <iostream>

class CollisionSystem : public System {
private:
	std::vector<TransformComponent *> collidableTransforms;
	std::vector<int> collidableEntities;

public:
	CollisionSystem(){};

	void AddColldable(int id, TransformComponent * transformComponent) {
		collidableEntities.push_back(id);
		collidableTransforms.push_back(transformComponent);
	}

	void update()
	{
		std::map<TransformComponent *, int>::iterator it;

		for (int i = 0; i < collidableTransforms.size(); i++) {
			for (int j = i + 1; j < collidableTransforms.size(); j++) {
				if (checkCollision(collidableTransforms[i], collidableTransforms[j])) {
					std::cout << "Collsion Happended\n";
				}
			}
		}

		collidableTransforms.clear();
	}


//https://www.geeksforgeeks.org/find-two-rectangles-overlap/
	bool checkCollision(TransformComponent * a, TransformComponent * b) {
		if (a->location.x >= b->location.x + b->size.x || b->location.x >= a->location.x + a->size.x) {
			return false;
		}
		if (a->location.y >= b->location.y + b->size.y || b->location.y >= a->location.y + a->size.y) {
			return false;
		}
		return true;
	}
};
