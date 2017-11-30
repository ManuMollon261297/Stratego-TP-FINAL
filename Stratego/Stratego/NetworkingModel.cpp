#include "NetworkingModel.h"
#include <iostream>


NetworkingModel::NetworkingModel()
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	socket->non_blocking(true);
	serverStat = UNINITIALIZED;
}

bool NetworkingModel::sendPackage(char * message, int size) //TERMINAR
{
	return false;
}

std::vector<char> NetworkingModel::readPackage()
{
	std::vector<char> aux;
	size_t len = 0;
	boost::system::error_code error;
	do
	{
		len = socket->read_some(boost::asio::buffer(aux), error);

	} while (error.value() == WSAEWOULDBLOCK);
	return aux;
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
	return serverStat;
}

void NetworkingModel::setServer(serverStatus server_)
{
	serverStat = server_;
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
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

bool NetworkingModel::connectAsServer()  //TERMINAR
{
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));
	std::cout << std::endl << "Ready. Port " << PORT << " created" << std::endl;
}


NetworkingModel::~NetworkingModel()
{
	socket->close();
	delete socket;
	delete IO_handler;
	if (serverStat == SERVER)
	{
		server_acceptor->close();
		delete server_acceptor;
	}
	else if(serverStat == CLIENT)
	{
		delete client_resolver;
	}
	else if (serverStat == UNINITIALIZED)
	{
		//do nothing
	}
}
