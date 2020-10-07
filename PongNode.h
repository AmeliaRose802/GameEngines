//insert the Headername here
#ifndef PONGNODE_H
#define PONGNODE_H

#include "scene/2d/node_2d.h"
#include "Enums.h"
#include <string>
#include <vector>
#include <map>

//Foward declare
class PhysicsSystem;
class DrawSystem;
class PlayerSystem;
class CollisionSystem;
class EventSystem;
class BallSystem;
class ResourceLoader;
class Component;

class PongNode : public Node2D {
private:
	GDCLASS(PongNode, Node2D);
	EventSystem *eventSystem;
	DrawSystem *drawSystem;
	PhysicsSystem *physicsSystem;
	PlayerSystem *playerSystem;
	CollisionSystem *collsionSystem;
	BallSystem *ballSystem;
	static int nextEntityID;
	ResourceLoader *rl;
	std::map<int, std::map<ComponentID, Component *> > entitiesAndComponents;

	void setUpBall();
	void setUpPaddle();

protected:
  static void _bind_methods();

public:
  PongNode();
  ~PongNode();
  void init();
  void _notification(int what);
  void updateSystems(float deltaTime);
  void loadLoseScene();
  Component *getComponent(int entityID, ComponentID componentID);
};

#endif
