#pragma once
#include "modules/ECSModule/Component.h"
#include "scene/2d/sprite.h"

class DrawComponent : public Component {
private:
	Sprite* mSprite;

public:
	DrawComponent(Sprite* sprite) {
		mSprite = sprite;
	}

	Sprite* getSprite() {
		return mSprite;
	}
};
