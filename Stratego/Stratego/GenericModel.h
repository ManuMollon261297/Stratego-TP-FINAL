#pragma once

#include <vector>
#include "GenericObserver.h"

using namespace std;


class GenericModel
{
public:
	virtual void AttachObserver(GenericObserver&);

protected:
	virtual ~GenericModel();
	virtual void NotifyAllObservers();
	vector <GenericObserver> ListOfObservers;


};