#pragma once

#include <vector>
#include "GenericObserver.h"
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



enum colour{BLUE,RED};

class AllegroViewer : public GenericObserver
{
public:
	AllegroViewer(GameModel &gm,colour c,ALLEGRO_DISPLAY * disp, int h = 720, int w = 1080);
	bool isViewerInitialized();
	void initImagesAndFonts();
	virtual void update();
	~AllegroViewer();
private:
	void drawBattlefield();
	void drawCemetery();
	void drawBackground();
	void drawMessage();
	void drawSoundB();
	void drawShuffle();
	void drawGameOver(bool playerWon);
	void drawRemainingTime();
	void drawHalo(double x, double y, double sizeX, double sizeY);
	void drawRankInBattle(bool opponent, notstd::rank tokenRank);
	void playBattleWarmUp(notstd::rank playerRank); //dibuja el rank propio hasta que llegue el del contrario
	void playBattle(notstd::rank playerRank, notstd::rank opponentRank); //animacion de la batalla
	void moveToken(pos init, pos fin);
	void highligthToken(pos init);
	void highlightCemetery(notstd::rank r);
	int  getCantSprites(int i);
	void getDrawingCoord(int& x, int& y, int& aWidth, int& aHeight, notstd::rank& r, bool opponent);
	void manageSoundtrack(); //actualiza el audio segun el estado del model y el viewer
	GameModel & engine;
	bool initialized;
	bool attackPending;
	bool sound;
	colour color;
	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int fichaHeight;
	unsigned int fichaWidth;
	int prevState;
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
	std::string shuffleDir;
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
	ALLEGRO_BITMAP * ALLEGRO_shuffle;
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