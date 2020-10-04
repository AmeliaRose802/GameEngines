//insert the Headername here
#ifndef FOLLOWMOUSENODE_H
#define FOLLOWMOUSENODE_H

#include "scene/main/node.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include "DrawSystem.h"
#include "System.h"
#include "Entity.h"
#include <string>
#include <vector>
#include <map>

class PongNode : public Node2D {
	GDCLASS(PongNode, Node2D);

private:
	Entity * paddle;
	std::map<int, std::map<int, Component *>> entitiesAndComponents;
	DrawSystem *drawSystem;

protected:
  static void _bind_methods();

public:
  PongNode();

  
  void updateSystems(float deltaTime);

};

#endif