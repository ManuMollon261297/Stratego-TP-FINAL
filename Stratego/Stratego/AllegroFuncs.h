#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

void fade_out(int speed, int screenWidth, int screenHeight);
void fade_in(ALLEGRO_BITMAP * bmp_orig, int speed, int screenWidth, int screenHeight);