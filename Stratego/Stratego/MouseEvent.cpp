#include "MouseEvent.h"

MouseEvent::MouseEvent(ALLEGRO_EVENT ev)
{
	SetEvent(MOUSE);
	x = ev.mouse.x;
	y = ev.mouse.y;
}