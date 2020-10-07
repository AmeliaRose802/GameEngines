#pragma once
#include "Enums.h"
#include "scene/2d/sprite.h"

//Base class for components. No functionality of its own
class Component {
public:
	Component() {}
};


//Marks an item as causing a lose state when it collides with the bad wall. Used on the ball
class LoseComponent : public Component {
public:
	WallLocation badWall;
	LoseComponent(WallLocation theBadWall) {
		badWall = theBadWall;
	}
};

//Marks an object as collidable. Might contain data about layers and such in the future but right now it is a dummy component
class CollisionComponent : public Component {
};

//Probly the biggest component. Contains data about all physics for an entity
class PhysicsComponent : public Component {
public:
	Vector2 velocity;
	Vector2 acceleration;
	const float MAX_BOUNCE_ANGLE = 5 * (3.14) / 12;

	PhysicsComponent(Vector2 vel, Vector2 acc) {
		velocity = vel;
		acceleration = acc;
	}

	float getSpeed() {
		return velocity.length();
	}
};

//Contains sprite so entity can actually be displayed on screen
class DrawComponent : public Component {
private:
	Sprite *mSprite;

public:
	DrawComponent(Sprite *sprite) {
		mSprite = sprite;
	}

	Sprite *getSprite() {
		return mSprite;
	}
};

//Marks a controllable player entity
class PlayerComponent : public Component {
public:
	Vector2 moveAmount;

	PlayerComponent(Vector2 moveBy) {
		moveAmount = moveBy;
	}
};

//Contains position and size data. Does not support rotation. Size only used for collison. Does not effect actual size of sprite
class TransformComponent : public Component {
public:
	Vector2 location;
	Vector2 size;

	TransformComponent(Vector2 loc, Vector2 siz) {
		location = loc;
		size = siz;
	}
};
