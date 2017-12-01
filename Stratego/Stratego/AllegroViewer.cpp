#include "AllegroViewer.h"

#define CASO_ESPECIAL(r, q) ( ((r == MINER) && (q == BOMB)) || ((r == SPY) && (q == MARSHAL)) )
#define PLAYER_CH screenWidth / 4, screenHeight / 3, 100, 100, false
#define OPPONENT_CH (3*screenWidth) / 4, screenHeight / 3, 100, 100, true
AllegroViewer::AllegroViewer(int h, int w, GameModel &gm,colour c) : engine(gm) //CAMBIAR VALORES DE LOS FORS CUANDO YA ESTEN LA IMAGENES
{
	color = c;
	attackPending = false;
	screenHeight = h;
	screenWidth = w;
	fichaHeight = (h / 11);
	fichaWidth = (w / 12);
	//inicializacion de allegro
	if (al_init()&& al_init_font_addon()&&al_init_primitives_addon()&&al_init_image_addon()) //SACAR AL_INIT
	{
		ALLEGRO_display = al_create_display(w, h);
		initialized = true;
	}
	else
	{
		initialized = false;
	}
	//inicializacion de strings
	for (int i =0;i<13;i++)
	{
		char caux = '0' + i;
		std::string aux = "\\Allegro Data\\BT\\" + caux;
		aux +=".png";
		BlueFichaImagesDir.push_back(aux);
	}
	for (int i = 0; i<13; i++)
	{
		char caux = '0' + i;
		std::string aux = "\\Allegro Data\\RT\\" + caux;
		aux += ".png";
		BlueFichaImagesDir.push_back(aux);
	}
	for (int i = 0; i<0/*CAMBIAR*/; i++)
	{
		char caux = '0' + i;
		std::string aux = "\\Allegro Data\\GO\\" + caux;
		aux += ".png";
		GameOverDir.push_back(aux);
	}
	botonDir = "\\Allegro Data\\button.png";
	battleBackgroundDir = "\\Allegro Data\\battleBackground.png";
	mapDir = "\\Allegro Data\\map.png";
	menuBackgroundDir = "\\Allegro Data\\menuBackground.png";
	muteDir = "\\Allegro Data\\mute.png";
	unMuteDir = "\\Allegro Data\\unmute.png";
	nameInputDir = "\\Allegro Data\\nameInput.png";
	fieldDir = "\\Allegro Data\\field.png";
	for (int i = 0; i<0/*CAMBIAR*/; i++)
	{
		char caux1 = '0' + i;
		for (int j = 0; j<0/*CAMBIAR*/; j++)
		{
			char caux2 = '0' + j;
			std::string aux = "\\Allegro Data\\BC\\" + caux1;
			aux += '//' + caux2;
			aux += ".png";
			GameOverDir.push_back(aux);
		}
	}
	for (int i = 0; i<0/*CAMBIAR*/; i++)
	{
		char caux1 = '0' + i;
		for (int j = 0; j<0/*CAMBIAR*/; j++)
		{
			char caux2 = '0' + j;
			std::string aux = "\\Allegro Data\\RC\\" + caux1;
			aux += '//' + caux2;
			aux += ".png";
			GameOverDir.push_back(aux);
		}
	}
	titlettfDir = "\\Allegro Data\\Prince Valiant.ttf";
	messagettfDir = "\\Allegro Data\\ARDED___.TTF";
	//nullptr a todos los punteros
	ALLEGRO_battleBackground = nullptr;
	ALLEGRO_map = nullptr;
	ALLEGRO_menuBackground = nullptr;
	ALLEGRO_boton = nullptr;
	ALLEGRO_mute = nullptr;
	ALLEGRO_unMute = nullptr;
	ALLEGRO_nameInput = nullptr;
	ALLEGRO_titlettf = nullptr;
	ALLEGRO_optionsttf = nullptr;
	ALLEGRO_messagesttf = nullptr;
	ALLEGRO_display = nullptr;
	ALLEGRO_field = nullptr;
}

bool AllegroViewer::isViewerInitialized()
{
	return initialized;
}

void AllegroViewer::initImagesAndFonts() //TERMINAR EL MAX DEL FOR DE SPRITES
{
	for (int i = 0; i < BlueFichaImagesDir.size(); i++)
	{
		Token tAux((rank)i, al_load_bitmap(BlueFichaImagesDir[i].c_str()));
		ALLEGRO_BlueFichaImages.push_back(tAux);
	}
	for (int i = 0; i < RedFichaImagesDir.size(); i++)
	{
		Token tAux((rank)i, al_load_bitmap(RedFichaImagesDir[i].c_str()));
		ALLEGRO_RedFichaImages.push_back(tAux);
	}
	for (int i = 0; i < BlueCharactersDir.size(); i++)
	{
		Sprite sAux(i);
		std::string aux = BlueCharactersDir[i];
		for (int j =0;j<10;j++)
		{
			char auxCh = '0' + j;
			aux =+ '/'+auxCh+ ".png";
			sAux.pushImage(al_load_bitmap(aux.c_str()));
		}
		ALLEGRO_BlueCharacters.push_back(sAux);
	}
	for (int i = 0; i < RedCharactersDir.size(); i++)
	{
		Sprite sAux(i);
		std::string aux = RedCharactersDir[i];
		for (int j = 0; j<10; j++)
		{
			char auxCh = '0' + j;
			aux = +'/' + auxCh + ".png";
			sAux.pushImage(al_load_bitmap(aux.c_str()));
		}
		ALLEGRO_RedCharacters.push_back(sAux);
	}
	for(int i=0;i<0/*CAMBIAR*/;i++)
	{
		ALLEGRO_BITMAP * aux = al_load_bitmap(GameOverDir[i].c_str());
		ALLEGRO_GameOver.push_back(aux);
	}
	ALLEGRO_boton = al_load_bitmap(botonDir.c_str());
	ALLEGRO_battleBackground = al_load_bitmap(battleBackgroundDir.c_str());
	ALLEGRO_map = al_load_bitmap(mapDir.c_str());
	ALLEGRO_menuBackground = al_load_bitmap(menuBackgroundDir.c_str());
	ALLEGRO_mute = al_load_bitmap(muteDir.c_str());
	ALLEGRO_unMute = al_load_bitmap(unMuteDir.c_str());
	ALLEGRO_nameInput = al_load_bitmap(nameInputDir.c_str());
	ALLEGRO_field = al_load_bitmap(fieldDir.c_str());
	ALLEGRO_titlettf = al_load_font(titlettfDir.c_str(), 20, 0);	//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_optionsttf = al_load_font(optionsttfDir.c_str(), 15, 0);//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_messagesttf = al_load_font(messagettfDir.c_str(), 5, 0);//cambiar el tamanio de la letra aca si es necesario
}

void AllegroViewer::drawBattlefield()
{
	al_draw_bitmap(ALLEGRO_map, fichaWidth, fichaHeight, 0);
	for (int i =0;i<10;i++)
	{
		for (int j =0;j<10;j++)
		{
			pos pAux(i, j);
			rank rAux = engine.getRankFromPos(pAux);
			if ((rAux != rank::WATER)&&(rAux != rank::LAND)&&(rAux != rank::OTHERS))
			{
				if (color == BLUE)
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
				else
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
			else if (rAux == rank::OTHERS)
			{
				if (color == BLUE)
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
				else
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
		}
	}
}

void AllegroViewer::drawCemetery()
{
	for (int i =0;i<10;i++)
	{
		pos pAux(i, 0);
		rank rAux = (rank)i;
		if (color == BLUE)
		{
			al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
				(i + 1)*fichaWidth + 5, 5, fichaWidth - 5, fichaHeight - 5, 0);
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), 0, fichaWidth*(i + 1 / 2), 0, "%d", engine.getNumberInCemetery(rAux));
		}
		else
		{
			al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
				(i + 1)*fichaWidth + 5, 5, fichaWidth - 5, fichaHeight - 5, 0);
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), 0, fichaWidth*(i + 1 / 2), 0, "%d", engine.getNumberInCemetery(rAux));
		}
	}
}

void AllegroViewer::highligthToken(pos init)
{
	drawHalo(init.x*fichaWidth + 5, init.y*fichaHeight + 5, fichaWidth, fichaHeight);
}

void AllegroViewer::highlightCemetery(rank r)
{
	drawHalo(5, fichaHeight*((int)r + 1) + 5, fichaWidth, fichaHeight);
}

void AllegroViewer::drawMessage()
{
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), 0, 5, 5, engine.getMessage().c_str());
}

void AllegroViewer::drawGameOver(bool playerWon)
{
	for (int i=0;i<ALLEGRO_GameOver.size();i++)
	{
		al_draw_scaled_bitmap(ALLEGRO_GameOver[i], 0, 0, al_get_bitmap_width(ALLEGRO_GameOver[i]),
			al_get_bitmap_height(ALLEGRO_GameOver[i]), 0, 0, screenWidth, screenHeight, 0);
	}
	if (playerWon)
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), screenWidth / 10, screenHeight / 2, 0, "You Won!");
	}
	else
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), screenWidth / 10, screenHeight / 2, 0, "You Lost!");
	}
}

void AllegroViewer::drawRemainingTime()
{
	int total = engine.getTime();
	int minutes = total / 60;
	int seconds = total % 60;
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth-100, 5, 0, "%d:%d",minutes,seconds);
}

void AllegroViewer::playBattleWarmUp(rank playerRank) //TERMINAR FADE IN
{
	for (int i = 1; i <= 10; i++)
	{
		ALLEGRO_COLOR color;
		color.a = 0+(10*i);
		color.r = 0;
		color.g = 0;
		color.b = 0;
		al_draw_tinted_scaled_bitmap(ALLEGRO_field, color, 0, 0, al_get_bitmap_width(ALLEGRO_field),
			al_get_bitmap_width(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
		al_flip_display();
	}
	switch (color)
	{
	case RED:
		ALLEGRO_RedCharacters[(int)playerRank].drawFirst(PLAYER_CH);
		break;
	case BLUE:
		ALLEGRO_BlueCharacters[(int)playerRank].drawFirst(PLAYER_CH);
		break;
	}
	al_flip_display();
}

void AllegroViewer::moveToken(pos init, pos fin)
{
	al_draw_bitmap(ALLEGRO_map, fichaWidth, fichaHeight, 0);
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			if ((i != init.x) && (j != init.y))
			{
				pos pAux(i, j);
				rank rAux = engine.getRankFromPos(pAux);
				if ((rAux != rank::WATER) && (rAux != rank::LAND) && (rAux != rank::OTHERS))
				{
					if (color == BLUE)
					{
						al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
							(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
					}
					else
					{
						al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
							(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
					}
				}
				else if (rAux == rank::OTHERS)
				{
					if (color == BLUE)
					{
						al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
							(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
					}
					else
					{
						al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
							(i + 1)*fichaWidth + 5, (j + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
					}
				}
			}
		}
	}
	drawCemetery();
	drawMessage();
	drawRemainingTime();
	ALLEGRO_BITMAP *  aux = al_get_target_bitmap();
	rank currR = engine.getRankFromPos(init);
	if (init.x == fin.x) //se mueve verticalmente
	{
		int offset = (int)abs((init.y - fin.y));
		int totalOffset = offset*fichaHeight;
		for (int i =0;i<totalOffset;i++)
		{
			al_draw_bitmap(aux, 0, 0, 0);
			if (init.y > fin.y) //se mueve para arriba
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.x+1)*fichaWidth + 5, (init.y+ 1)*fichaHeight + 5-i, fichaWidth - 5, fichaHeight - 5, 0);
					//agregar sleep si es necesario

				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5, (init.y + 1)*fichaHeight + 5-i, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
			else //se mueve para abajo
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5, (init.y + 1)*fichaHeight + 5+i, fichaWidth - 5, fichaHeight - 5, 0);
				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5, (init.y + 1)*fichaHeight + 5+i, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
			al_flip_display();
		}
	}
	else if (init.y == fin.y) //se mueve horizontalmente
	{
		int offset = (int)abs((init.x - fin.x));
		int totalOffset = offset*fichaWidth;
		for (int i = 0; i<totalOffset; i++)
		{
			al_draw_bitmap(aux, 0, 0, 0);
			if (init.x > fin.x) //se mueve para la izquierda
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.x + 1)*fichaWidth + 5-i, (init.y + 1)*fichaHeight + 5 , fichaWidth - 5, fichaHeight - 5, 0);
					//agregar sleep si es necesario

				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5-i, (init.y + 1)*fichaHeight + 5 + i, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
			else //se mueve para la derecha
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5+i, (init.y + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(init.x + 1)*fichaWidth + 5+i, (init.y + 1)*fichaHeight + 5, fichaWidth - 5, fichaHeight - 5, 0);
				}
			}
			al_flip_display();
		}
	}
	else
	{
		//movimiento invalido
	}

}

void AllegroViewer::update()
{
}
enum whoWon{PLAYER,OPPONENT,TIE};

void AllegroViewer::playBattle(rank playerRank, rank opponentRank)
{
	whoWon status;
	switch (engine.getState()) //asumo sprites mirando a la izquierda
	{
	case MY_ATTACKING:
			if (opponentRank == FLAG)
			{
				status = PLAYER;
			}
			else if (CASO_ESPECIAL(playerRank, opponentRank) || (playerRank < opponentRank))
			{
				status = PLAYER;
			}
			else if (playerRank == opponentRank)
			{
				status = TIE;
			}
			else
			{
				status = OPPONENT;
			}
			break;
	case OP_ATTACKING:
		if (playerRank == FLAG)
		{
			status = OPPONENT;
		}
		else if ((CASO_ESPECIAL(opponentRank, playerRank)) || ((opponentRank < playerRank) && (playerRank != BOMB))) //entra si gano el opponent
		{
			status = OPPONENT;
		}
		else if (playerRank == opponentRank) //empate
		{
			status = TIE;
		}
		else //gane
		{
			status = PLAYER;
		}
		break;
	}
	switch (status)
	{
	case PLAYER:
		switch (color)
		{
		case RED:
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_RedCharacters[playerRank].playSequence(PLAYER_CH);
			ALLEGRO_BlueCharacters[opponentRank].flicker(OPPONENT_CH);
			break;
		case BLUE:
			ALLEGRO_RedCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_BlueCharacters[playerRank].playSequence(PLAYER_CH);
			ALLEGRO_RedCharacters[opponentRank].flicker(OPPONENT_CH);
			break;
		}
		break;
	case OPPONENT:
		switch (color)
		{
		case RED:
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_BlueCharacters[opponentRank].playSequence(OPPONENT_CH);
			ALLEGRO_RedCharacters[playerRank].flicker(PLAYER_CH);
			break;
		case BLUE:
			ALLEGRO_RedCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_RedCharacters[opponentRank].playSequence(OPPONENT_CH);
			ALLEGRO_BlueCharacters[playerRank].flicker(PLAYER_CH);
			break;
		}
		break;
	case TIE:
		switch (color)
		{
		case RED:
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_BlueCharacters[opponentRank].playSequence(OPPONENT_CH);
			ALLEGRO_RedCharacters[playerRank].playSequence(PLAYER_CH);
			ALLEGRO_RedCharacters[playerRank].flicker(PLAYER_CH);
			ALLEGRO_BlueCharacters[opponentRank].flicker(OPPONENT_CH);
			break;
		case BLUE:
			ALLEGRO_RedCharacters[opponentRank].drawFirst(OPPONENT_CH);
			ALLEGRO_RedCharacters[opponentRank].playSequence(OPPONENT_CH);
			ALLEGRO_BlueCharacters[playerRank].playSequence(PLAYER_CH);
			ALLEGRO_BlueCharacters[playerRank].flicker(PLAYER_CH);
			ALLEGRO_RedCharacters[opponentRank].flicker(OPPONENT_CH);
			break;
		}
		break;
	}
}

void AllegroViewer::drawHalo(double x, double y, double sizeX, double sizeY)
{
	for (int i = 1; i <= 5; i++)
	{
		al_draw_rectangle(x - i, y - i, x + sizeX + i, y + sizeY + i, al_map_rgb(0, 255 - i * 20, 0), 1.0);
	}
}

AllegroViewer::~AllegroViewer()
{
	if (ALLEGRO_battleBackground != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_battleBackground);
		ALLEGRO_battleBackground = nullptr;
	}
	if (ALLEGRO_map != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_map);
		ALLEGRO_map = nullptr;
	}
	if (ALLEGRO_menuBackground != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_menuBackground);
		ALLEGRO_menuBackground = nullptr;
	}
	if (ALLEGRO_boton != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_boton);
		ALLEGRO_boton = nullptr;
	}
	if (ALLEGRO_mute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_mute);
		ALLEGRO_mute = nullptr;
	}
	if (ALLEGRO_unMute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_unMute);
		ALLEGRO_unMute = nullptr;
	}
	if (ALLEGRO_nameInput != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_nameInput);
		ALLEGRO_nameInput = nullptr;
	}
	if (ALLEGRO_titlettf != nullptr)
	{
		al_destroy_font(ALLEGRO_titlettf);
		ALLEGRO_titlettf = nullptr;
	}
	if (ALLEGRO_optionsttf != nullptr)
	{
		al_destroy_font(ALLEGRO_optionsttf);
		ALLEGRO_optionsttf = nullptr;
	}
	if (ALLEGRO_messagesttf != nullptr)
	{
		al_destroy_font(ALLEGRO_messagesttf);
		ALLEGRO_messagesttf = nullptr;
	}
	if (ALLEGRO_display != nullptr)
	{
		al_destroy_display(ALLEGRO_display);
		ALLEGRO_display = nullptr;
	}
	for (int i = 0; i < ALLEGRO_GameOver.size() ; i++)
	{
		if (ALLEGRO_GameOver[i] != nullptr)
		{
			al_destroy_bitmap(ALLEGRO_GameOver[i]);
			ALLEGRO_GameOver[i] = nullptr;
		}
	}
}
