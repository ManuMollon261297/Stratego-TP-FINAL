#include "EventGenerator.h"


EventGenerator::EventGenerator(GameModel * gm_, NetworkingModel * nwm_, ALLEGRO_EVENT_QUEUE* ev_q)
{
	for (int i = 0; i < 512; i++)
	{
		buffer[i] = 0;
	}

	gm = gm_;
	nwm = nwm_;
	eventQueue = ev_q;
}

EventGenerator::~EventGenerator()
{
	if (!eventList.empty()) //vacio las listas para que ya no puedan ser accedidas
	{
		eventList.clear();
	}
}

void EventGenerator::searchForEvents()
{
	bool finished = false;

	size_t cant;
	while (!finished)
	{
		if (al_get_next_event(eventQueue, &evento)) //Eventos de Allegro
		{
			shape(evento);
			finished = true;
		}
		else if (!(nwm->GetReading())) //Eventos de Boost
		{
			nwm->StartReading();
		}
		if (nwm->WasPackageRecieved())
		{
			shape(nwm->GetPackage());
			finished = true;
		}
	}
			
}

bool EventGenerator::hayEvento()
{
	if (eventList.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


/*
	La funcion  getNextEvent supone que hay por lo menos un elemento en la lista, se debe preguntar antes
	si lo hay con la funcion hayEvento
*/
GenericEvent * EventGenerator::getNextEvent()
{
	std::list<GenericEvent*>::iterator it= eventList.begin();
	GenericEvent*   current_ev = (*it);
	eventList.pop_front();
	return current_ev;
}

enum {ioEvent,otherEvent};

void EventGenerator::shape(ALLEGRO_EVENT ev)
{
	int type;
	GenericEvent events;
	switch (ev.type)		//Falta SOUND, GRAPHICS, ver TIMER (ver tipo de evento de TIMER, hasta ahora son todos ioEvent)
		
							//NET, GRAPHICS, KEYBOARD, MOUSE, SOUND, TIMER

	{
		case ALLEGRO_EVENT_TIMER:
			events.SetEvent(TIMER);
			events.SetUd(0);
			type = ioEvent;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			events.SetEvent(KEYBOARD);
			type = ioEvent;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			events.SetEvent(MOUSE);
			type = ioEvent;
			break;		
		default:
			type = otherEvent;
			break;
	}
	if (type == ioEvent)
	{
		if (!(events.GetEvent() == QUIT))				//Ver para que tipo de evento no guardo informacion
		{
			GenericEvent * genEv = new RefreshEvent(events);

			((RefreshEvent*)genEv)->gm_ = gm;			//ver
			((RefreshEvent*)genEv)->nwm_ = nwm;			//ver
			
			((RefreshEvent*)genEv)->socket_ = socket_;
			eventList.push_back(genEv);
		}
		else 
		{
			GenericEvent * genEve = new RefreshEvent(events);
			((RefreshEvent*)genEve)->socket_ = socket_;
			eventList.push_back(genEve);
		}
	}
	else if (type == otherEvent)
	{
		//no nos interesa otro tipo de evento para este tp
	}
}



void EventGenerator::shape(std::string pckg)
{
	GenericEvent* eve = new NetWorkingEvent(pckg);
	eventList.push_back(eve);
}


/*
Little Endian --> True
Big Endian -----> False
*/
bool EventGenerator::DetectLittleEndian(void)
{
	bool returnValue = true;

	uint32_t temp = 1;

	uint32_t *ptemp = &temp;

	char firstByte = *((char *)ptemp);		//Tomo el primer byte EN MEMORIA de temp:
											//Little:	01 00 00 00
											//Big:		00 00 00 01
	if (firstByte)
	{
		returnValue = true;
	}
	else
	{
		returnValue = false;
	}

	return returnValue;
}