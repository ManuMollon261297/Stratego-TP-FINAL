#include "currStatus.h"



currStatus::currStatus()
{
	pos prev(0,0);
	pos nex(0,0);
	previous = prev;
	next = nex;
}

currStatus::currStatus(pos prev, pos nex)
{
	previous = prev;
	next = nex;
}

currStatus::currStatus(int x_prev, int y_prev, int x_nex, int y_nex)
{
	pos prev(x_prev, y_prev);
	pos nex(x_nex, y_nex);
	previous = prev;
	next = nex;
}


currStatus::~currStatus()
{
}
