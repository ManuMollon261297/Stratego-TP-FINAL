#include "Event.h"

//Getters y Setters
unsigned int GenericEvent:: GetEvent(void)
{
	return eventType;
}

void GenericEvent::SetEvent(unsigned int type)
{
	eventType = type;
}
char GenericEvent::GetUd(void)
{
	return ud;
}
void GenericEvent::SetUd(char dir)
{
	ud = dir;
}
