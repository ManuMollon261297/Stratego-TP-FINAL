#pragma once

#include "Event.h"
#include <allegro5\allegro.h>

class KeyboardEvent : public GenericEvent
{
public:
	KeyboardEvent();
	~KeyboardEvent();

	virtual unsigned int GetEvent(void);
	virtual void SetEvent(unsigned int);

	ALLEGRO_EVENT * getAlEv(void);
	
private:
	ALLEGRO_EVENT * alEvent;
};