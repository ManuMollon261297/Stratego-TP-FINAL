#include "Token.h"


Token::Token(notstd::rank k, ALLEGRO_BITMAP * i)
{
	TokenRank = k;
	image = i;
}

void Token::deleteBmps()
{
	if (image != nullptr)
	{
		al_destroy_bitmap(image);
	}
}
