#include "RefreshEvent.h"

RefreshEvent::RefreshEvent()
{
}

RefreshEvent::RefreshEvent(GenericEvent evnt)
{
	SetUd(evnt.GetUd());
	SetEvent(evnt.GetEvent());
}
