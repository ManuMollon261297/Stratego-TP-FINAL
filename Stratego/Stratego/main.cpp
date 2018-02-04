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

	display = al_create_display(720, 1080);

	MenuViewer menuView(720, 1080, menu, display);

	menuView.initImagesAndFonts();
	menuView.isViewerInitialized();
	menuView.drawMenu();

	

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

	al_flip_display();
	ALLEGRO_EVENT ev;
	while (1)
	{
		if (al_get_next_event(event_queue, &ev))
		{
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
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
	return ret;
}