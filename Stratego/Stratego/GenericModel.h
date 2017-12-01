#pragma once

#include <vector>

using namespace std;


class GenericModel
{
protected:

	virtual void NotifyAllObservers();
	virtual void AttachObserver();
	vector <int> ListOfObservers;


};