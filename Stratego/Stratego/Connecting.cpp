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
		return  new WaitingNameIs;
	}
	else 
	{
		MM->setMessage("Connected succesfully as Client");
		return new WaitingName;
	}
	p_nwm->TryToConnect();
	return p_state;
}