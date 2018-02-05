#include "mouseGameController.h"
#include "AllegroViewer.h"
#include "menuMouseController.h"
#include "MenuViewer.h"

using namespace std;

dataButtonsPos fillButtonsInfo(void);

void printStateModel(int state);

int main()
{
	dataButtonsPos dataButtons = fillButtonsInfo();
	MenuModel menu;
	menuMouseController menuControllerMouse(&menu, dataButtons);

	ALLEGRO_DISPLAY * display = nullptr;


	if (!al_init()) {
		return -1;
	}

	display = al_create_display(1080, 720);
	al_set_window_title(display, "Stratego                                                                                       Opponent: ???"); //moverlo a cuando sepamos ya quien es el oponente
	MenuViewer menuView(1080, 720, menu, display);

	menuView.initImagesAndFonts();
	menuView.isViewerInitialized();
	menuView.drawMenu();

	al_flip_display();

	ALLEGRO_EVENT_QUEUE* event_queue = nullptr;  ////////////event generator

	if (!al_install_mouse())
	{
		return false;
	}

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		return false;
	}
	al_register_event_source(event_queue, al_get_mouse_event_source());  //////////////

	
	ALLEGRO_EVENT ev;
	while (1)
	{
		if (al_get_next_event(event_queue, &ev))
		{
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				cout << "x: " << ev.mouse.x << endl;
				cout << "y: " << ev.mouse.y << endl;
				menuControllerMouse.dispatch(menuControllerMouse.shape(ev.mouse.x, ev.mouse.y));
				menuView.update();
				al_flip_display();
			}
			
		}
		
	}
	getchar();
	al_destroy_event_queue(event_queue);
	return 0;
}

void printStateModel(int state)
{
	cout << "estado del modelo:    ";
	switch (state)
	{
	case 0:
		cout << "MY_TURN" << endl;
		break;
	case 1:
		cout << "OP_TURN" << endl;
		break;
	case 2:
		cout << "MY_ATTACKING" << endl;
		break;
	case 3:
		cout << "OP_ATTACKING" << endl;
		break;
	case 4:
		cout << "MY_MOVING" << endl;
		break;
	case 5:
		cout << "OP_MOVING" << endl;
		break;
	case 6:
		cout << "PLACING_FICHAS" << endl;
		break;
	case 7:
		cout << "GAME_OVER" << endl;
		break;
	case 8:
		cout << "IDLE" << endl;
		break;
	case 9:
		cout << "ENDING_PLACING_FICHAS" << endl;
		break;
	case 10:
		cout << "WAITING_FOR_OPPONENTS_SELECTION" << endl;
		break;
	case 11:
		cout << "PLAY_AGAIN_SELECTED" << endl;
		break;
	case 12:
		cout << "GAME_OVER_SELECTED" << endl;
		break;
	default:
		cout << "estado desconocido" << endl;
	}
}

dataButtonsPos fillButtonsInfo(void)
{
	dataButtonsPos ret;
	ret.ll_play.x = 377;
	ret.ll_play.y = 358;
	ret.hr_play.x = 704;
	ret.hr_play.y = 268;

	ret.ll_help.x = 377;
	ret.ll_help.y = 464;
	ret.hr_help.x = 704;
	ret.hr_help.y = 377;

	ret.ll_goback.x = 771;
	ret.ll_goback.y = 703;
	ret.hr_goback.x = 951;
	ret.hr_goback.y = 619;
	return ret;
}