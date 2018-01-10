#pragma once

#include "EventGenerator.h"
#include "boost\asio.hpp"
#include "Event.h"

class RefreshEvent : public GenericEvent
{
public:
	RefreshEvent();
	RefreshEvent(GenericEvent evnt);
	
	GameModel * gm_;
	NetworkingModel * nwm_;
	
	//Datos de Boost

	boost::asio::ip::tcp::socket* socket_;
};


