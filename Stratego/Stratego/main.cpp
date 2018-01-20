#include "mouseGameController.h"
#include "AllegroViewer.h"

enum states { //SOLO PARA DEBUGGING
	MY_TURN, OP_TURN, MY_ATTACKING, OP_ATTACKING, MY_MOVING, OP_MOVING, PLACING_FICHAS, GAME_OVER, IDLE
	, ENDING_PLACING_FICHAS, WAITING_FOR_OPPONENTS_SELECTION, PLAY_AGAIN_SELECTED, GAME_OVER_SELECTED
};
//#include <allegro5\allegro.h>

using namespace std;

void printStateModel(int state);

int main()
{
	pos inicial(6, 5);
	pos final(6, 0);
	GameModel engine;
	engine.setRed(true);
	AllegroViewer viewer(720, 1080, engine, RED);
	viewer.initImagesAndFonts();
	mouseGameController mouseControl(720, 1080, &engine);

	pos bPlaceReadyLL(0, 65);
	pos bPlaceReadyHR(65, 0);
	button placeReady_B(PLACE_READY_B, bPlaceReadyLL, bPlaceReadyHR);
	engine.pushButton(placeReady_B);

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





	for (int i = 6; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			pos curr(i, j);
			engine.setFicha(SCOUT, curr);
		}
	}
	//engine.setState(MY_TURN); //DEBUG
	viewer.drawBackground();
	viewer.drawBattlefield();
	viewer.drawCemetery();
	al_flip_display();
	ALLEGRO_EVENT ev;
	while (1)
	{
		if (al_get_next_event(event_queue, &ev))
		{
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				mouseControl.dispatch(mouseControl.shape(ev.mouse.x, ev.mouse.y));
				viewer.drawBackground();
				viewer.drawBattlefield();
				viewer.drawCemetery();
				al_flip_display();
				engine.printBattlefield();
				printStateModel(engine.getState());  //deberia imprimir PLACING_FICHAS
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