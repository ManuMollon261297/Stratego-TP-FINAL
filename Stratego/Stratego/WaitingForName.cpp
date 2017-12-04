#include "WaitingForName.h"



NetworkingState*  WaitingName::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state;
	std::string my_name = (p_nwm->getMe());
	unsigned char count = my_name.size();
	std::string pckg;
	pckg[0] = NAME_IS_HEADER;
	pckg[1] = count;
	pckg += my_name;
	p_nwm->sendPackage((char*)pckg.c_str(), pckg.size()); //Mando paquete con mi nombre
	p_state = new WaitingNameResponse; //espero respuesta de que llego el paquete.
	return p_state;

}