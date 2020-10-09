#include "PongNode.h"

#include "Component.h"
#include "EventSystem.h"
#include "PhysicsSystem.h"
#include "PlayerSystem.h"
#include "DrawSystem.h"
#include "CollisionSystem.h"
#include "BallSystem.h"
#include "scene/2d/sprite.h"
#include "../../core/io/resource_loader.h"
#include "../../scene/resources/packed_scene.h"
#include <core\engine.h>


PongNode::PongNode()
{
	init();
}

int PongNode::nextEntityID = 0;

void PongNode::init()
{
	eventSystem = new EventSystem();
	drawSystem = new DrawSystem(eventSystem, this);
	physicsSystem = new PhysicsSystem(eventSystem, this);
	playerSystem = new PlayerSystem(eventSystem, this);
	collsionSystem = new CollisionSystem(eventSystem, this);
	ballSystem = new BallSystem(eventSystem, this);

	rl = new ResourceLoader();

	setUpBall();
	setUpPaddle();
	set_process(true);
}

//Bind all your methods used in this class
void PongNode::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("updateSystems", "deltaTime"), &PongNode::updateSystems);
	ClassDB::bind_method(D_METHOD("_notification", "what"), &PongNode::_notification);
}

//TODO: Figure out why this is not being called
void PongNode::_notification(int what)
{
	switch (what)
	{
		case NOTIFICATION_READY:
			//init();
			break;
		case NOTIFICATION_PROCESS:
			std::cout << "Process being called\n";
			if (!Engine::get_singleton()->is_editor_hint()) {
				updateSystems(get_process_delta_time());
			}
			break;
	}
	
}

void PongNode::updateSystems(float deltaTime)
{
	std::map<int, std::map<ComponentID, Component *>>::iterator it;
	for (it = entitiesAndComponents.begin(); it != entitiesAndComponents.end(); ++it)
	{

		//If it has both a draw and a transform component then tell the draw system to draw it?
		if (it->second.count(COMPONENT_DRAW) && it->second.count(COMPONENT_TRANSFORM))
		{
			drawSystem->drawEntity(static_cast<DrawComponent *>(it->second[COMPONENT_DRAW]), static_cast<TransformComponent *>(it->second[COMPONENT_TRANSFORM]));
		}
		//If it has a userInput system, a transform and a physics system then allow the user to control the object
		if (it->second.count(COMPONENT_TRANSFORM) && it->second.count(COMPONENT_PLAYER))
		{
			playerSystem->applyUserInput(static_cast<TransformComponent *>(it->second[COMPONENT_TRANSFORM]), static_cast<PlayerComponent *>(it->second[COMPONENT_PLAYER]));
		}
		//If is has a position and physics then have it move
		if (it->second.count(COMPONENT_PHYSICS) && it->second.count(COMPONENT_TRANSFORM))
		{
			physicsSystem->update(deltaTime, static_cast<PhysicsComponent *>(it->second[COMPONENT_PHYSICS]), static_cast<TransformComponent *>(it->second[COMPONENT_TRANSFORM]));
		}
		//Make a list of all collidable entities
		if (it->second.count(COMPONENT_TRANSFORM) && it->second.count(COMPONENT_COLLISION))
		{
			collsionSystem->checkWallCollision(it->first, static_cast<TransformComponent *>(it->second[COMPONENT_TRANSFORM]));
			collsionSystem->addColldable(it->first, static_cast<TransformComponent *>(it->second[COMPONENT_TRANSFORM]));
		}
	}

	//Check for collsion between the collidables
	collsionSystem->update();

}

Component* PongNode::getComponent(int entityID, ComponentID componentID)
{
	if (entitiesAndComponents.count(entityID) > 0) {
		if (entitiesAndComponents[entityID].count(componentID) > 0) {
			return entitiesAndComponents[entityID][componentID];
		}
	}
	return NULL;
}

void PongNode::loadLoseScene() {
	get_tree()->change_scene("LoseScene.tscn");
}

void PongNode::setUpBall() {
	
	int ballID = ++nextEntityID;
	
	Ref<PackedScene> ballScene = rl->load("res://Ball.tscn");

	Sprite *ballSprite = (Sprite *)(ballScene->instance());
	add_child(ballSprite);

	entitiesAndComponents[ballID][COMPONENT_TRANSFORM] = new TransformComponent(Vector2(200, 200), Vector2(50, 50));
	entitiesAndComponents[ballID][COMPONENT_DRAW] = new DrawComponent(ballSprite);
	entitiesAndComponents[ballID][COMPONENT_COLLISION] = new CollisionComponent();
	entitiesAndComponents[ballID][COMPONENT_PHYSICS] = new PhysicsComponent(Vector2(-400, 0), Vector2(0, 0));
	entitiesAndComponents[ballID][COMPONENT_LOSE] = new LoseComponent(WALL_LEFT);
}
void PongNode::setUpPaddle() {
	int paddleID = ++nextEntityID;

	Ref<PackedScene> paddleScene = rl->load("res://PlayerPaddle.tscn");

	Sprite *paddleSprite = (Sprite *)(paddleScene->instance());
	add_child(paddleSprite);

	entitiesAndComponents[paddleID][COMPONENT_TRANSFORM] = new TransformComponent(Vector2(30, 200), Vector2(20, 130));
	entitiesAndComponents[paddleID][COMPONENT_DRAW] = new DrawComponent(paddleSprite);
	entitiesAndComponents[paddleID][COMPONENT_COLLISION] = new CollisionComponent();
	entitiesAndComponents[paddleID][COMPONENT_PLAYER] = new PlayerComponent(Vector2(5, 5));
}


PongNode::~PongNode() {

	delete eventSystem;
	eventSystem = NULL;

	delete drawSystem;
	drawSystem = NULL;

	delete physicsSystem;
	physicsSystem = NULL;

	delete playerSystem;
	playerSystem = NULL;

	delete ballSystem;
	ballSystem = NULL;

	delete collsionSystem;
	collsionSystem = NULL;

	delete ballSystem;
	ballSystem = NULL;

	delete rl;
	rl = NULL;

	std::map<int, std::map<ComponentID, Component *> >::iterator it;

	for (it = entitiesAndComponents.begin(); it != entitiesAndComponents.end(); ++it) {
		std::map<ComponentID, Component *>::iterator it2;
		for (it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			delete it2->second;
		}
	}
}
