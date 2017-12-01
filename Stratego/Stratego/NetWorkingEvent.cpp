#include "NetWorkingEvent.h"

NetWorkingEvent:: NetWorkingEvent(std::string package)
{
	eventType = NET;
	recieved = package; //Buffer recibido en el paquete de boost.
}

std::string NetWorkingEvent::GetRecieved()const
{
	return recieved;
}
