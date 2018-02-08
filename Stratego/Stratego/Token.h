#pragma once
#include "ranks.h"
#include "allegro5\allegro.h"


class Token
{
public:
	Token(notstd::rank k, ALLEGRO_BITMAP * i);
	notstd::rank TokenRank;
	ALLEGRO_BITMAP * image;
	void deleteBmps();
};

