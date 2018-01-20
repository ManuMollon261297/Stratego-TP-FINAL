#include "NetWorkingController.h"

NetWorkingController::NetWorkingController(GameModel* p2GameModel)
{
	char user_name[256];
	NWM = new NetworkingModel(new boost::asio::io_service());
	std::ifstream ip_file("./ip.txt");
	std::ifstream name_file("./temporal.txt");
	ip_file.getline(ip, MAX_IP_LENGTH); //Consigo la ip del otro jugador
	name_file.getline(user_name, 255); //Consigo el nombreo de mi usuario.
	std::string user_nameS(user_name);

	NWM->setMe(user_nameS);
	Gm = p2GameModel;
	proxState = nullptr;
	srand(time(NULL));
	int waiting_time = 2000 + (rand() % 3000); //genera un tiempo de espera aleatorio entre 2000 y 5000 milisegundos.
	char pckg[1];
	if ((NWM->connectAsClient(waiting_time, ip))) 
	{
		NWM->setServer(CLIENT);
		actualState = new WaitingName;
	}
	else
	{
		if (NWM->connectAsServer()) //si tuvo exito manda el paquete de name
		{
			NWM->setServer(SERVER);
			pckg[0] = NAME_HEADER;
			NWM->sendPackage(pckg, 1);
			actualState = new WaitingNameIs;
		}
	}
}

NetWorkingController::~NetWorkingController()
{
	delete NWM;
}

void NetWorkingController::dispatch(GenericEvent& newEvent)
{
	
	if ((newEvent.GetEvent()) == NET )
	{
		switch ( (((NetWorkingEvent&)newEvent).GetRecieved())[0] ) //revisar bien, tal vez hay que castear a char o algo.
		{
		case PLAY_AGAIN_HEADER:
			proxState = actualState->Play_again((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case NAME_HEADER:
			proxState = actualState->Name((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case NAME_IS_HEADER:
			proxState = actualState->Name_is((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case R_U_READY_HEADER:
			proxState = actualState->R_u_ready((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case I_AM_READY_HEADER:
			proxState = actualState->I_am_ready((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case I_START_HEADER:
			proxState = actualState->I_start((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case YOU_START_HEADER:
			proxState = actualState->You_start((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case ERROR_HEADER:
			proxState = actualState->Error((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case QUIT_HEADER:
			proxState = actualState->Quit((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case ACK_HEADER:
			proxState = actualState->Ack((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case GAME_OVER_HEADER:
			proxState = actualState->Game_over((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case MOVE_HEADER:
			proxState = actualState->Move((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case ATTACK_HEADER:
			proxState = actualState->Attack((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		case YOU_WON_HEADER:
			proxState = actualState->You_won((NetWorkingEvent&)newEvent, NWM, Gm);
			break;
		}

		if (proxState != nullptr)
		{
			delete actualState;
			actualState = proxState;
			proxState = nullptr;
		}
	}
	else if ((newEvent.GetEvent()) == MOUSE)
	{
		switch (Gm->getState())
		{
		case ENDING_PLACING_FICHAS:
			proxState = actualState->EndedPlacing(NWM, Gm);
			break;
		case GAME_OVER_SELECTED:
			proxState = actualState->SelectedGameOver(NWM, Gm);
			break;
		case PLAY_AGAIN_SELECTED:
			proxState = actualState->SelectedPlayAgain(NWM, Gm);
			break;
		case MY_MOVING:
			proxState = actualState->MoveDone(NWM, Gm);
			break;
		case MY_ATTACKING:
			proxState = actualState->AttackDone(NWM, Gm);
			break;
		}
		if (proxState != nullptr)
		{
			delete actualState;
			actualState = proxState;
			proxState = nullptr;
		}
	}
		
}