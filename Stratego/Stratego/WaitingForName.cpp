#include "WaitingForName.h"



NetworkingState*  WaitingName::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state;
	p_state = new WaitingNameResponse; //espero respuesta de que llego el paquete.
	bool sent = false;
	std::string my_name = (p_nwm->getMe());
	unsigned char count = my_name.size();
	std::string pckg;
	pckg.append(1, NAME_IS_HEADER);
	pckg.append(1, count);
	pckg += my_name;
	do
	{
		sent = p_nwm->sendPackage((char*)pckg.c_str(), pckg.size()); //Mando paquete con mi nombre
	} while (!sent);
	return p_state;

}