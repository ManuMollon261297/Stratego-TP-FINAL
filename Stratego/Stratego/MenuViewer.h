#pragma once

#include "MenuModel.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "AllegroFuncs.h"
#include <vector>

class MenuViewer
{
public:
	MenuViewer(int w, int h, MenuModel & p2e, ALLEGRO_DISPLAY * disp);
	bool isViewerInitialized();
	void initImagesAndFonts();
	void update();
	~MenuViewer();
	//SOLO EN PUBLIC PARA DEBUGEAR
	void drawMenu();
	void drawLeaderboard();
	void drawRules();
	void drawWritingName();
	void manageSoundtrack();
private:
	int screenWidth;
	int screenHeight;
	int prevState;
	MenuModel & engine;
	//direcciones de bmps
	std::string menuBackgroundDir;
	std::string botonLayoutDir;
	std::string muteDir;
	std::string unmuteDir;
	std::string nameInputDir;
	//direcciones de fonts
	std::string titlettfDir;
	std::string optionsttfDir;
	std::string messagettfDir;
	//direccion de sonidos
	std::string soundtrackDir;
	//bools
	bool sound;
	bool initialized;
	// allegro bmps
	ALLEGRO_BITMAP * ALLEGRO_menuBackground;	//fondo de pantalla durante el menu 
	ALLEGRO_BITMAP * ALLEGRO_boton;				//imagen boton
	ALLEGRO_BITMAP * ALLEGRO_mute;
	ALLEGRO_BITMAP * ALLEGRO_unMute;
	ALLEGRO_BITMAP * ALLEGRO_nameInput;
	//allegro font
	ALLEGRO_FONT * ALLEGRO_titlettf;
	ALLEGRO_FONT * ALLEGRO_optionsttf;
	ALLEGRO_FONT * ALLEGRO_messagesttf;
	//allegro samples (sounds)
	ALLEGRO_SAMPLE * wavSoundtrack;
	//display
	ALLEGRO_DISPLAY * ALLEGRO_display;

};

