#include "EventGenerator.h"


EventGenerator::EventGenerator(GameModel * gm_, NetworkingModel * nwm_, ALLEGRO_EVENT_QUEUE* ev_q)
{
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
	\
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



//	La funcion  getNextEvent supone que hay por lo menos un elemento en la lista, se debe preguntar antes
//si lo hay con la funcion hayEvento

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
	GenericEvent* p_event;
	switch (ev.type)		//Falta SOUND y corregir el de MOUSE.
	{
		case ALLEGRO_EVENT_TIMER:
			p_event = new GenericEvent;
			p_event->SetEvent(TIMER);
			break;
		//case ALLEGRO_EVENT_KEY_DOWN:
		//	p_event = new KeyboardEvent;
		//	break;
		//case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		//	p_event = new MouseEvent;
		//	break;	
		case ALLEGRO_EVENT_DISPLAY_CLOSE: //Es el unico evento del display que nos importa.
			p_event = new GenericEvent;
			p_event->SetEvent(GRAPHICS);
			break;
		default:
			p_event = new GenericEvent; //Eventos que ignoramos.
			p_event->SetEvent(OTHER);
			break;
	}
	if ((p_event->GetEvent()) != OTHER)
	{
		eventList.push_back(p_event);
	}
	
}



void EventGenerator::shape(std::string pckg)
{
	GenericEvent* eve = new NetWorkingEvent(pckg);
	eventList.push_back(eve);
}

