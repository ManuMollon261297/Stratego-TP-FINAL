#include "mouseMenuEvent.h"

mouseMenuEvent::mouseMenuEvent(ALLEGRO_EVENT ev)
{
	SetEvent(MOUSE);
	x = ev.mouse.x;
	y = ev.mouse.y;

}