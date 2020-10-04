//insert the Headername here
#ifndef FOLLOWMOUSENODE_H
#define FOLLOWMOUSENODE_H

#include "scene/main/node.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include "PhysicsSystem.h"
#include "PlayerSystem.h"
#include "../../core/io/resource_loader.h"
#include "../../scene/resources/packed_scene.h"
#include "DrawSystem.h"
#include "System.h"
#include "Entity.h"
#include "CollisionSystem.h"
#include <string>
#include <vector>
#include <map>

class PongNode : public Node2D {
	GDCLASS(PongNode, Node2D);

private:
	Entity * paddle;
	Entity *ball;
	std::map<int, std::map<int, Component *>> entitiesAndComponents;
	DrawSystem *drawSystem;
	PhysicsSystem *physicsSystem;
	PlayerSystem *playerSystem;
	CollisionSystem *collsionSystem;

protected:
  static void _bind_methods();

public:
  PongNode();

  void _process(float delta);
  void updateSystems(float deltaTime);

};

#endif
