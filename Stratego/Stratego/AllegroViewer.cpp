#include "AllegroViewer.h"
#include "currStatus.h"

#define CASO_ESPECIAL(r, q) ( ((r == MINER) && (q == BOMB)) || ((r == SPY) && (q == MARSHAL)) )
#define DIF_A_POS_INICIAL !((i == init.x) && (j == init.y))
#define DIF_A_POS_FINAL !((i == fin.x) && (j == fin.y))

enum whoWon { PLAYER, OPPONENT, TIE };

AllegroViewer::AllegroViewer(GameModel &gm,colour c, ALLEGRO_DISPLAY * disp, int h, int w) : engine(gm)
{
	color = c;
	attackPending = false;
	sound = false;
	screenHeight = h;
	screenWidth = w;
	fichaHeight = (h / 11);
	fichaWidth = (w / 12);
	//inicializacion de allegro
	ALLEGRO_display = disp;
	if (al_init_font_addon()&&al_init_primitives_addon()&&al_init_image_addon()
		&&al_init_ttf_addon()&& al_install_audio() && al_init_acodec_addon())
	{
		initialized = true;
	}
	else
	{
		initialized = false;
	}
	al_reserve_samples(4);
	//inicializacion de strings
	for (int i =0;i<13;i++)
	{
		std::string aux = "../Allegro Data/BT/";
		if (i <= 9)
		{
			char caux = '0' + i;
			aux.push_back(caux);
		}
		else
		{
			char caux1;
			char caux2;
			caux1 = '0' + (i / 10);
			caux2 = '0' + (i % 10);
			aux.push_back(caux1);
			aux.push_back(caux2);
		}
		aux +=".png";
		BlueFichaImagesDir.push_back(aux);
	}
	for (int i = 0; i<13; i++)
	{
		std::string aux = "../Allegro Data/RT/";
		if (i <= 9)
		{
			char caux = '0' + i;
			aux.push_back(caux);
		}
		else
		{
			char caux1;
			char caux2;
			caux1 = '0' + (i / 10);
			caux2 = '0' + (i % 10);
			aux.push_back(caux1);
			aux.push_back(caux2);
		}
		aux += ".png";
		RedFichaImagesDir.push_back(aux);
	}
	for (int i = 0; i<1; i++)
	{
		char caux = '0' + i;
		std::string aux = "../Allegro Data/GO/";
		aux.push_back(caux);
		aux += ".png";
		GameOverDir.push_back(aux);
	}
	botonDir = "../Allegro Data/button.png";
	battleBackgroundDir = "../Allegro Data/battleBackground.png";
	mapDir = "../Allegro Data/map.png";
	muteDir = "../Allegro Data/mute.png";
	unMuteDir = "../Allegro Data/unmute.png";
	fieldDir = "../Allegro Data/field.png";
	shuffleDir = "../Allegro Data/shuffle.png";
	attackDir = "../Allegro Data/AUDIO/attack1.wav";
	deathDir = "../Allegro Data/AUDIO/death.wav";
	introDir = "../Allegro Data/AUDIO/intro.wav";
	soundtrackDir = "../Allegro Data/AUDIO/soundtrack.wav";
	int jmax;
	for (int i = 0; i<=11; i++)
	{
		std::vector<std::string> auxV;
		jmax = getCantSprites(i);
		if (i <= 9)
		{
			char caux = '0' + i;
			for (int j = 0; j<jmax; j++)
			{
				//char caux2 = '0' + j;
				std::string aux = "../Allegro Data/BC/";
				aux.push_back(caux);
				aux += '/';
				if (j <= 9)
				{
					char caux2 = '0' + j;
					aux.push_back(caux2);
				}
				else
				{
					char caux3;
					char caux4;
					caux3 = '0' + (j / 10);
					caux4 = '0' + (j % 10);
					aux.push_back(caux3);
					aux.push_back(caux4);
				}
				aux += ".png";
				auxV.push_back(aux);
			}
		}
		else
		{
			char caux1;
			char caux2;
			caux1 = '0' + (i / 10);
			caux2 = '0' + (i % 10);
			for (int j = 0; j<jmax; j++)
			{
				//char caux2 = '0' + j;
				std::string aux = "../Allegro Data/BC/";
				aux.push_back(caux1);
				aux.push_back(caux2);
				aux += '/';
				if (j <= 9)
				{
					char caux2 = '0' + j;
					aux.push_back(caux2);
				}
				else
				{
					char caux3;
					char caux4;
					caux3 = '0' + (j / 10);
					caux4 = '0' + (j % 10);
					aux.push_back(caux3);
					aux.push_back(caux4);
				}
				aux += ".png";
				auxV.push_back(aux);
			}
		}
		BlueCharactersDir.push_back(auxV);
	}
	for (int i = 0; i<=11; i++)
	{
		std::vector<std::string> auxV;
		jmax = getCantSprites(i);
		if (i <= 9)
		{
			char caux = '0' + i;
			for (int j = 0; j<jmax; j++)
			{
				std::string aux = "../Allegro Data/RC/";
				aux.push_back(caux);
				aux += '/';
				if (j <= 9)
				{
					char caux2 = '0' + j;
					aux.push_back(caux2);
				}
				else
				{
					char caux3;
					char caux4;
					caux3 = '0' + (j / 10);
					caux4 = '0' + (j % 10);
					aux.push_back(caux3);
					aux.push_back(caux4);
				}
				aux += ".png";
				auxV.push_back(aux);
			}
		}
		else
		{
			char caux1;
			char caux2;
			caux1 = '0' + (i / 10);
			caux2 = '0' + (i % 10);
			for (int j = 0; j<jmax; j++)
			{
				std::string aux = "../Allegro Data/RC/";
				aux.push_back(caux1);
				aux.push_back(caux2);
				aux += '/';
				if (j <= 9)
				{
					char caux2 = '0' + j;
					aux.push_back(caux2);
				}
				else
				{
					char caux3;
					char caux4;
					caux3 = '0' + (j / 10);
					caux4 = '0' + (j % 10);
					aux.push_back(caux3);
					aux.push_back(caux4);
				}
				aux += ".png";
				auxV.push_back(aux);
			}
		}
		RedCharactersDir.push_back(auxV);
	}
	titlettfDir = "../Allegro Data/Prince Valiant.ttf";
	optionsttfDir = "../Allegro Data/Prince Valiant.ttf";
	messagettfDir = "../Allegro Data/Eutemia-I Italic.ttf";
	//nullptr a todos los punteros
	ALLEGRO_battleBackground = nullptr;
	ALLEGRO_map = nullptr;
	ALLEGRO_boton = nullptr;
	ALLEGRO_mute = nullptr;
	ALLEGRO_unMute = nullptr;
	ALLEGRO_titlettf = nullptr;
	ALLEGRO_optionsttf = nullptr;
	ALLEGRO_messagesttf = nullptr;
	ALLEGRO_field = nullptr;

	initImagesAndFonts();
	std::string aux;
	aux = engine.GetOpponentName();
	std::string aux1 = "Stratego                                                                                       Opponent: ";
	std::string auxFinal;
	auxFinal = aux1+ aux;
	al_set_window_title(ALLEGRO_display, auxFinal.c_str());
	update();
}

bool AllegroViewer::isViewerInitialized()
{
	return initialized;
}

void AllegroViewer::initImagesAndFonts()
{
	for (int i = 0; i < BlueFichaImagesDir.size(); i++)
	{
		Token tAux((notstd::rank)i, al_load_bitmap(BlueFichaImagesDir[i].c_str()));
		ALLEGRO_BlueFichaImages.push_back(tAux);
	}
	for (int i = 0; i < RedFichaImagesDir.size(); i++)
	{
		Token tAux((notstd::rank)i, al_load_bitmap(RedFichaImagesDir[i].c_str()));
		ALLEGRO_RedFichaImages.push_back(tAux);
	}
	int jmax;
	for (int i = 0; i < BlueCharactersDir.size(); i++)
	{
		Sprite sAux(i);
		jmax = getCantSprites(i);
		for (int j =0;j<jmax;j++)
		{
			sAux.pushImage(al_load_bitmap(BlueCharactersDir[i][j].c_str()));
		}
		ALLEGRO_BlueCharacters.push_back(sAux);
	}
	for (int i = 0; i < BlueCharactersDir.size(); i++)
	{
		Sprite sAux(i);
		jmax = getCantSprites(i);
		for (int j = 0; j<jmax; j++)
		{
			sAux.pushImage(al_load_bitmap(RedCharactersDir[i][j].c_str()));
		}
		ALLEGRO_RedCharacters.push_back(sAux);
	}
	for(int i=0;i<1;i++)
	{
		ALLEGRO_BITMAP * aux = al_load_bitmap(GameOverDir[i].c_str());
		ALLEGRO_GameOver.push_back(aux);
	}
	ALLEGRO_boton = al_load_bitmap(botonDir.c_str());
	ALLEGRO_battleBackground = al_load_bitmap(battleBackgroundDir.c_str());
	ALLEGRO_map = al_load_bitmap(mapDir.c_str());
	ALLEGRO_mute = al_load_bitmap(muteDir.c_str());
	ALLEGRO_unMute = al_load_bitmap(unMuteDir.c_str());
	ALLEGRO_field = al_load_bitmap(fieldDir.c_str());
	ALLEGRO_shuffle = al_load_bitmap(shuffleDir.c_str());
	ALLEGRO_titlettf = al_load_ttf_font(titlettfDir.c_str(), 100, 0);	//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_optionsttf = al_load_ttf_font(optionsttfDir.c_str(), 60, 0);//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_messagesttf = al_load_ttf_font(messagettfDir.c_str(), 50, 0);//cambiar el tamanio de la letra aca si es necesario
	wavAttack = al_load_sample(attackDir.c_str());
	wavDeath = al_load_sample(deathDir.c_str());
	wavIntro = al_load_sample(introDir.c_str());
	wavSoundtrack = al_load_sample(soundtrackDir.c_str());
}

void AllegroViewer::drawBattlefield()
{
	al_draw_scaled_bitmap(ALLEGRO_map, 0, 0, al_get_bitmap_width(ALLEGRO_map), al_get_bitmap_height(ALLEGRO_map),
		fichaWidth, fichaHeight, screenWidth - fichaWidth, screenHeight - fichaHeight,0);
	for (int i =0;i<10;i++)
	{
		for (int j =0;j<10;j++)
		{
			pos pAux(i, j);
			notstd::rank rAux = engine.getRankFromPos(pAux);
			if ((rAux != notstd::rank::WATER)&&(rAux != notstd::rank::LAND)&&(rAux != notstd::rank::OTHERS))
			{
				if (color == BLUE)
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
				else
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			else if (rAux == notstd::rank::OTHERS)
			{
				if (color == BLUE)
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
						(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
				else
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
						(j + 1)*(fichaWidth+5.5) + 19, (i + 1)*(fichaHeight-2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			if (engine.isSelectedFromPos(pAux))
			{
				highligthToken(pAux);
			}
		}
	}
}

void AllegroViewer::drawCemetery()
{
	for (int i =0;i<10;i++)
	{
		pos pAux(i, 0);
		notstd::rank rAux = (notstd::rank)i;
		if (color == BLUE)
		{
			al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
				5, (i + 1)*fichaHeight+2, fichaWidth - 5, fichaHeight - 5, 0);
		}
		else
		{
			al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
				5, (i + 1)*fichaHeight+2, fichaWidth - 5, fichaHeight - 5, 0);
		}
		al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), fichaWidth/2-10, fichaHeight*(i+ 1 + 1 / 2)-10, 0, "%d", engine.getNumberInCemetery(rAux));
		if (engine.isRankCemeterySelected(rAux))
		{
			highlightCemetery(rAux);
		}
	}
	if (color == BLUE)
	{
		al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[notstd::rank::BOMB].image, 0, 0,
			al_get_bitmap_width(ALLEGRO_BlueFichaImages[notstd::rank::BOMB].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[notstd::rank::BOMB].image),
			5, 2, fichaWidth - 5, fichaHeight - 5, 0);
		al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), (fichaWidth / 2) - 10, -12, 0, "%d", engine.getNumberInCemetery(notstd::rank::BOMB));
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[notstd::rank::BOMB].image, 0, 0,
			al_get_bitmap_width(ALLEGRO_RedFichaImages[notstd::rank::BOMB].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[notstd::rank::BOMB].image),
			5, 2, fichaWidth - 5, fichaHeight - 5, 0);
		al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), (fichaWidth / 2) - 10, -12, 0, "%d", engine.getNumberInCemetery(notstd::rank::BOMB));
	}
	if (engine.isRankCemeterySelected(notstd::rank::BOMB))
	{
		highlightCemetery(notstd::rank::BOMB);
	}
	if (engine.getState() == PLACING_FICHAS)
	{
		al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
			(screenWidth)-130, -17, 130, 90, 0);
		al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 110, -11, 0, "done");
		//dibujo la ficha especial (flag)
		if (color == BLUE)
		{
			al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[notstd::rank::FLAG].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_BlueFichaImages[notstd::rank::FLAG].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[notstd::rank::FLAG].image),
				5 + fichaWidth, 2, (fichaWidth)-5, fichaHeight - 5, 0);
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), (fichaWidth / 2) + fichaWidth - 10, -12, 0, "%d", engine.getNumberInCemetery(notstd::rank::FLAG));
		}
		else
		{
			al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[notstd::rank::FLAG].image, 0, 0,
				al_get_bitmap_width(ALLEGRO_RedFichaImages[notstd::rank::FLAG].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[notstd::rank::FLAG].image),
				5 + fichaWidth, 2, (fichaWidth)-5, fichaHeight - 5, 0);
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), (fichaWidth / 2) + fichaWidth - 10, -12, 0, "%d", engine.getNumberInCemetery(notstd::rank::FLAG));
		}
		if (engine.isRankCemeterySelected(notstd::rank::FLAG))
		{
			highlightCemetery(notstd::rank::FLAG);
		}
	}
}

void AllegroViewer::drawBackground()
{
	al_draw_scaled_bitmap(ALLEGRO_battleBackground, 0, 0, al_get_bitmap_width(ALLEGRO_battleBackground),
		al_get_bitmap_height(ALLEGRO_battleBackground), 0, 0, screenWidth, screenHeight, 0);
}

void AllegroViewer::highligthToken(pos init)
{
	drawHalo((init.y + 1)*(fichaWidth + 5.5) + 19, (init.x + 1)*(fichaHeight - 2.2) + 18, fichaWidth-10, fichaHeight-10);
}

void AllegroViewer::highlightCemetery(notstd::rank r)
{
	if ((r != notstd::rank::FLAG)&&(r != notstd::rank::BOMB))
	{
		drawHalo(5, (fichaHeight*(r+1)) + 5, fichaWidth-10, fichaHeight-10);
	}
	else if (r == notstd::rank::FLAG)
	{
		drawHalo(5 + fichaWidth, 5, fichaWidth - 10, fichaHeight - 10);
	}
	else if (r == notstd::rank::BOMB)
	{
		drawHalo(5, 5, fichaWidth - 10, fichaHeight - 10);
	}
}

void AllegroViewer::drawMessage()
{
	if ((engine.getState() == GAME_OVER)|| (engine.getState() == PLAY_AGAIN_SELECTED)|| (engine.getState() == GAME_OVER_SELECTED))
	{
		al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(255, 255, 255), screenWidth / 2, 5, 5, engine.getMessage().c_str());
	}
	else
	{
		al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, 5, 5, engine.getMessage().c_str());
	}
}

void AllegroViewer::drawGameOver(bool playerWon)
{
	al_draw_scaled_bitmap(ALLEGRO_GameOver[0], 0, 0, al_get_bitmap_width(ALLEGRO_GameOver[0]), al_get_bitmap_height(ALLEGRO_GameOver[0]), 0, 0, screenWidth, screenHeight, 0);
	if (playerWon)
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(255, 255, 255), screenWidth/3, screenHeight /6 , 0, "You Won!");
	}
	else
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(255, 255, 255), screenWidth / 3, screenHeight / 6, 0, "You Lost!");
	}
	for (int i = 1; i < 3; i++)
	{
		al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
			(screenWidth / 2) - 200, screenHeight / 3 + i*(al_get_bitmap_height(ALLEGRO_boton) + 2) +50
			, 400, 130, 0);
	}
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth / 2 - 45, (screenHeight / 3) + 190, 0, "Exit");
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth / 2 - 125, (screenHeight / 3) + 300, 0, "Play Again");
	al_flip_display();
}

void AllegroViewer::drawRemainingTime()
{
	int total = engine.getTime();
	int minutes = total / 60;
	int seconds = total % 60;
	if (seconds < 10)
	{
		if (minutes == 0)
		{
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(188,24, 24), screenWidth - 120, -10, 0, "%d:0%d", minutes, seconds);
		}
		else
		{
			al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 120, -10, 0, "%d:0%d", minutes, seconds);
		}
	}
	else
	{
		al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 120, -10, 0, "%d:%d", minutes, seconds);
	}
}

void AllegroViewer::drawSoundB()
{
	if (engine.isMuteOn())
	{
		al_draw_scaled_bitmap(ALLEGRO_mute, 0, 0, al_get_bitmap_width(ALLEGRO_mute), al_get_bitmap_height(ALLEGRO_mute)
			, screenWidth - 195, 3, 70, 60, 0);
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_unMute, 0, 0, al_get_bitmap_width(ALLEGRO_unMute), al_get_bitmap_height(ALLEGRO_unMute)
			, screenWidth - 195, 3, 70, 60, 0);
	}
}

void AllegroViewer::drawShuffle()
{
	al_draw_scaled_bitmap(ALLEGRO_shuffle, 0, 0, al_get_bitmap_width(ALLEGRO_shuffle), al_get_bitmap_height(ALLEGRO_shuffle)
		, screenWidth - 260, 3, 60, 60, 0);
}

void AllegroViewer::playBattleWarmUp(notstd::rank playerRank)
{
	fade_out(1, screenWidth, screenHeight);
	fade_in(ALLEGRO_field, 1, screenWidth, screenHeight);
	int x=0;
	int y=0;
	int aWidth=0;
	int aHeight=0;
	getDrawingCoord(x, y, aWidth, aHeight, playerRank, false);

	//dibujo el rank de mi carta
	drawRankInBattle(false, playerRank);

	switch (color)
	{
	case RED:
		ALLEGRO_RedCharacters[(int)playerRank].drawFirst(x, y, aWidth, aHeight, false);
		break;
	case BLUE:
		ALLEGRO_BlueCharacters[(int)playerRank].drawFirst(x, y, aWidth, aHeight, false);
		break;
	}
	al_flip_display();
	al_play_sample(wavIntro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_rest(0.25);
}

void AllegroViewer::moveToken(pos init, pos fin)
{
	drawBackground();
	al_draw_scaled_bitmap(ALLEGRO_map, 0, 0, al_get_bitmap_width(ALLEGRO_map), al_get_bitmap_height(ALLEGRO_map),
		fichaWidth, fichaHeight, screenWidth - fichaWidth, screenHeight - fichaHeight, 0);
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			if (DIF_A_POS_INICIAL && DIF_A_POS_FINAL)
			{
				pos pAux(i, j);
				notstd::rank rAux = engine.getRankFromPos(pAux);
				if ((rAux != notstd::rank::WATER) && (rAux != notstd::rank::LAND) && (rAux != notstd::rank::OTHERS))
				{
					if (color == BLUE)
					{
						al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
							(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
					}
					else
					{
						al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
							(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
					}
				}
				else if (rAux == notstd::rank::OTHERS)
				{
					if (color == BLUE)
					{
						al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_RedFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[rAux].image),
							(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
					}
					else
					{
						al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[rAux].image, 0, 0,
							al_get_bitmap_width(ALLEGRO_BlueFichaImages[rAux].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[rAux].image),
							(j + 1)*(fichaWidth + 5.5) + 19, (i + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
					}
				}
			}
		}
	}
	drawCemetery();
	drawRemainingTime();
	ALLEGRO_BITMAP *  dAux = al_get_target_bitmap();
	ALLEGRO_BITMAP *  aux = al_clone_bitmap(dAux);
	notstd::rank currR = engine.getRankFromPos(fin);
	if (init.y == fin.y) //se mueve verticalmente
	{
		int offset = (int)abs((init.x - fin.x));
		int totalOffset = offset*(fichaHeight-2.2);
		for (int i =0;i<=totalOffset;i++)
		{
			al_draw_bitmap(aux, 0, 0, 0);
			if (init.x > fin.x) //se mueve para arriba
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19, (init.x + 1)*(fichaHeight - 2.2) + 18 - i, fichaWidth - 10, fichaHeight - 10, 0);

				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19, (init.x + 1)*(fichaHeight - 2.2) + 18 -i, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			else //se mueve para abajo
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19, (init.x + 1)*(fichaHeight - 2.2) + 18 + i, fichaWidth - 10, fichaHeight - 10, 0);
				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19, (init.x + 1)*(fichaHeight - 2.2) + 18 + i, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			al_flip_display();
		}
	}
	else if (init.x == fin.x) //se mueve horizontalmente
	{
		int offset = (int)abs((init.y - fin.y));
		int totalOffset = offset*(fichaWidth+ 5.5);
		for (int i = 0; i<totalOffset; i++)
		{
			al_draw_bitmap(aux, 0, 0, 0);
			if (init.y > fin.y) //se mueve para la izquierda
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19-i, (init.x + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);

				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19-i, (init.x + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			else //se mueve para la derecha
			{
				if (((currR != OTHERS) && (color == BLUE)) || ((currR == OTHERS) && (color == RED)))
				{
					al_draw_scaled_bitmap(ALLEGRO_BlueFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_BlueFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_BlueFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19+i, (init.x + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
				else if (((currR != OTHERS) && (color == RED)) || ((currR == OTHERS) && (color == BLUE)))
				{
					al_draw_scaled_bitmap(ALLEGRO_RedFichaImages[currR].image, 0, 0,
						al_get_bitmap_width(ALLEGRO_RedFichaImages[currR].image), al_get_bitmap_height(ALLEGRO_RedFichaImages[currR].image),
						(init.y + 1)*(fichaWidth + 5.5) + 19+i, (init.x + 1)*(fichaHeight - 2.2) + 18, fichaWidth - 10, fichaHeight - 10, 0);
				}
			}
			al_flip_display();
		}
	}
	else
	{
		//movimiento invalido
	}
	al_destroy_bitmap(aux);

}

void AllegroViewer::playBattle(notstd::rank playerRank, notstd::rank opponentRank)
{
	whoWon status;
	switch (engine.getState()) //asume que sprites esta mirando a la izquierda
	{
	case MY_ATTACKING:
			if (opponentRank == FLAG)
			{
				status = PLAYER;
			}
			else if ((playerRank!= MINER)&&(opponentRank == BOMB))
			{
				status = OPPONENT;
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

	int pX =0;
	int pY =0;
	int pWidth=0;
	int pHeight=0;
	
	int oX = 0;
	int oY = 0;
	int oWidth = 0;
	int oHeight = 0;
	getDrawingCoord(pX, pY, pWidth, pHeight, playerRank, false);
	getDrawingCoord(oX, oY, oWidth, oHeight, opponentRank, true);
	al_play_sample(wavAttack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	switch (status)
	{
	case PLAYER:
		switch (color)
		{
		case RED:
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			drawRankInBattle(false, playerRank);
			drawRankInBattle(true, opponentRank);
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(oX,oY,oWidth,oHeight,true);
			ALLEGRO_RedCharacters[playerRank].playSequence(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_RedCharacters[playerRank].drawFirst(pX, pY, pWidth, pHeight, false);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_BlueCharacters[opponentRank].flicker(oX, oY, oWidth, oHeight, true);
			break;
		case BLUE:
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			drawRankInBattle(false, playerRank);
			drawRankInBattle(true, opponentRank);
			ALLEGRO_RedCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			ALLEGRO_BlueCharacters[playerRank].playSequence(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_BlueCharacters[playerRank].drawFirst(pX, pY, pWidth, pHeight, false);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_RedCharacters[opponentRank].flicker(oX, oY, oWidth, oHeight, true);
			break;
		}
		break;
	case OPPONENT:
		switch (color)
		{
		case RED:
			drawRankInBattle(true, opponentRank);
			ALLEGRO_BlueCharacters[opponentRank].playSequence(oX, oY, oWidth, oHeight, true);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_RedCharacters[playerRank].flicker(pX, pY, pWidth, pHeight, false);
			break;
		case BLUE:
			drawRankInBattle(true, opponentRank);
			ALLEGRO_RedCharacters[opponentRank].playSequence(oX, oY, oWidth, oHeight, true);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_RedCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_BlueCharacters[playerRank].flicker(pX, pY, pWidth, pHeight, false);
			break;
		}
		break;
	case TIE:
		switch (color)
		{
		case RED:
			drawRankInBattle(true, opponentRank);
			ALLEGRO_BlueCharacters[opponentRank].playSequence(oX, oY, oWidth, oHeight, true);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavAttack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_RedCharacters[playerRank].playSequence(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_BlueCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_RedCharacters[playerRank].flicker(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_BlueCharacters[opponentRank].flicker(oX, oY, oWidth, oHeight, true);
			break;
		case BLUE:
			drawRankInBattle(true, opponentRank);
			ALLEGRO_RedCharacters[opponentRank].playSequence(oX, oY, oWidth, oHeight, true);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_RedCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavAttack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_BlueCharacters[playerRank].playSequence(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			ALLEGRO_RedCharacters[opponentRank].drawFirst(oX, oY, oWidth, oHeight, true);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_BlueCharacters[playerRank].flicker(pX, pY, pWidth, pHeight, false);
			al_draw_scaled_bitmap(ALLEGRO_field, 0, 0, al_get_bitmap_width(ALLEGRO_field),
				al_get_bitmap_height(ALLEGRO_field), 0, 0, screenWidth, screenHeight, 0);
			al_play_sample(wavDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ALLEGRO_RedCharacters[opponentRank].flicker(oX, oY, oWidth, oHeight, true);
			break;
		}
		break;
	}
	al_rest(0.5);
	fade_out(1,screenWidth,screenHeight);
}

void AllegroViewer::drawHalo(double x, double y, double sizeX, double sizeY)
{
	for (int i = 1; i <= 5; i++)
	{
		al_draw_rectangle(x - i, y - i, x + sizeX + i, y + sizeY + i, al_map_rgb(0, 255 - i * 20, 0), 1.0);
	}
}

void AllegroViewer::drawRankInBattle(bool opponent, notstd::rank tokenRank)
{
	int x;
	if (opponent)
	{
		x = (3 * screenWidth) / 4;
	}
	else
	{
		x = screenWidth / 4;
	}
	if (tokenRank == notstd::rank::BOMB)
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(233, 233, 10), x, 50, 0, "B");
	}
	else if (tokenRank == notstd::rank::SPY)
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(233, 233, 10), x, 50, 0, "S");
	}
	else if (tokenRank == notstd::rank::FLAG)
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(233, 233, 10),  x, 50, 0, "F");
	}
	else
	{
		al_draw_textf(ALLEGRO_titlettf, al_map_rgb(233, 233, 10), x, 50, 0, "%d", (tokenRank + 1));
	}
}

void AllegroViewer::update()
{
	color = ((engine.getRed()) ? RED : BLUE); //Actualiza el color dependiendo quien empieza.
	currStatus myS = engine.GetmyPosStatus();
	currStatus opS = engine.GetopPosStatus();
	if (engine.isAttackResolved())
	{
		playBattle(engine.getMyRank(), engine.getOpponentRank());
	}
	else
	{
		switch (engine.getState())
		{
		case PLACING_FICHAS:
			manageSoundtrack();
			drawBackground();
			drawBattlefield();
			drawCemetery();
			drawMessage();
			drawSoundB();
			drawShuffle();
			al_flip_display();
			break;
		case MY_TURN:
			manageSoundtrack();
			drawBackground();
			drawBattlefield();
			drawCemetery();
			drawMessage();
			drawRemainingTime();
			drawSoundB();
			al_flip_display();
			break;
		case MY_ATTACKING:
				playBattleWarmUp(engine.getRankFromPos(myS.previous));
			break;
		case MY_MOVING:
			if (engine.getMoveDone() == false)
			{
				moveToken(myS.previous, myS.next);
			}
			break;
		case OP_TURN:
			manageSoundtrack();
			drawBackground();
			drawBattlefield();
			drawCemetery();
			drawMessage();
			drawRemainingTime();
			drawSoundB();
			al_flip_display();
			break;
		case OP_ATTACKING:
			playBattleWarmUp(engine.getRankFromPos(opS.next));
			break;
		case OP_MOVING:
			moveToken(opS.previous, opS.next);
			break;
		case GAME_OVER:
			if (engine.getState() != prevState)
			{
				fade_out(1, screenWidth, screenHeight);
				fade_in(ALLEGRO_GameOver[0], 1, screenWidth, screenHeight);
			}
			drawGameOver(engine.didPlayerWin());
			drawMessage();
			al_flip_display();
			break;
		case PLAY_AGAIN_SELECTED:
			drawGameOver(engine.didPlayerWin());
			drawMessage();
			al_flip_display();
			break;
		case GAME_OVER_SELECTED:
			drawGameOver(engine.didPlayerWin());
			drawMessage();
			al_flip_display();
			break;
		case ENDING_PLACING_FICHAS:
			manageSoundtrack();
			drawBackground();
			drawBattlefield();
			drawCemetery();
			drawMessage();
			drawRemainingTime();
			drawSoundB();
			al_flip_display();
			break;
		}
	}
	prevState = engine.getState();
	if (engine.GetExit() == true)
	{
		al_rest(3);
	}
}

int AllegroViewer::getCantSprites(int i)
{
	int aux;
	switch(i)
	{
	case 0:
		aux = 36;
		break;
	case 1:
		aux = 17;
		break;
	case 2:
		aux = 9;
		break;
	case 3:
		aux = 26;
		break;
	case 4:
		aux = 19;
		break;
	case 5:
		aux = 55;
		break;
	case 6:
		aux = 35;
		break; 
	case 7:
		aux = 61;
		break; 
	case 8:
		aux = 19;
		break;
	case 9:
		aux = 23;
		break;
	case 10:
		aux = 44;
		break;
	case 11:
		aux = 1;
		break;
	}
	return aux;
}

void AllegroViewer::getDrawingCoord(int& x, int& y, int& aWidth, int& aHeight, notstd::rank& r, bool opponent)
{
	if (opponent)
	{
		switch (r)
		{
		case notstd::rank::BOMB:
			x = 4.5*screenWidth / 7;
			y = (screenHeight * 5) / 8;
			aWidth = 150;
			aHeight = 200;
			break;
		case notstd::rank::CAPTAIN:
			x = 3*screenWidth / 8;
			y = (screenHeight * 4) / 8;
			aWidth = 500;
			aHeight = 300;
			break;
		case notstd::rank::CORONEL:
			x = 1.5*screenWidth / 5;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::FLAG:
			x = 4*screenWidth / 7;
			y = (screenHeight * 5) / 8;
			aWidth = 200;
			aHeight = 200;
			break;
		case notstd::rank::GENERAL:
			x = 1.5*screenWidth / 5;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::LIEUTENANT:
			x = 1.5*screenWidth / 5;
			y = (screenHeight * 3) / 8;
			aWidth = 500;
			aHeight = 400;
			break;
		case notstd::rank::MAJOR:
			x = 3*screenWidth / 9;
			y = (screenHeight * 4) / 9;
			aWidth = 500;
			aHeight = 350;
			break;
		case notstd::rank::MARSHAL:
			x = 5*screenWidth / 12;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::MINER:
			x = (screenWidth*5) / 12;
			y = (screenHeight * 3) / 8;
			aWidth = 500;
			aHeight = 400;
			break;
		case notstd::rank::SCOUT:
			x = 2.5*screenWidth / 7;
			y = (screenHeight * 5) / 8;
			aWidth = 450;
			aHeight = 200;
			break;
		case notstd::rank::SERGEANT:
			x = (screenWidth*3.2) / 9;
			y = (screenHeight * 2) / 8;
			aWidth = 650;
			aHeight = 600;
			break;
		case notstd::rank::SPY:
			x = screenWidth * 4.5 / 9;
			y = (screenHeight * 5) / 8;
			aWidth = 280;
			aHeight = 200;
			break;
		}
	}
	else
	{
		switch (r)
		{
		case notstd::rank::BOMB:
			x = screenWidth / 7;
			y = (screenHeight * 5) / 8;
			aWidth = 150;
			aHeight = 200;
			break;
		case notstd::rank::CAPTAIN:
			x = screenWidth / 8;
			y = (screenHeight * 4) / 8;
			aWidth = 500;
			aHeight = 300;
			break;
		case notstd::rank::CORONEL:
			x = screenWidth / 5;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::GENERAL:
			x = screenWidth / 5;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::LIEUTENANT:
			x = screenWidth / 5;
			y = (screenHeight * 3) / 8;
			aWidth = 500;
			aHeight = 400;
			break;
		case notstd::rank::MAJOR:
			x = screenWidth / 9;
			y = (screenHeight * 4) / 9;
			aWidth = 500;
			aHeight = 350;
			break;
		case notstd::rank::MARSHAL:
			x = screenWidth / 12;
			y = (screenHeight * 5) / 8;
			aWidth = 500;
			aHeight = 200;
			break;
		case notstd::rank::MINER:
			x = screenWidth / 12;
			y = (screenHeight * 3) / 8;
			aWidth = 500;
			aHeight = 400;
			break;
		case notstd::rank::SCOUT:
			x = screenWidth / 7;
			y = (screenHeight * 5) / 8;
			aWidth = 450;
			aHeight = 200;
			break;
		case notstd::rank::SERGEANT:
			x = screenWidth / 9;
			y = (screenHeight * 2) / 8;
			aWidth = 650;
			aHeight = 600;
			break;
		case notstd::rank::FLAG:
			x = screenWidth / 9;
			y = (screenHeight * 5) / 8;
			aWidth = 200;
			aHeight = 200;
			break;
		case notstd::rank::SPY:
			x = screenWidth / 5;
			y = (screenHeight * 5) / 8;
			aWidth = 280;
			aHeight = 200;
			break;
		}
	}
}

void AllegroViewer::manageSoundtrack()
{
	if (sound&&engine.isMuteOn())
	{
		//apagar la musica
		al_stop_samples();
		sound = false;
	}
	else if ((!sound) && !engine.isMuteOn())
	{
		//empiezo musica
		al_play_sample(wavSoundtrack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		sound = true;
	}
	else if ((!sound) && engine.isMuteOn())
	{
		//nada
	}
	else if (sound && !engine.isMuteOn())
	{
		//nada
	}
}

AllegroViewer::~AllegroViewer()
{
	for (int i=0;i< ALLEGRO_BlueFichaImages.size();i++)
	{
		ALLEGRO_BlueFichaImages[i].deleteBmps();
	}
	for (int i = 0; i< ALLEGRO_RedFichaImages.size(); i++)
	{
		ALLEGRO_RedFichaImages[i].deleteBmps();
	}
	for (int i = 0; i< ALLEGRO_BlueCharacters.size(); i++)
	{
		ALLEGRO_BlueCharacters[i].deleteBmps();
	}
	for (int i = 0; i< ALLEGRO_RedCharacters.size(); i++)
	{
		ALLEGRO_RedCharacters[i].deleteBmps();
	}
	if (ALLEGRO_field != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_field);
	}
	if (ALLEGRO_battleBackground != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_battleBackground);
	}
	if (ALLEGRO_map != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_map);
	}
	if (ALLEGRO_boton != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_boton);
	}
	if (ALLEGRO_mute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_mute);
	}
	if (ALLEGRO_unMute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_unMute);
	}
	if (ALLEGRO_titlettf != nullptr)
	{
		al_destroy_font(ALLEGRO_titlettf);
	}
	if (ALLEGRO_optionsttf != nullptr)
	{
		al_destroy_font(ALLEGRO_optionsttf);
	}
	if (ALLEGRO_messagesttf != nullptr)
	{
		al_destroy_font(ALLEGRO_messagesttf);
	}
	for (int i = 0; i < ALLEGRO_GameOver.size() ; i++)
	{
		if (ALLEGRO_GameOver[i] != nullptr)
		{
			al_destroy_bitmap(ALLEGRO_GameOver[i]);
		}
	}
	if (wavAttack != nullptr)
	{
		al_destroy_sample(wavAttack);
	}
	if (wavDeath != nullptr)
	{
		al_destroy_sample(wavDeath);
	}
	if (wavIntro != nullptr)
	{
		al_destroy_sample(wavIntro);
	}
	if (wavSoundtrack != nullptr)
	{
		al_destroy_sample(wavSoundtrack);
	}
}
