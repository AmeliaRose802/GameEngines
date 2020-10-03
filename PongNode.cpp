#include "PongNode.h"
#include "TransformSystem.h"
#include "DrawSystem.h"
#include "DrawComponent.h"


PongNode::PongNode()
{
	paddle = new Entity();

	TranformSystem *transformSystem = new TranformSystem();
	DrawSystem *drawSystem = new DrawSystem();

	systems.push_back(transformSystem);
	systems.push_back(drawSystem);

	Ref<ImageTexture> tex;
	ImageTexture *imgTex = new ImageTexture();
	
	Error error = imgTex->load("res://icon.png");

	Sprite *sprite = new Sprite();
	sprite->set_texture(imgTex);
	add_child(sprite, true);
	
}

//Bind all your methods used in this class
void PongNode::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("updateSystems", "deltaTime"), &PongNode::updateSystems);
}

void PongNode::updateSystems(float deltaTime)
{
	for (int i = 0; i < systems.size(); i++)
	{
		systems[i]->update(deltaTime);
	}
}
