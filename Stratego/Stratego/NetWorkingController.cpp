#include "NetWorkingController.h"

NetWorkingController::NetWorkingController(GameModel* p2GameModel)
{
	NWM = new NetworkingModel(); //Recibe algo para construirse?
	Gm = p2GameModel;
	proxState = nullptr;
	srand(time(NULL));
	int waiting_time = 2000 + (rand() % 3000); //genera un tiempo de espera aleatorio entre 2000 y 5000 milisegundos.
	char pckg[1];
	if ((NWM->connectAsClient(waiting_time, ip))) //hay que conseguir el ip del otro y pasarselo.
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
	//Antes de entrar a la fsm habria que ver si hay que mandar un paquete de move.
	//o de ru_ready.
	if ( Gm->getMoveDone()) //El usuario hizo un movimiento valido
	{
		Gm->setMoveDoneFalse();
		char move_pckg[5];
		move_pckg[0] = MOVE_HEADER;
		char or_col = 'A'+ (char) ((Gm->GetmyPosStatus()).previous.y);
		char or_row = 1+ ((Gm->GetmyPosStatus()).previous.x);
		char des_col = 'A' + (char)((Gm->GetmyPosStatus()).next.y);
		char des_row = 1 + ((Gm->GetmyPosStatus()).next.x);
		move_pckg[1] = or_col;
		move_pckg[2] = or_row;
		move_pckg[3] = des_col;
		move_pckg[4] = des_row;
		NWM->sendPackage(move_pckg, 5); //Manda el paquete de move.
		delete actualState;
		if ( (Gm->getState()) == MY_MOVING)
		{
			actualState = new WaitingMove; //Si es pasivo espero un move
			Gm->setState(OP_TURN);
		}

		else
		{
			actualState = new StartingAttack; //Si es ofensivo espero un ataque.
			Gm->setState(OP_TURN);
		}
		actualState = new WaitingMove;


		

	}
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
}