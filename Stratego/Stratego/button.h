#pragma once
#include "pos.h"

#define PLACE_READY_B 1
#define PLAY_AGAIN_B 2
#define GAME_OVER_B 3

class button
{
public:
	button(int index_, pos LL, pos HR);
	void press();
	void unpress();
	bool getPressStatus();
	int getIndex();
	bool isTouched(double x, double y);
	~button();
private:
	pos verticeLL; //low left
	pos verticeHR; //high right
	int index;
	bool pressed;
};

