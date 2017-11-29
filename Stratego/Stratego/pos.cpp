#include "pos.h"



pos::pos(int x_, int y_)
{
	x = x_;
	y = y_;
}

pos::pos()
{
	x = 0;
	y = 0;
}


bool pos::operator==(pos pos_)
{
	if ((pos_.x == this->x) && (pos_.y == this->y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

pos::~pos()
{
}
