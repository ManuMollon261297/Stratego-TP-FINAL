#include "Sprite.h"

Sprite::Sprite(int code_)
{
	code = code_;
}


Sprite::~Sprite()
{
	for (int i = 0; i< sequence.size(); i++)
	{
		al_destroy_bitmap(sequence[i]);
	}
}

void Sprite::playSequence(int dx, int dy,int dw,int dh, bool facingLeft)
{
	for (int i = 0;i< sequence.size();i++)
	{
		al_draw_scaled_bitmap(sequence[i], 0, 0, al_get_bitmap_height(sequence[i]), al_get_bitmap_width(sequence[i]),
			dx, dy, dw, dh, 0);
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
	al_draw_scaled_bitmap(sequence[0], 0, 0, al_get_bitmap_width(sequence[0]),
		al_get_bitmap_height(sequence[0]), x, y, width, height, 0);
}

void Sprite::flicker(int x, int y, int width, int height, bool facingLeft)
{
}
