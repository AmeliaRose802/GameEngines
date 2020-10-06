#pragma once
#include "Enums.h"

class Event {
protected:
	EventType mType;

public:
	Event(EventType type) {
		mType = type;
	}
	
	virtual EventType getType() { return mType; }
};

class CollisionEvent : public Event {
	

	public:
	int aID;
	int bID;
	CollisionEvent(int idA, int idB) :
			Event(EventType::EVENT_COLLISION)
	{
		aID = idA;
		bID = idB;
	};
};


class WallCollisionEvent : public Event {

public:
	WallLocation wallLoc;
	int entityID;
	WallCollisionEvent(WallLocation loc, int id) :
			Event(EventType::EVENT_WALL_COLLISON) {
		wallLoc = loc;
		entityID = id;
	};
};
