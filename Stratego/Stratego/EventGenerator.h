#pragma once

#include <list>
#include "State.h"
#include "Event.h"
#include "allegro5\allegro.h"

#include "GameModel.h"
#include "NetworkingModel.h"


#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "NetWorkingEvent.h"

#include "RefreshEvent.h"


class EventGenerator
{
public:
	EventGenerator(GameModel * gm_, NetworkingModel * nwm_, ALLEGRO_EVENT_QUEUE* ev_q);
	~EventGenerator();
	void searchForEvents();
	bool hayEvento();
		
	GenericEvent* getNextEvent();

private:
	void shape(ALLEGRO_EVENT ev);
	void shape(std::string);

	ALLEGRO_EVENT_QUEUE * eventQueue;
	ALLEGRO_EVENT evento;
	
	GameModel * gm;
	NetworkingModel * nwm;



	std::list<GenericEvent*> eventList;
};

