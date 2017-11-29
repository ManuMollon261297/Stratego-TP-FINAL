#pragma once
#include "pos.h"

class button
{
public:
	button();
	pos verticeLL; //low left
	pos verticeHR; //high right
	int index;
	bool pressed; // setters y getters
	~button();
};

