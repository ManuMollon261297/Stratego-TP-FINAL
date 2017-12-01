#pragma once
#include "ranks.h"
#include "allegro5\allegro.h"
class Token
{
public:
	Token(rank k, ALLEGRO_BITMAP * i);
	rank TokenRank;
	ALLEGRO_BITMAP * image;
	~Token();
};

