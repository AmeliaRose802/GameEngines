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

#include "Enums.h"

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
			//updateSystems(get_process_delta_time());
			break;
	}
	
}

void PongNode::updateSystems(float deltaTime)
{
	std::map<int, std::map<int, Component *>>::iterator it;
	for (it = entitiesAndComponents.begin(); it != entitiesAndComponents.end(); ++it)
	{

		//If it has both a draw and a transform component then tell the draw system to draw it?
		if (it->second.count(DRAW_COMPONENT) && it->second.count(TRANSFORM_COMPONENT))
		{
			drawSystem->drawEntity(static_cast<DrawComponent *>(it->second[DRAW_COMPONENT]), static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}
		//If it has a userInput system, a transform and a physics system then allow the user to control the object
		if (it->second.count(TRANSFORM_COMPONENT) && it->second.count(PLAYER_COMPONENT))
		{
			playerSystem->applyUserInput(static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]), static_cast<PlayerComponent *>(it->second[PLAYER_COMPONENT]));
		}
		//If is has a position and physics then have it move
		if (it->second.count(PHYSICS_COMPONENT) && it->second.count(TRANSFORM_COMPONENT))
		{
			physicsSystem->update(deltaTime, static_cast<PhysicsComponent *>(it->second[PHYSICS_COMPONENT]), static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}
		//Make a list of all collidable entities
		if (it->second.count(TRANSFORM_COMPONENT) && it->second.count(COLLISION_COMPONENT))
		{
			collsionSystem->checkWallCollision(it->first, static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
			collsionSystem->addColldable(it->first, static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
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

	entitiesAndComponents[ballID][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(200, 200), Vector2(50, 50));
	entitiesAndComponents[ballID][DRAW_COMPONENT] = new DrawComponent(ballSprite);
	entitiesAndComponents[ballID][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[ballID][PHYSICS_COMPONENT] = new PhysicsComponent(Vector2(-400, 0), Vector2(0, 0));
	entitiesAndComponents[ballID][LOSE_COMPONENT] = new LoseComponent(WALL_LEFT);
}
void PongNode::setUpPaddle() {
	int paddleID = ++nextEntityID;

	Ref<PackedScene> paddleScene = rl->load("res://PlayerPaddle.tscn");

	Sprite *paddleSprite = (Sprite *)(paddleScene->instance());
	add_child(paddleSprite);

	entitiesAndComponents[paddleID][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(30, 200), Vector2(20, 130));
	entitiesAndComponents[paddleID][DRAW_COMPONENT] = new DrawComponent(paddleSprite);
	entitiesAndComponents[paddleID][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[paddleID][PLAYER_COMPONENT] = new PlayerComponent(Vector2(5, 5));
}
