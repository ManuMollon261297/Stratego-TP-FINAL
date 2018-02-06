#include "WaitingForName.h"



NetworkingState*  WaitingName::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
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

NetworkingState* WaitingName::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = nullptr;
	p_nwm->IncrementTime();
	if (p_nwm->TimeEnded())
	{
		char error_pckg[1] = { ERROR_HEADER };
		p_state = new Quiting;
		Gm->SetExit(true);
		Gm->setMessage("Se perdio la comunicacion, cerrando...");
		p_nwm->sendPackage(error_pckg, 1);
		p_nwm->Shutdown();
	}
	return p_state;
}