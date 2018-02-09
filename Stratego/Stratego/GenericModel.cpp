#include "GenericModel.h"



GenericModel::~GenericModel()
{
	for (unsigned int i =0; i< ListOfObservers.size(); i++)
	{
		delete ListOfObservers[i]; //Destruye la memoria alocada
	}
	ListOfObservers.clear();
}

void GenericModel::NotifyAllObservers()
{
	for (unsigned int i = 0; i < ListOfObservers.size(); i++)
	{
		(ListOfObservers[i])->update(); //Le informa a todos los observadores que el
										//modelo cambio.
	}
}

void GenericModel::AttachObserver(GenericObserver* obs)
{
	ListOfObservers.push_back(obs); //Agrega un observador a la lista
}