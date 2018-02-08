#pragma once

#include <vector>
#include "GenericObserver.h"

using namespace std;


class GenericModel
{
protected:
	virtual ~GenericModel();
	virtual void NotifyAllObservers();
	virtual void AttachObserver(GenericObserver&);
	vector <GenericObserver> ListOfObservers;


};