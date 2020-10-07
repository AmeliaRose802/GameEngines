#pragma once
#include <map>
#include <vector>
#include "Component.h"

//Foward declare
class EventSystem;
class PongNode;
class Event;

//Base class for systems. All systems can receve events and have refrences to the event system and the pong node
class System
{
protected:
	PongNode *pongNode;
	EventSystem *eventSystem;

public:
	System(EventSystem * theEventSystem, PongNode * thePongNode) {
		pongNode = thePongNode;
		eventSystem = theEventSystem;
	}
	~System(){};
	virtual void receiveEvent(Event *event){}; 
};
