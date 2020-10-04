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
	int aID;
	int bID;

	public:
	CollisionEvent(int idA, int idB) :
			Event(EventType::EVENT_COLLISION)
	{
		aID = idA;
		bID = idB;
	};
};
