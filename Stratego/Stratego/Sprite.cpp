#include "Sprite.h"

Sprite::Sprite(int code_)
{
	code = code_;
}


Sprite::~Sprite()
{
	/*
	for (int i = 0; i< sequence.size(); i++)
	{
		al_destroy_bitmap(sequence[i]);
	}
	*/
}

void Sprite::playSequence(int dx, int dy,int dw,int dh, bool facingLeft)
{
	ALLEGRO_BITMAP * dAux = al_get_target_bitmap();
	ALLEGRO_BITMAP * aux = al_clone_bitmap(dAux);
	int flag =0;
	if (!facingLeft)
	{
		flag = ALLEGRO_FLIP_HORIZONTAL;
	}
	for (int i = 0;i< sequence.size();i++)
	{
		al_draw_bitmap(aux, 0, 0, 0);
		al_draw_scaled_bitmap(sequence[i], 0, 0, al_get_bitmap_width(sequence[i]), al_get_bitmap_height(sequence[i]),
			dx, dy, dw, dh, flag);
		al_rest(0.06);
		al_flip_display();
		//si la animacion va muy rapido aca hay que poner un sleep 
	}
}

bool Sprite::pushImage(ALLEGRO_BITMAP * bitmap)
{
	if (bitmap != nullptr)
	{
		sequence.push_back(bitmap);
		return true;
	}
	else
	{
		return false;
	}
}

void Sprite::drawFirst(int x, int y, int width, int height, bool facingLeft)
{
	int flag = 0;
	if (!facingLeft)
	{
		flag = ALLEGRO_FLIP_HORIZONTAL;
	}
	al_draw_scaled_bitmap(sequence[0], 0, 0, al_get_bitmap_width(sequence[0]),
		al_get_bitmap_height(sequence[0]), x, y, width, height, flag);
}

void Sprite::flicker(int x, int y, int width, int height, bool facingLeft) //llamarlo sin la imagen primero 
{
	ALLEGRO_BITMAP * dAux = al_get_target_bitmap();
	ALLEGRO_BITMAP * aux = al_clone_bitmap(dAux);
	bool show = true;
	int flag = 0;
	if (!facingLeft)
	{
		flag = ALLEGRO_FLIP_HORIZONTAL;
	}
	for (int i = 0; i < 10; i++)
	{
		if (show)
		{
			al_draw_scaled_bitmap(sequence[0], 0, 0, al_get_bitmap_width(sequence[0]),
				al_get_bitmap_height(sequence[0]), x, y, width, height, flag);
			al_flip_display();
			al_rest(0.1);
			//agregar delay necesario
		}
		else
		{
			al_draw_bitmap(aux, 0, 0, 0);
			al_flip_display();
			al_rest(0.05);
			//agregar delay necesario
		}
		show = !show;
	}
}
