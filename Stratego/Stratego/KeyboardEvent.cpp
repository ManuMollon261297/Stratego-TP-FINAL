#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
{
	eventType = KEYBOARD;
}

KeyboardEvent::~KeyboardEvent()
{

}

unsigned int KeyboardEvent::GetEvent(void)
{
	return eventType;
}

void KeyboardEvent::SetEvent(unsigned int newEv)
{
	//eventType = newEv;
}

ALLEGRO_EVENT * KeyboardEvent::getAlEv(void)
{
	return alEvent;
}