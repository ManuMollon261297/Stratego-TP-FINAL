#pragma once
#include <iostream>
#include "Event.h"





class NetWorkingEvent : public GenericEvent
{
public:
	NetWorkingEvent(std::string package);
	std::string GetRecieved()const;
private:
	std::string recieved;
};