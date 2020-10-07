#include "PlayerSystem.h"
#include "core\os\input.h"
#include "PongNode.h"
#include "EventSystem.h"
#include "Component.h"


PlayerSystem::PlayerSystem(EventSystem *eventSystem, PongNode *pongNode) : System(eventSystem, pongNode)
{
	input = Input::get_singleton();
}

//Apply user input with speed determined by data in player component. Ignores physics and does own bounds detection
void PlayerSystem::applyUserInput(TransformComponent *transform, PlayerComponent *playerComponent)
{
	if (transform->location.y > 0 && input->is_action_pressed("ui_up"))
	{
		transform->location.y -= playerComponent->moveAmount.y;
	}
	if (transform->location.y < SCREEN_SIZE.y && input->is_action_pressed("ui_down"))
	{
		transform->location.y += playerComponent->moveAmount.y;
	}
}
