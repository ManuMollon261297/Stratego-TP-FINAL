#include "MenuViewer.h"



MenuViewer::MenuViewer(int w, int h,MenuModel & p2e) : engine(p2e)
{
	//inicializacion de allegro
	if (al_init() && al_init_font_addon() && al_init_primitives_addon() && al_init_image_addon() && al_init_ttf_addon()) //SACAR AL_INIT DESPUES DE DEBUGGEAR
	{
		ALLEGRO_display = al_create_display(w, h);
		initialized = true;
	}
	else
	{
		initialized = false;
	}
	screenHeight = h;
	screenWidth = w;
	muteOn = false;
	//bmps
	botonLayoutDir = "../Allegro Data/button.png";
	menuBackgroundDir = "../Allegro Data/menuBackground.png";
	muteDir = "../Allegro Data/mute.png";
	unmuteDir = "../Allegro Data/unmute.png";
	//fonts
	titlettfDir = "../Allegro Data/Prince Valiant.ttf";
	optionsttfDir = "../Allegro Data/Prince Valiant.ttf";
	messagettfDir = "../Allegro Data/Eutemia-I Italic.ttf";

	ALLEGRO_menuBackground = nullptr;
	ALLEGRO_mute = nullptr;
	ALLEGRO_unMute = nullptr;
	ALLEGRO_nameInput = nullptr;
	ALLEGRO_boton = nullptr;

	ALLEGRO_titlettf = nullptr;
	ALLEGRO_optionsttf = nullptr;
	ALLEGRO_messagesttf = nullptr;
}

bool MenuViewer::isViewerInitialized()
{
	return initialized;
}


MenuViewer::~MenuViewer()
{
	if (ALLEGRO_menuBackground != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_menuBackground);
	}
	if (ALLEGRO_mute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_mute);
	}
	if (ALLEGRO_unMute != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_unMute);
	}
	if (ALLEGRO_nameInput != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_nameInput);
	}
	if (ALLEGRO_boton != nullptr)
	{
		al_destroy_bitmap(ALLEGRO_boton);
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
}

void MenuViewer::initImagesAndFonts()
{
	ALLEGRO_menuBackground = al_load_bitmap(menuBackgroundDir.c_str());
	ALLEGRO_mute = al_load_bitmap(muteDir.c_str());
	ALLEGRO_unMute = al_load_bitmap(unmuteDir.c_str());
	ALLEGRO_nameInput = al_load_bitmap(nameInputDir.c_str());
	ALLEGRO_boton = al_load_bitmap(botonLayoutDir.c_str());

	ALLEGRO_titlettf = al_load_ttf_font(titlettfDir.c_str(), 100, 0);	//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_optionsttf = al_load_ttf_font(optionsttfDir.c_str(), 60, 0);//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_messagesttf = al_load_ttf_font(messagettfDir.c_str(), 50, 0);//cambiar el tamanio de la letra aca si es necesario
}

void MenuViewer::update()
{
	switch (engine.getState())
	{
	case MENU:
		break;
	case WRITING_NAME:
		break;
	case RULES:
		break;
	case MUTE_TOGGLE:
		break;
	case LEADERBOARD:
		break;
	}
}

void MenuViewer::drawMenu()
{
	al_draw_scaled_bitmap(ALLEGRO_menuBackground, 0, 0, al_get_bitmap_width(ALLEGRO_menuBackground), 
		al_get_bitmap_height(ALLEGRO_menuBackground), 0, 0, screenWidth, screenHeight, 0);
	for (int i = 0; i < 3; i++)
	{
		al_draw_bitmap(ALLEGRO_boton, (screenWidth / 2) - (al_get_bitmap_width(ALLEGRO_boton) / 2), 
			screenHeight / 3 + i*(al_get_bitmap_height(ALLEGRO_boton) +2), 0);
	}
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2, screenHeight / 3, 0, "Play");
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2, 
		screenHeight / 3 + (al_get_bitmap_height(ALLEGRO_boton) + 2), 0, "Rules");
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2,
		screenHeight / 3 + 2*(al_get_bitmap_height(ALLEGRO_boton) + 2), 0, "Leaderboard");
	if (muteOn)
	{
		al_draw_bitmap(ALLEGRO_mute, screenWidth - al_get_bitmap_width(ALLEGRO_mute), 
			screenHeight - al_get_bitmap_height(ALLEGRO_mute), 0);
	}
	else
	{
		al_draw_bitmap(ALLEGRO_unMute, screenWidth - al_get_bitmap_width(ALLEGRO_unMute),
			screenHeight - al_get_bitmap_height(ALLEGRO_unMute), 0);
	}
	al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), screenWidth/2, screenHeight / 4, 0, "STRATEGO");
	al_flip_display();
}

void MenuViewer::drawLeaderboard() //sacarlos del archivo
{
}

void MenuViewer::drawRules()//escribir las reglas principales
{
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight + 00, 0, "dsjdksjdkddsjd", name.c_str());
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight + 20, 0, "  mdsnmdnsmdns", name.c_str());
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight + 40, 0, "ms,m,dms,mds,d", name.c_str());
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight + 60, 0, "ksldkldksdssls", name.c_str());
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight + 80, 0, "dklsdklsdsslss", name.c_str());
}

void MenuViewer::drawWritingName()
{
	al_draw_scaled_bitmap(ALLEGRO_nameInput, 0, 0, al_get_bitmap_width(ALLEGRO_nameInput),
		al_get_bitmap_height(ALLEGRO_nameInput), 0, 0, screenWidth, screenHeight, 0);
	al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), screenWidth / 2, screenHeight / 4, 0, "%s",name.c_str());
	al_flip_display();
}
