#pragma once
#include "pos.h"

class currStatus
{
public:
	currStatus();
	currStatus(pos prev, pos nex);
	currStatus(int x_prev, int y_prev, int x_nex,int y_nex);
	pos previous;
	pos next;
	~currStatus();

};

