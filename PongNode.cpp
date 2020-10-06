#include "PongNode.h"

#include "DrawComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "UserInputComponent.h"
#include "EventSystem.h"
#include "PhysicsSystem.h"
#include "PlayerSystem.h"
#include "DrawSystem.h"
#include "CollisionSystem.h"
#include "BallSystem.h"

#include "Enums.h"

PongNode::PongNode()
{
	eventSystem = new EventSystem();
	paddle = new Entity();
	ball = new Entity();
	drawSystem = new DrawSystem();
	physicsSystem = new PhysicsSystem(eventSystem, this);
	playerSystem = new PlayerSystem();
	collsionSystem = new CollisionSystem(eventSystem, this);
	ballSystem = new BallSystem(eventSystem, this);

	ResourceLoader *rl = new ResourceLoader();
	Ref<PackedScene> paddleScene = rl->load("res://PlayerPaddle.tscn");
	Ref<PackedScene> ballScene = rl->load("res://Ball.tscn");

	Sprite *paddleSprite = (Sprite *)(paddleScene->instance());
	add_child(paddleSprite);

	Sprite *ballSprite = (Sprite *)(ballScene->instance());
	add_child(ballSprite);



	entitiesAndComponents[paddle->getID()][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(10, 200), Vector2(20, 100));
	entitiesAndComponents[paddle->getID()][DRAW_COMPONENT] = new DrawComponent(paddleSprite);
	entitiesAndComponents[paddle->getID()][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[paddle->getID()][USER_INPUT_COMPONENT] = new UserInputComponent();
	entitiesAndComponents[paddle->getID()][PHYSICS_COMPONENT] = new PhysicsComponent(Vector2(0,0), Vector2(0,0));
	entitiesAndComponents[paddle->getID()][PLAYER_COMPONENT] = new PlayerComponent(Vector2(5, 5));


	entitiesAndComponents[ball->getID()][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(200, 200), Vector2(50, 50));
	entitiesAndComponents[ball->getID()][DRAW_COMPONENT] = new DrawComponent(ballSprite);
	entitiesAndComponents[ball->getID()][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[ball->getID()][PHYSICS_COMPONENT] = new PhysicsComponent(Vector2(-200, 0), Vector2(0, 0));
	entitiesAndComponents[ball->getID()][LOSE_COMPONENT] = new LoseComponent(WALL_LEFT);
}

//Bind all your methods used in this class
void PongNode::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("updateSystems", "deltaTime"), &PongNode::updateSystems);
  ClassDB::bind_method(D_METHOD("_process", "delta"), &PongNode::_process);
}

//TODO: Figure out why this is not being called
void PongNode::_process(float delta) {
	std::cout << "Process being called?\n";
	updateSystems(delta);
}

void PongNode::updateSystems(float deltaTime)
{
	std::map<int, std::map<int, Component *>>::iterator it;
	for (it = entitiesAndComponents.begin(); it != entitiesAndComponents.end(); ++it) {

		//If it has both a draw and a transform component then tell the draw system to draw it?
		if (it->second.count(DRAW_COMPONENT) && it->second.count(TRANSFORM_COMPONENT)) {
			drawSystem->drawEntity(static_cast<DrawComponent *>(it->second[DRAW_COMPONENT]), static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}
		//If it has a userInput system, a transform and a physics system then allow the user to control the object
		if (it->second.count(TRANSFORM_COMPONENT) && it->second.count(PLAYER_COMPONENT)) {
			playerSystem->ApplyUserInput(static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]), static_cast<PlayerComponent *>(it->second[PLAYER_COMPONENT]));
		}
		//If is has a position and physics then have it move
		if (it->second.count(PHYSICS_COMPONENT) && it->second.count(TRANSFORM_COMPONENT)) {
			physicsSystem->update(deltaTime, static_cast<PhysicsComponent *>(it->second[PHYSICS_COMPONENT]), static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}
		//Make a list of all collidable entities
		if (it->second.count(TRANSFORM_COMPONENT) && it->second.count(COLLISION_COMPONENT)) {
			collsionSystem->checkWallCollision(it->first, static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
			collsionSystem->addColldable(it->first, static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}

	
	}

	//Check for collsion between the collidables
	collsionSystem->update();

}

Component* PongNode::getComponent(int entityID, ComponentID componentID) {
	if (entitiesAndComponents.count(entityID) > 0) {
		if (entitiesAndComponents[entityID].count(componentID) > 0) {
			return entitiesAndComponents[entityID][componentID];
			}
		}
	
	
	return NULL;
}

//TODO: DESTRUCTOR

void PongNode::printMap() {
	std::map<int, std::map<int, Component *> >::iterator it;
	for (it = entitiesAndComponents.begin(); it != entitiesAndComponents.end(); ++it) {
		std::cout << "Key: " << it->first << "\n";
		std::map<int, Component *>::iterator it2;
		for (it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			std::cout << "Key: " << it2->first << " Value: " << it2->second << "\n";
		}
	}

}
