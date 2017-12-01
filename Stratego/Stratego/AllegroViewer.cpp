#include "AllegroViewer.h"



AllegroViewer::AllegroViewer(int h, int w, GameModel &gm) //CAMBIAR VALORES DE LOS FORS CUANDO YA ESTEN LA IMAGENES
{
	engine = gm;
	//inicializacion de allegro
	if (al_init()&& al_init_font_addon())
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
	ALLEGRO_titlettf = al_load_font(titlettfDir.c_str(), 20, 0);	//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_optionsttf = al_load_font(optionsttfDir.c_str(), 15, 0);//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_messagesttf = al_load_font(messagettfDir.c_str(), 5, 0);//cambiar el tamanio de la letra aca si es necesario
}

void AllegroViewer::drawBattlefield()
{
}

void AllegroViewer::drawCemetery()
{
}

void AllegroViewer::playBattleWarmUp()
{
}

void AllegroViewer::playBattle(rank playerRank, rank opponentRank)
{
}

void AllegroViewer::moveToken(pos init, pos fin)
{
}

void AllegroViewer::update()
{
}

void AllegroViewer::highligthToken(pos init)
{
}

void AllegroViewer::highlightCemetery(rank r)
{
}

void AllegroViewer::drawMessage()
{
}

void AllegroViewer::drawGameOver(bool playerWon)
{
}

void AllegroViewer::drawRemainingTime()
{
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
