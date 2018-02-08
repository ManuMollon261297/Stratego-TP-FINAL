#include "MenuViewer.h"



MenuViewer::MenuViewer(int w, int h,MenuModel & p2e, ALLEGRO_DISPLAY * disp) : engine(p2e)
{
	//inicializacion de allegro
	ALLEGRO_display = disp;
	prevState = MENU;
	if (al_init_font_addon() && al_init_primitives_addon() && al_init_image_addon() && al_init_ttf_addon()
		&& al_install_audio() && al_init_acodec_addon())
	{
		initialized = true;
	}
	else
	{
		initialized = false;
	}
	al_reserve_samples(4);
	screenHeight = h;
	screenWidth = w;
	sound = false;
	//bmps
	botonLayoutDir = "../Allegro Data/button.png";
	menuBackgroundDir = "../Allegro Data/menuBackground.png";
	muteDir = "../Allegro Data/mute.png";
	unmuteDir = "../Allegro Data/unmute.png";
	nameInputDir = "../Allegro Data/nameInput.png";
	//fonts
	titlettfDir = "../Allegro Data/Prince Valiant.ttf";
	optionsttfDir = "../Allegro Data/Prince Valiant.ttf";
	messagettfDir = "../Allegro Data/Eutemia-I Italic.ttf";
	//sounds
	soundtrackDir = "../Allegro Data/AUDIO/soundtrack.wav";

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
	if (wavSoundtrack != nullptr)
	{
		al_destroy_sample(wavSoundtrack);
	}
}

void MenuViewer::initImagesAndFonts()
{
	ALLEGRO_menuBackground = al_load_bitmap(menuBackgroundDir.c_str());
	ALLEGRO_mute = al_load_bitmap(muteDir.c_str());
	ALLEGRO_unMute = al_load_bitmap(unmuteDir.c_str());
	ALLEGRO_nameInput = al_load_bitmap(nameInputDir.c_str());
	ALLEGRO_boton = al_load_bitmap(botonLayoutDir.c_str());

	ALLEGRO_titlettf = al_load_ttf_font(titlettfDir.c_str(), 160, 0);	//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_optionsttf = al_load_ttf_font(optionsttfDir.c_str(), 60, 0);//cambiar el tamanio de la letra aca si es necesario
	ALLEGRO_messagesttf = al_load_ttf_font(messagettfDir.c_str(), 50, 0);//cambiar el tamanio de la letra aca si es necesario

	wavSoundtrack = al_load_sample(soundtrackDir.c_str());
}

void MenuViewer::update()
{
	if (engine.getState() != prevState)
	{
		fade_out(1, screenWidth, screenHeight);
	}
	switch (engine.getState())
	{
	case MENU:
		manageSoundtrack();
		drawMenu();
		break;
	case WRITING_NAME:
		manageSoundtrack();
		drawWritingName();
		break;
	case RULES:
		manageSoundtrack();
		drawRules();
		break;
	case LEADERBOARD:
		manageSoundtrack();
		drawLeaderboard();
		break;
	}
	prevState = engine.getState();
}

void MenuViewer::drawMenu()
{
	al_draw_scaled_bitmap(ALLEGRO_menuBackground, 0, 0, al_get_bitmap_width(ALLEGRO_menuBackground), 
		al_get_bitmap_height(ALLEGRO_menuBackground), 0, 0, screenWidth, screenHeight, 0);
	for (int i = 0; i < 3; i++)
	{
		al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
			(screenWidth / 2) - 200, screenHeight / 3 + i*(al_get_bitmap_height(ALLEGRO_boton) + 2)
			, 400, 130, 0);
	}
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2-50, (screenHeight / 3)+30, 0, "Play");
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2-60, (screenHeight / 3)+140, 0, "Rules");
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth/2-125,(screenHeight / 3)+250, 0, "Leaderboard");
	if (engine.isMuteOn())
	{
		al_draw_scaled_bitmap(ALLEGRO_mute, 0, 0, al_get_bitmap_width(ALLEGRO_mute), al_get_bitmap_height(ALLEGRO_mute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_unMute, 0, 0, al_get_bitmap_width(ALLEGRO_unMute), al_get_bitmap_height(ALLEGRO_unMute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), (screenWidth/2)-225, screenHeight / 20
		, 0, "Stratego");
	al_flip_display();
}

void MenuViewer::drawLeaderboard()
{
	al_draw_scaled_bitmap(ALLEGRO_menuBackground, 0, 0, al_get_bitmap_width(ALLEGRO_menuBackground),
		al_get_bitmap_height(ALLEGRO_menuBackground), 0, 0, screenWidth, screenHeight, 0);
	al_draw_textf(ALLEGRO_titlettf, al_map_rgb(0, 0, 0), (screenWidth / 2) - 340, screenHeight / 20
		, 0, "Leaderboard");
	std::vector<std::string> info;
	info = engine.getLeadreboardInfo();
	for (int i = 0; i < info.size(); i++)
	{
		if (info[i][info[i].size() - 1] == '\r')
		{
			info[i].pop_back();
		}
	}
	for (int i=0; (i<5)&&(i<info.size());i++)
	{
		al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80 * (i+3), 0,
			info[i].c_str());
	}
	if (engine.isMuteOn())
	{
		al_draw_scaled_bitmap(ALLEGRO_mute, 0, 0, al_get_bitmap_width(ALLEGRO_mute), al_get_bitmap_height(ALLEGRO_mute)
			, screenWidth - 110, screenHeight - 100, 90, 80, 0);
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_unMute, 0, 0, al_get_bitmap_width(ALLEGRO_unMute), al_get_bitmap_height(ALLEGRO_unMute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
		screenWidth - 330, screenHeight - 128, 220, 120, 0);
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 270, screenHeight - 100, 0, "Back");
	al_flip_display();
}

void MenuViewer::drawRules()
{
	al_draw_scaled_bitmap(ALLEGRO_menuBackground, 0, 0, al_get_bitmap_width(ALLEGRO_menuBackground),
		al_get_bitmap_height(ALLEGRO_menuBackground), 0, 0, screenWidth, screenHeight, 0);
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80*0, 0,
		"The object of the game is to capture your opponent's flag. On your");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80*1, 0,
		"turn you can move your pieces or attack. Pieces move one square at a");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80*2, 0,
		"time, forward, backward or sideways. Except for Scouts (rank 1)");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80*3, 0,
		"that move multiple squares They cannot jump over another piece or to");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80*4, 0,
		"water areas Pieces cannot move back and forth the same squares in");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80 * 5, 0,
		"three consecutive turns. The Bomb and Flag pieces cannot be moved.");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80 * 6, 0,
		"When attacking, pieces with the lower higher number lose, except when the spy");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(0, 0, 0), screenWidth / 20, 30 + 80 * 7, 0,
		"attacks the marshall or miner attacks the bomb.");
	if (engine.isMuteOn())
	{
		al_draw_scaled_bitmap(ALLEGRO_mute, 0, 0, al_get_bitmap_width(ALLEGRO_mute), al_get_bitmap_height(ALLEGRO_mute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_unMute, 0, 0, al_get_bitmap_width(ALLEGRO_unMute), al_get_bitmap_height(ALLEGRO_unMute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
		screenWidth - 330, screenHeight - 128, 220, 120, 0);
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth -270, screenHeight-100, 0, "Back");
	al_flip_display();
}

void MenuViewer::drawWritingName()
{
	al_draw_scaled_bitmap(ALLEGRO_nameInput, 0, 0, al_get_bitmap_width(ALLEGRO_nameInput),
		al_get_bitmap_height(ALLEGRO_nameInput), 0, 0, screenWidth, screenHeight, 0);
	al_draw_textf(ALLEGRO_titlettf, al_map_rgb(255, 255, 255), 50, screenHeight / 4, 0, "%s",(engine.getName()).c_str());
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(255, 255, 255), screenWidth / 20, 30 + 80 * 0, 0,
		"Please write your name");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(255, 255, 255), screenWidth / 20, 30 + 80 * 1, 0,
		"You cant leave this blank empty");
	al_draw_textf(ALLEGRO_messagesttf, al_map_rgb(255, 255, 255), screenWidth / 20, 30 + 80 * 2, 0,
		"You can write up to 12 letters");
	if (engine.isMuteOn())
	{
		al_draw_scaled_bitmap(ALLEGRO_mute, 0, 0, al_get_bitmap_width(ALLEGRO_mute), al_get_bitmap_height(ALLEGRO_mute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	else
	{
		al_draw_scaled_bitmap(ALLEGRO_unMute, 0, 0, al_get_bitmap_width(ALLEGRO_unMute), al_get_bitmap_height(ALLEGRO_unMute)
			, screenWidth - 100, screenHeight - 100, 90, 80, 0);
	}
	al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
		screenWidth - 330, screenHeight - 128, 220, 120, 0);
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 270, screenHeight - 100, 0, "Back");
	al_draw_scaled_bitmap(ALLEGRO_boton, 0, 0, al_get_bitmap_width(ALLEGRO_boton), al_get_bitmap_height(ALLEGRO_boton),
		screenWidth - 350 -220, screenHeight - 128, 270, 120, 0);
	al_draw_textf(ALLEGRO_optionsttf, al_map_rgb(0, 0, 0), screenWidth - 525, screenHeight - 100, 0, "Confirm");
	al_flip_display();
}

void MenuViewer::manageSoundtrack()
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
