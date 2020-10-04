#include <map>
#include <vector>
#include "Enums.h"
#include "System.h"
#include "Events.h"

class EventSystem {
private:
	std::map<EventType, std::vector<System *> > listeners;

public:
	void subscribe(EventType eventType, System *system);
	void unSubscribe(EventType eventType, System *system);

	void dispatchEvent(Event * theEvent);


};
