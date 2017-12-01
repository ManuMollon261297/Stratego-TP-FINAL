#include "AllegroButton.h"


AllegroButton::AllegroButton(ALLEGRO_BITMAP * b, int i)
{
	boton = b;
	index = i;
}

AllegroButton::~AllegroButton()
{
	al_destroy_bitmap(boton);
}
