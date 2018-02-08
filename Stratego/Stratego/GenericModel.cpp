#include "GenericModel.h"



GenericModel::~GenericModel()
{
	ListOfObservers.clear();
}

void GenericModel::NotifyAllObservers()
{
	for (unsigned int i = 0; i < ListOfObservers.size(); i++)
	{
		(ListOfObservers[i]).update(); //Le informa a todos los observadores que el
										//modelo cambio.
	}
}

void GenericModel::AttachObserver(GenericObserver& obs)
{
	ListOfObservers.push_back(move(obs)); //Agrega un observador a la lista
}