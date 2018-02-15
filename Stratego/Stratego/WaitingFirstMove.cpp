#include "WaitingFirstMove.h"

WaitingFirstMove::WaitingFirstMove()
{
#ifdef DEBUG
	std::cout << std::endl << "In WaitingFirstMove" << endl;
#endif //DEBUG
}


NetworkingState* WaitingFirstMove::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState * p_state = nullptr;
	Gm->setState(OP_TURN); //Es el turno del oponente.
	std::string pckg = ev.GetRecieved();
	int original_posY = pckg[1] - 'A'; //Le resta el valor de la primera columna para obtener el numero.
	int original_posX = pckg[2] - 1; //le resta uno porque tomamos posiciones de 0 a 9 y llegan de 1 a 10.

	int destination_posY = pckg[3] - 'A';
	int destination_posX = pckg[4] - 1;

	pos origin(original_posX, original_posY);
	pos destination(destination_posX, destination_posY);
	if (!(Gm->getRed())) //Si soy azul invierto las posiciones
	{
		InvertPositionToLayout(&origin);
		InvertPositionToLayout(&destination);
	}
	if (!(ValidateMovement(Gm, origin, destination)))
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	else
	{
		if (!(Gm->move(origin, destination))) //Si devuelve false es porque el move fue un ataque.
		{
			ErrorRoutine(p_nwm, Gm); //La primer movida no puede ser un ataque.
			p_state = new Quiting;

		}
		else //El move no fue un ataque
		{
			Gm->setState(MY_TURN); //Ya se realizo la movida del oponente asique es mi turno.
			Gm->setMessage("Please Make a move");
			Gm->restartTimer();
			p_state = new WaitingMove; //No cambia de estado.
		}
	}

	return p_state;

}
NetworkingState* WaitingFirstMove::You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	Gm->playerWon();
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	Gm->setMessage("Enemy's time up or couldn't move");
	NetworkingState * p_state = new WaitingPlayerDecision;
	return p_state;
}