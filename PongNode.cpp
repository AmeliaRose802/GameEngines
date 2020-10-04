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
	drawSystem = new DrawSystem();


	Ref<ImageTexture> tex;
	ImageTexture *imgTex = new ImageTexture();
	
	Error error = imgTex->load("res://icon.png");

	Sprite *sprite = new Sprite();
	sprite->set_texture(imgTex);
	add_child(sprite, true);

	entitiesAndComponents[paddle->getID()][TRANSFORM_COMPONENT] = new TransformComponent(Vector2(100, 100));
	entitiesAndComponents[paddle->getID()][DRAW_COMPONENT] = new DrawComponent(sprite);
	entitiesAndComponents[paddle->getID()][COLLISION_COMPONENT] = new CollisionComponent();
	entitiesAndComponents[paddle->getID()][USER_INPUT_COMPONENT] = new UserInputComponent();
	entitiesAndComponents[paddle->getID()][PHYSICS_COMPONENT] = new PhysicsComponent();
}

//Bind all your methods used in this class
void PongNode::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("updateSystems", "deltaTime"), &PongNode::updateSystems);
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
			std::cout << "User input not implemented\n";
		}
		//If is has a position and physics then have it move
		if (it->second.count(PHYSICS_COMPONENT) && it->second.count(TRANSFORM_COMPONENT)) {
			//TODO: Make the fucker move
		}

		//TODO: How the fuck does collison work
	
	}
}
