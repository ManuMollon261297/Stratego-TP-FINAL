#pragma once
#include "pos.h"

class button
{
public:
	button(int index_, pos LL, pos HR);
	void press();
	void unpress();
	bool getPressStatus();
	int getIndex();
	~button();
private:
	pos verticeLL; //low left
	pos verticeHR; //high right
	int index;
	bool pressed;
};

