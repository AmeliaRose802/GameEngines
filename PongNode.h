//insert the Headername here
#ifndef FOLLOWMOUSENODE_H
#define FOLLOWMOUSENODE_H

#include "scene/main/node.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include "System.h"
#include "Entity.h"
#include <string>
#include <vector>

class PongNode : public Node2D {
	GDCLASS(PongNode, Node2D);

private:
	Entity * paddle;

protected:
  static void _bind_methods();
	Vector<System * > systems;

public:
  PongNode();

  
  void updateSystems(float deltaTime);

};

#endif
