#include "MainMenu.h"
#include "NetworkingModel.h"
#include <fstream>
#include <time.h>

using namespace std;


void printStateModel(int state);
#define MAX_IP_LENGTH 45
//#define NETWORKING_TEST
//#define MENU_TEST
#define FINAL_TEST

typedef struct
{
	ALLEGRO_DISPLAY* display = nullptr;
	ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
}resources;

bool Init(resources* r); //Inicializa todos los recursos necesarios.
void DoExit(resources* r); //Se ocupa ded todos los recurso a la salida del programa.

int main()
{

#ifdef FINAL_TEST
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

#endif //FINAL_TEST


#ifdef MENU_TEST
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
	menuView.manageSoundtrack();

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

#endif //MENU_TEST

#ifdef NETWORKING_TEST
	char user_name[256];
	char ip[MAX_IP_LENGTH + 1];
	std::string pckg;
	pckg += NAME_IS_HEADER;
	bool sent = false;
	NetworkingModel* NWM = new NetworkingModel();
	std::ifstream ip_file("./ip.txt");
	std::ifstream name_file("./temporal.txt");
	ip_file.getline(ip, MAX_IP_LENGTH); //Consigo la ip del otro jugador
	name_file.getline(user_name, 255); //Consigo el nombre de mi usuario.
	std::string user_nameS(user_name);

	NWM->setMe(user_nameS);
	pckg += (char)user_nameS.size();
	pckg += user_nameS;
	srand(time(NULL));
	int waiting_time = 2000 + (rand() % 3000); //genera un tiempo de espera aleatorio entre 2000 y 5000 milisegundos.
	if ((NWM->connectAsClient(waiting_time, ip)))
	{
		NWM->setServer(CLIENT);
		sent = NWM->sendPackage((char*)pckg.c_str(), pckg.size()); //mando mi nombre
		if (!sent)
		{
			NWM->Shutdown();
		}
	}
	else
	{
		if (NWM->connectAsServer()) //recibo el paquete con el nombre
		{
			NWM->setServer(SERVER);
			NWM->StartReading();
			while (!(NWM->WasPackageRecieved()))
			{
				NWM->GetReading();
			}
			std::cout << std::endl << NWM->GetPackage() << std::endl;
		}
	}
	getchar();
#endif //NETWORKING_TEST
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