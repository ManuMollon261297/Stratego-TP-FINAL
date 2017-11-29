#pragma once
class pos
{
public:
	pos(int x_, int y_);
	pos();
	int x;
	int y;
	bool operator==(pos pos_);
	~pos();
};

