#pragma once

//VER CUANDO SE RESUELVE EL ATAQUE
//-------------------------------------------
//CAMBIAR LO DEL DISPLAY CUANDO JUNTEMOS TODO
//IMAGEN DE LA FLAG Y VER COMO MOSTRAR CUANDO LA ATACAN/ES ATACADA

#include <vector>
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Sprite.h"
#include "Token.h"
#include "AllegroFuncs.h"
#include "GameModel.h"
#include "ranks.h"
#include "pos.h"

enum colour{RED,BLUE};

class AllegroViewer
{
public:
	AllegroViewer(int h ,int w,GameModel &gm,colour c);
	bool isViewerInitialized();
	void initImagesAndFonts();
	void update();
	//para debugeo
	void drawBattlefield();
	void drawCemetery();
	void drawBackground();
	void drawMessage();
	void drawSoundB();
	void drawGameOver(bool playerWon);
	void drawRemainingTime();
	void drawHalo(double x, double y, double sizeX, double sizeY);
	void playBattleWarmUp(rank playerRank);
	void playBattle(rank playerRank, rank opponentRank);
	void moveToken(pos init, pos fin);
	void highligthToken(pos init);
	void highlightCemetery(rank r);
	int  getCantSprites(int i);
	void getDrawingCoord(int& x, int& y, int& aWidth, int& aHeight, rank& r, bool opponent);
	void manageSoundtrack();
	//
	~AllegroViewer();
private:
	GameModel & engine;
	bool initialized;
	bool attackPending;
	bool sound;
	colour color;
	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int fichaHeight;
	unsigned int fichaWidth;
	//direcciones de imagenes
	std::vector<std::string> BlueFichaImagesDir;//cada dir es una imagen de las fichas azules
	std::vector<std::string> RedFichaImagesDir;	//cada dir es una imagen de las fichas rojas
	std::vector<std::vector<std::string>> BlueCharactersDir; //cada dir es una carpeta con la animacion correspondiente a cada personaje azul
	std::vector<std::vector<std::string>> RedCharactersDir;	//cada dir es una carpeta con la animacion correspondiente a cada personaje rojo
	std::vector<std::string> GameOverDir;		//cada dir es una imagen de la secuencia de game over
	std::string botonDir;						//dir de una imagen de un boton
	std::string battleBackgroundDir;			//dir de fondo de pantalla durante la partida
	std::string mapDir;							//dir de imagen del mapa de juego  
	std::string muteDir;
	std::string unMuteDir;
	std::string fieldDir;
	std::string attackDir;
	std::string deathDir;
	std::string introDir;
	std::string soundtrackDir;
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
	ALLEGRO_BITMAP * ALLEGRO_boton;				//imagenes boton
	ALLEGRO_BITMAP * ALLEGRO_battleBackground;	//fondo de pantalla durante la partida
	ALLEGRO_BITMAP * ALLEGRO_map;				//imagen del mapa de juego  
	ALLEGRO_BITMAP * ALLEGRO_mute;
	ALLEGRO_BITMAP * ALLEGRO_unMute;
	ALLEGRO_BITMAP * ALLEGRO_field;
	//allegro font
	ALLEGRO_FONT * ALLEGRO_titlettf;
	ALLEGRO_FONT * ALLEGRO_optionsttf;
	ALLEGRO_FONT * ALLEGRO_messagesttf;
	//allegro samples (sounds)
	ALLEGRO_SAMPLE * wavAttack;
	ALLEGRO_SAMPLE * wavDeath;
	ALLEGRO_SAMPLE * wavIntro;
	ALLEGRO_SAMPLE * wavSoundtrack;
	//display
	ALLEGRO_DISPLAY * ALLEGRO_display;
};