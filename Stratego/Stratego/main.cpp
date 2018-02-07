#include "MainMenu.h"
#include "NetworkingModel.h"
#include <fstream>
#include <time.h>

using namespace std;


void printStateModel(int state);
#define MAX_IP_LENGTH 45

typedef struct
{
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
}resources;

bool Init(resources* r); //Inicializa todos los recursos necesarios.
void DoExit(resources* r); //Se ocupa ded todos los recurso a la salida del programa.

int main()
{

	resources res;
	bool success = true;
	success = Init(&res);
	if (!success)
	{
		return -1;
	}

	MainMenu* p_menu = new MainMenu(res.display, res.event_queue); //Se inicializa, corre y destruye el menu del juego.
	p_menu->Run();
	delete p_menu;

	DoExit(&res);


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

bool Init(resources* r)
{
	if (!al_init()) {
		return false;
	}
	r->display = al_create_display(1080, 720);
	al_set_window_title(r->display, "Stratego                                                                                       Opponent: ???"); //moverlo a cuando sepamos ya quien es el oponente

	if (!al_install_mouse())
	{
		return false;
	}

	r->event_queue = al_create_event_queue();
	if (!(r->event_queue))
	{
		return false;
	}
	al_register_event_source(r->event_queue, al_get_mouse_event_source());
	al_register_event_source(r->event_queue, al_get_display_event_source(r->display));
	return true;

}

void DoExit(resources* r)
{
	al_destroy_display(r->display);
	al_destroy_event_queue(r->event_queue);
}