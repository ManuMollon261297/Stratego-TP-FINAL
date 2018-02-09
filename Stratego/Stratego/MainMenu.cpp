#include "MainMenu.h"

MainMenu::MainMenu(ALLEGRO_DISPLAY* disp, ALLEGRO_EVENT_QUEUE* ev_q)
{
	dataButtons = fillButtonsInfo();
	menu = new MenuModel;
	menuControllerMouse = new menuMouseController(menu, dataButtons);
	KeyController = new KeyboardController(menu);
	menu_viewer = new MenuViewer(1080, 720, *menu, disp); //crea el viewer del menu
	menu_viewer->initImagesAndFonts();
	menu_viewer->isViewerInitialized();
	menu_viewer->drawMenu();
	menu_viewer->manageSoundtrack();
	queue = ev_q;
	al_flip_display();
}

MainMenu::~MainMenu()
{
	delete menu;
	delete menuControllerMouse;
	delete KeyController;
	delete menu_viewer;
}


void MainMenu::Run(void)
{
	ALLEGRO_EVENT ev;
	do
	{
		if (al_get_next_event(queue, &ev))
		{
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				std::cout << "x: " << ev.mouse.x << std::endl;
				std::cout << "y: " << ev.mouse.y << std::endl;
				menuControllerMouse->dispatch(menuControllerMouse->shape(ev.mouse.x, ev.mouse.y));
				menu_viewer->update();
				
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				KeyController->dispatch(KeyboardEvent(ev.keyboard));
				menu_viewer->update();
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				menu->setExit();
			}

		}

	} while (!(menu->GetExit()));
	
}

dataButtonsPos MainMenu::fillButtonsInfo(void)
{
	dataButtonsPos ret;

	ret.ll_play.x = 378;
	ret.ll_play.y = 358;
	ret.hr_play.x = 707;
	ret.hr_play.y = 268;

	ret.ll_leaderboard.x = 378;
	ret.ll_leaderboard.y = 576;
	ret.hr_leaderboard.x = 707;
	ret.hr_leaderboard.y = 488;

	ret.ll_help.x = 378;
	ret.ll_help.y = 464;
	ret.hr_help.x = 707;
	ret.hr_help.y = 377;

	ret.ll_goback.x = 771;
	ret.ll_goback.y = 703;
	ret.hr_goback.x = 951;
	ret.hr_goback.y = 619;

	ret.ll_sound.x = 984;
	ret.ll_sound.y = 694;
	ret.hr_sound.x = 1058;
	ret.hr_sound.y = 622;

	ret.ll_confirm.x = 538;
	ret.ll_confirm.y = 700;
	ret.hr_confirm.x = 757;
	ret.hr_confirm.y = 620;

	return ret;
}