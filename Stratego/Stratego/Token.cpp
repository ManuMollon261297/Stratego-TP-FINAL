#include "Token.h"


Token::Token(rank k, ALLEGRO_BITMAP * i)
{
	TokenRank = k;
	image = i;
}

Token::~Token()
{
	al_destroy_bitmap(image);
}
