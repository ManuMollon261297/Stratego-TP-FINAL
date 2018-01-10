#pragma once

#include <list>
#include "State.h"
#include "Event.h"
#include "allegro5\allegro.h"
#include "boost\asio.hpp"

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
	//std::list<WormInfo>::iterator getListIterator();

private:
	void shape(ALLEGRO_EVENT ev);
	void shape(char * buf, unsigned int cant);
	//bool DetectLittleEndian(void);

	ALLEGRO_EVENT_QUEUE * eventQueue;
	ALLEGRO_EVENT evento;
	
	GameModel * gm;
	NetworkingModel * nwm;


	char buffer[512];

	std::list<GenericEvent*> eventList;
	
	boost::asio::ip::tcp::socket* socket_; //lo necesario para poder leer y escribir
};

