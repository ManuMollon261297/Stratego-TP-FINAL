#include "MainMenu.h"

MainMenu::MainMenu(ALLEGRO_DISPLAY* disp, ALLEGRO_EVENT_QUEUE* ev_q, NetWorkingController* nw, EventGenerator* ev_g)
{
	p_nw = nw;
	p_Ev_gen = ev_g;
	dataButtons = fillButtonsInfo();
	menu = new MenuModel;
	p_nw->AddMainMenu(menu);
	v_contr.push_back(new menuMouseController(menu, dataButtons));
	v_contr.push_back(new KeyboardController(menu, 21, 8));
	MenuViewer* menu_viewer = new MenuViewer(1080, 720, *menu, disp); //crea el viewer del menu
	menu_viewer->initImagesAndFonts();
	menu_viewer->isViewerInitialized();
	menu_viewer->drawMenu();
	menu_viewer->manageSoundtrack();
	menu->AttachObserver(menu_viewer);
	queue = ev_q;
	al_flip_display();
}

MainMenu::~MainMenu()
{
	delete menu;
	for (unsigned int i =0 ; i< v_contr.size(); i++)
	{
		delete v_contr[i];
	}
	v_contr.clear();
}


bool MainMenu::Run(void)
{
	while (!(menu->GetExit()))
	{
		p_Ev_gen->searchForEvents();
		if ( p_Ev_gen->hayEvento())
		{
			GenericEvent * G_ev = p_Ev_gen->getNextEvent();
			for (unsigned int i = 0; i<v_contr.size(); i++)
			{
				(v_contr[i])->dispatch(*G_ev);
			}
			if ( menu->getState() == CONNECTING)
			{
				p_nw->dispatch(*G_ev);
			}
			delete G_ev;
		}

	}
	if (p_nw->GetServer() == UNINITIALIZED)
	{
		return false;
	}
	else
	{
		return true;
	}
	
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