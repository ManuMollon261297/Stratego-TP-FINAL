#include "MainMenu.h"
#include "NetworkingModel.h"
#include "NetWorkingController.h"
#include "GameModel.h"
#include "EventGenerator.h"
#include "Event.h"
#include "GenericController.h"
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;



typedef struct
{
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
	ALLEGRO_TIMER* timer = nullptr;
}resources;

bool Init(resources* r); //Inicializa todos los recursos necesarios.
void DoExit(resources* r); //Se ocupa de todos los recursos a la salida del programa.
void InitializeControllers(vector<GenericController*>&, GameModel* p_gm, NetworkingModel* p_nwm,NetWorkingController* NetCont);
void DestroyControllers(vector<GenericController*>&);

int main()
{

	resources res;
	bool success = true;
	success = Init(&res);
	if (!success)
	{
		return -1;
	}
	GameModel Gm;
	NetworkingModel Nwm;
	NetWorkingController* NetContr = new NetWorkingController(&Gm, &Nwm);
	EventGenerator EvGen(&Gm, &Nwm, res.event_queue);
	MainMenu* p_menu = new MainMenu(res.display, res.event_queue, NetContr, &EvGen); //Se inicializa, corre y destruye el menu del juego.
	if (!p_menu->Run())
	{
		delete p_menu;
		delete NetContr;
		p_menu = nullptr;
		NetContr = nullptr;
		DoExit(&res);
		return 0;
	}
	delete p_menu;
	p_menu = nullptr;

	colour c = ( (Gm.getRed()) ? RED : BLUE);
	Gm.AttachObserver(new AllegroViewer(Gm, c, res.display));
	vector<GenericController*> v_contr;
	InitializeControllers(v_contr, &Gm, &Nwm, NetContr);

	while ( !(Gm.GetExit()))
	{
		GenericEvent* ev;
		EvGen.searchForEvents();
		if ( EvGen.hayEvento())
		{
			ev = EvGen.getNextEvent();
			if ((ev->GetEvent()) == (MOUSE))
			{
				cout << "Mouse event:" << endl;
			}
			for (int i = 0; i < v_contr.size(); i++)
			{
				(v_contr[i])->dispatch(*ev); 
			}
			delete ev;
		}

	}
	DestroyControllers(v_contr);

	DoExit(&res);
	return 0;

}



bool Init(resources* r)
{
	if (!al_init()) {
		return false;
	}
	
	if (!al_install_mouse())
	{
		return false;
	}
	r->timer = al_create_timer(1); //crea un timer de un segundo.
	if ((r->timer) == nullptr)
	{
		return false;
	}


	if (!al_install_keyboard())
	{
		al_destroy_timer(r->timer);
		return false;
	}

	r->event_queue = al_create_event_queue();
	if (!(r->event_queue))
	{
		al_destroy_timer(r->timer);
		return false;
	}

	r->display = al_create_display(1080, 720);
	if (r->display == nullptr)
	{
		al_destroy_timer(r->timer);
		r->event_queue = al_create_event_queue();

	}
	al_set_window_title(r->display, "Stratego                                                                                       Opponent: ???"); //moverlo a cuando sepamos ya quien es el oponente


	//Registro todas las fentes de eventos relevantes, Timer, display, keyboard y mouse.
	al_register_event_source(r->event_queue, al_get_mouse_event_source()); 
	al_register_event_source(r->event_queue, al_get_display_event_source(r->display));
	al_register_event_source(r->event_queue, al_get_keyboard_event_source());
	al_register_event_source(r->event_queue, al_get_timer_event_source(r->timer));
	al_start_timer(r->timer); //Activo el timer que llama cada un segundo.
	return true;

}

void DoExit(resources* r)
{
	al_destroy_display(r->display);
	al_destroy_event_queue(r->event_queue);
	al_destroy_timer(r->timer);
}

void InitializeControllers(vector<GenericController*>& v, GameModel* p_gm, NetworkingModel* p_nwm, NetWorkingController* NetCont)
{
	v.push_back(NetCont);
	v.push_back(new mouseGameController(720, 1080, p_gm));
}

void DestroyControllers(vector<GenericController*>& v)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		delete (v[i]);
	}
	v.clear(); //Destruye los controllers.
}

