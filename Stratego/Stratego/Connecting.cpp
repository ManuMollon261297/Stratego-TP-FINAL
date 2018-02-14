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
		MM->setMessage("Loading...");
		char pckg[1] = {NAME_HEADER};
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
		MM->setMessage("Loading...");
		return new WaitingName;
	}
	return p_state;
}

NetworkingState* Connecting::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = nullptr;

	if (p_nwm->getServer() == CLIENT)
	{
		NetworkingState* p_state;
		p_nwm->ResetTimeout(); //reinicio el timeout de comunicacion.
		p_state = new WaitingNameResponse; //espero respuesta de que llego el paquete.
		bool sent = false;
		std::string my_name = (p_nwm->getMe());
		unsigned char count = my_name.size();
		std::string pckg;
		pckg.append(1, NAME_IS_HEADER);
		pckg.append(1, count);
		pckg += my_name;
		sent = p_nwm->sendPackage((char*)pckg.c_str(), pckg.size()); //Mando paquete con mi nombre
		if (!sent) //Error de comunicacion.
		{
			Gm->SetExit(true);
			p_state = new Quiting;
		}
		return p_state;
	}
	else
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	return p_state;

}