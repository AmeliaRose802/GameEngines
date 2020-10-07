#include <map>
#include <vector>
#include "Enums.h"

class System;
class Event;

//Anything with access to the event system can dispatch an event. Only systems can receve events
class EventSystem
{
private:
	//Map event types to the listeners that care about them
	std::map<EventType, std::vector<System *> > listeners;

public:
	void subscribe(EventType eventType, System *system);
	void unsubscribe(EventType eventType, System *system);
	void dispatchEvent(Event * theEvent);
};
