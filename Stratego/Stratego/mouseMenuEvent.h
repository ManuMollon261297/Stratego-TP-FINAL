#pragma once
#include "Event.h"
#include "allegro5\allegro.h"



class mouseMenuEvent : public GenericEvent
{
public:
	mouseMenuEvent(ALLEGRO_EVENT ev);
	int x;
	int y;
};