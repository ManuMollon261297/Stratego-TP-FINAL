#pragma once
#include "allegro5\allegro.h"
class AllegroButton
{
public:
	AllegroButton(ALLEGRO_BITMAP * b,int i);
	ALLEGRO_BITMAP * boton;
	int index;
	~AllegroButton();
};

