#include "Event.h"

//Getters y Setters
unsigned int GenericEvent:: GetEvent(void)
{
	return eventType;
}

void GenericEvent::SetEvent(unsigned int type)
{
	eventType = (ev)type;
}
