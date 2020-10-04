#include "PongNode.h"

#include "DrawComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "UserInputComponent.h"


enum ComponentIDs {
	TRANSFORM_COMPONENT,
	DRAW_COMPONENT,
	COLLISION_COMPONENT,
	USER_INPUT_COMPONENT,
	PHYSICS_COMPONENT,
	NUM_COMPONENTS,
};

PongNode::PongNode()
{
	paddle = new Entity();
	ball = new Entity();
	drawSystem = new DrawSystem();
	physicsSystem = new PhysicsSystem();

	ResourceLoader *rl = new ResourceLoader();
	Ref<PackedScene> paddleScene = rl->load("res://PlayerPaddle.tscn");
	Ref<PackedScene> ballScene = rl->load("res://Ball.tscn");

	Sprite *paddleSprite = (Sprite *)(paddleScene->instance());
	add_child(paddleSprite);

	Sprite *ballSprite = (Sprite *)(ballScene->instance());
	add_child(ballSprite);



	//entitiesAndComponents[paddle->getID()][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(100, 100));
	//entitiesAndComponents[paddle->getID()][DRAW_COMPONENT] = new DrawComponent(paddleSprite);
	//entitiesAndComponents[paddle->getID()][COLLISION_COMPONENT] = new CollisionComponent();
	//entitiesAndComponents[paddle->getID()][USER_INPUT_COMPONENT] = new UserInputComponent();
	//entitiesAndComponents[paddle->getID()][PHYSICS_COMPONENT] = new PhysicsComponent(Vector2(0,0), Vector2(0,0));


	entitiesAndComponents[ball->getID()][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(450, 100));
	entitiesAndComponents[ball->getID()][DRAW_COMPONENT] = new DrawComponent(paddleSprite);
	entitiesAndComponents[ball->getID()][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[ball->getID()][PHYSICS_COMPONENT] = new PhysicsComponent(Vector2(30, 0), Vector2(5, 0));
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
		if (it->second.count(PHYSICS_COMPONENT) && it->second.count(TRANSFORM_COMPONENT) && it->second.count(USER_INPUT_COMPONENT)) {
			//TODO: Implement this
			
		}
		//If is has a position and physics then have it move
		if (it->second.count(PHYSICS_COMPONENT) && it->second.count(TRANSFORM_COMPONENT)) {
			physicsSystem->update(deltaTime, static_cast<PhysicsComponent *>(it->second[PHYSICS_COMPONENT]), static_cast<TransformComponent *>(it->second[TRANSFORM_COMPONENT]));
		}

		//TODO: How the fuck does collison work
	
	}
}
