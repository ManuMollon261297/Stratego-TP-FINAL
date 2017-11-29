#include "NetworkingModel.h"



NetworkingModel::NetworkingModel() //TERMINAR
{
}

bool NetworkingModel::sendPackage(char * message, int size) //TERMINAR
{
	return false;
}

std::vector<char>* NetworkingModel::readPackage() //TERMINAR (FIJARSE BIEN QUE DEVUELVE)
{
	return nullptr;
}

int NetworkingModel::getState()
{
	return state;
}

void NetworkingModel::setState(int state_)
{
	state = state_;
}

bool NetworkingModel::getServer()
{
	return server;
}

void NetworkingModel::setServer(bool server_)
{
	server = server_;
}

std::string NetworkingModel::getMe()
{
	return me;
}

void NetworkingModel::setMe(std::string me_)
{
	me = me_;
}

std::string NetworkingModel::getYou()
{
	return you;
}

void NetworkingModel::setYou(std::string you_)
{
	you = you_;
}

bool NetworkingModel::connectAsClient(int timer) //TERMINAR
{
	return false;
}

bool NetworkingModel::connectAsServer()  //TERMINAR
{
	return false;
}


NetworkingModel::~NetworkingModel() //TERMINAR
{
}
