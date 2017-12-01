#pragma once

#include "allegro5\allegro.h"
#include <vector>

class Sprite
{
public:
	Sprite(int code);
	~Sprite(); //se ocupa de eliminar as imagenes
	void playSequence(int x, int y, int width, int height);	// dibuja la secuencia en el rango dado por los parametros
															// puntos "x","y" del vertice High Left
	bool pushImage(ALLEGRO_BITMAP * bitmap); //agrega a final del vector una imagen para la sequencia, al final se 
											 // ocupa de eliminarlas
private:
	std::vector<ALLEGRO_BITMAP *> sequence;
	int code; //en nuestro caso sera igual al rank de nuestra ficha para simplificar el uso
};

