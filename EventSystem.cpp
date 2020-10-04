#include "EventSystem.h"


void EventSystem::subscribe(EventType eventType, System* system) {
	//If it dosn't already have that listener add it
	if (std::count(listeners[eventType].begin(), listeners[eventType].end(), system) == 0) {
		listeners[eventType].push_back(system);
	}
}

void EventSystem::dispatchEvent(Event* theEvent) {
	for (int i = 0; i < listeners[theEvent->getType()].size(); i++) {
		listeners[theEvent->getType()][i]->receiveEvent(theEvent);
	}
	
}

//Remove a given system from receving messages about a given eventtype
void EventSystem::unSubscribe(EventType eventType, System *system) {
	auto it = find(listeners[eventType].begin(), listeners[eventType].end(), system);
	listeners[eventType].erase(it);
}
