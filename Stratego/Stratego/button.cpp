#include "button.h"




button::button(int index_, pos LL, pos HR)
{
	index = index_;
	verticeLL = LL;
	verticeHR = HR;
}

void button::press()
{
	pressed = true;
}

void button::unpress()
{
	pressed = false;
}

bool button::getPressStatus()
{
	return pressed;
}

int button::getIndex()
{
	return index;
}

button::~button()
{
}
