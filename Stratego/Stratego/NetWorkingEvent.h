#pragma once
#include <iostream>
#include "Event.h"

/*
enum NetWorkingTypeEvent
{
PLAY_AGAIN, NAME, NAME_IS, R_U_READY, I_START, YOU_START,
ERROR, QUIT, ACK, GAME_OVER, MOVE, ATTACK, YOU_WON
};
*/



class NetWorkingEvent : public GenericEvent
{
public:
	NetWorkingEvent(std::string package);
	std::string GetRecieved()const;
private:
	std::string recieved;
};