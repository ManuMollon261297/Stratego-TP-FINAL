#include "mouseGameController.h"
#include "AllegroViewer.h"
#include "menuMouseController.h"
#include "MenuViewer.h"
#include "NetworkingModel.h"
#include <fstream>

using namespace std;

dataButtonsPos fillButtonsInfo(void);

void printStateModel(int state);
#define MAX_IP_LENGTH 45
#define NETWORKING_TEST
//#define MENU_TEST

int main()
{
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
	bool sent = false;
	NetworkingModel* NWM = new NetworkingModel();
	std::ifstream ip_file("./ip.txt");
	std::ifstream name_file("./temporal.txt");
	ip_file.getline(ip, MAX_IP_LENGTH); //Consigo la ip del otro jugador
	name_file.getline(user_name, 255); //Consigo el nombre de mi usuario.
	std::string user_nameS(user_name);

	NWM->setMe(user_nameS);
	srand(time(NULL));
	int waiting_time = 2000 + (rand() % 3000); //genera un tiempo de espera aleatorio entre 2000 y 5000 milisegundos.
	if ((NWM->connectAsClient(waiting_time, ip)))
	{
		NWM->setServer(CLIENT);
		sent = NWM->sendPackage((char*)user_nameS.c_str(), user_nameS.size()); //mando mi nombre
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

dataButtonsPos fillButtonsInfo(void)
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