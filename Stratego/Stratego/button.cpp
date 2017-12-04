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

bool button::isTouched(double x, double y)
{
	bool ret = false;

	if ((x > verticeLL.x) && (x < verticeHR.x) && (y > verticeHR.y) && (y < verticeLL.y))
	{
		ret = true;
	}

	return ret;
}

button::~button()
{
}
