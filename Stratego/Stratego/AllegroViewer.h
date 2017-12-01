#pragma once

#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "Sprite.h"
#include "Token.h"
#include <vector>
#include "GameModel.h"
#include "ranks.h"
#include "pos.h"

class AllegroViewer
{
public:
	AllegroViewer(int h ,int w,GameModel &gm);
	bool isViewerInitialized();
	void initImagesAndFonts();
	void update(); //HACER
	void drawBattlefield(); //HACER
	void drawCemetery(); //HACER
	void playBattleWarmUp(); //HACER
	void playBattle(rank playerRank, rank opponentRank); //HACER
	void moveToken(pos init, pos fin); //HACER
	void highligthToken(pos init); //HACER
	void highlightCemetery(rank r); //HACER
	void drawMessage(); //HACER
	void drawGameOver(bool playerWon); //HACER
	void drawRemainingTime(); //HACER
	~AllegroViewer();
private:
	GameModel & engine;
	bool initialized;
	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int fichaHeight;
	unsigned int fichaWidth;
	//direcciones de imagenes
	std::vector<std::string> BlueFichaImagesDir;//cada dir es una imagen de las fichas azules
	std::vector<std::string> RedFichaImagesDir;	//cada dir es una imagen de las fichas rojas
	std::vector<std::string> BlueCharactersDir; //cada dir es una carpeta con la animacion correspondiente a cada personaje azul
	std::vector<std::string> RedCharactersDir;	//cada dir es una carpeta con la animacion correspondiente a cada personaje rojo
	std::vector<std::string> GameOverDir;		//cada dir es una imagen de la secuencia de game over
	std::string botonDir;						//dir de una imagen de un boton
	std::string battleBackgroundDir;			//dir de fondo de pantalla durante la partida
	std::string mapDir;							//dir de imagen del mapa de juego  
	std::string menuBackgroundDir;				//dir de fondo de pantalla durante el menu
	std::string muteDir;
	std::string unMuteDir;
	std::string nameInputDir;
	//direccion del font
	std::string titlettfDir;
	std::string optionsttfDir;
	std::string messagettfDir;
	//allegro bitmaps
	std::vector<Token> ALLEGRO_BlueFichaImages;	//bitmap de las fichas azules
	std::vector<Token> ALLEGRO_RedFichaImages;  //bitmap de las fichas rojas
	std::vector<Sprite> ALLEGRO_BlueCharacters;	//sprite correspondiente a cada personaje azul
	std::vector<Sprite> ALLEGRO_RedCharacters;	//sprite correspondiente a cada personaje rojo
	std::vector<ALLEGRO_BITMAP *> ALLEGRO_GameOver;		//cada dir es una imagen de la secuencia de game over
	ALLEGRO_BITMAP * ALLEGRO_boton;	//imagenes boton
	ALLEGRO_BITMAP * ALLEGRO_battleBackground;	//fondo de pantalla durante la partida
	ALLEGRO_BITMAP * ALLEGRO_map;				//imagen del mapa de juego  
	ALLEGRO_BITMAP * ALLEGRO_menuBackground;	//fondo de pantalla durante el menu 
	ALLEGRO_BITMAP * ALLEGRO_mute;
	ALLEGRO_BITMAP * ALLEGRO_unMute;
	ALLEGRO_BITMAP * ALLEGRO_nameInput;
	//allegro font
	ALLEGRO_FONT * ALLEGRO_titlettf;
	ALLEGRO_FONT * ALLEGRO_optionsttf;
	ALLEGRO_FONT * ALLEGRO_messagesttf;
	//display
	ALLEGRO_DISPLAY * ALLEGRO_display;
};

