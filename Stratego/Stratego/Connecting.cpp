#include "Connecting.h"


Connecting::Connecting()
{
#ifdef DEBUG
	std::cout << std::endl << "In Connecting" << std::endl;
#endif //DEBUG
}

NetworkingState* Connecting::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
{
	NetworkingState* p_state = nullptr;
	p_nwm->TryToConnect();
	if (p_nwm->getServer() == UNINITIALIZED)
	{
		if (p_nwm->GetTriedAsClient())
		{
			MM->setMessage("Timeout, connecting as server");
		}
		else
		{
			MM->setMessage("Trying to connect as Client");
		}
	}
	else if (p_nwm->getServer() == SERVER)
	{
		MM->setMessage("Connected succesfully as Server");
		char pckg[1] = {MOVE_HEADER};
		bool sent = false;
		sent = p_nwm->sendPackage(pckg, 1);
		if (!sent)
		{
			ErrorRoutine(p_nwm, Gm);
			return new Quiting;
		}
		return  new WaitingNameIs;
	}
	else 
	{
		MM->setMessage("Connected succesfully as Client");
		return new WaitingName;
	}
	return p_state;
}