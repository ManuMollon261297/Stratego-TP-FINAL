#include "AllegroFuncs.h"

void fade_out(int speed, int screenWidth, int screenHeight)
{
	ALLEGRO_BITMAP *  dAux = al_get_target_bitmap();
	ALLEGRO_BITMAP *  aux;
	if (aux = al_clone_bitmap(dAux))
	{
		int a;
		if (speed <= 0)
		{
			speed = 16;
		}
		for (a = 0; a < 256; a += speed)
		{
			al_draw_scaled_bitmap(aux, 0, 0, al_get_bitmap_width(aux), al_get_bitmap_height(aux), 0, 0, screenWidth, screenHeight, 0);
			al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba(0, 0, 0, a));
			al_flip_display();
		}
		al_destroy_bitmap(aux);
	}
}

void fade_in(ALLEGRO_BITMAP * bmp_orig, int speed, int screenWidth, int screenHeight)
{
	ALLEGRO_BITMAP * bmp_buff;
	if (bmp_buff = al_create_bitmap(screenWidth, screenHeight))
	{
		int a;
		if (speed <= 0)
		{
			speed = 16;
		}
		for (a = 255; a >= 0; a -= speed)
		{
			al_draw_scaled_bitmap(bmp_orig, 0, 0, al_get_bitmap_width(bmp_orig), al_get_bitmap_height(bmp_orig), 0, 0, screenWidth, screenHeight, 0);
			al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba(0, 0, 0, a));
			al_flip_display();
		}
		al_destroy_bitmap(bmp_buff);
	}
}