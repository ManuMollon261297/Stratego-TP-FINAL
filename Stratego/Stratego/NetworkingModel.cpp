#include "NetworkingModel.h"
#include <iostream>


NetworkingModel::NetworkingModel()
{
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	socket->non_blocking(true);
	serverStat = UNINITIALIZED;
}

bool NetworkingModel::sendPackage(char * message, int size)
{
	size_t len;
	boost::system::error_code error;
	do
	{
		len = socket->write_some(boost::asio::buffer(message, size), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool NetworkingModel::connectAsClient(int timer,char * ip)	// HACER QUE DURE SOLO EL PERIODO DEL TIMER Y FIJARSE EL TEMA
{															//  DEL IP
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, PORT_C));
	std::cout << "Trying to connect to " << ip << " on port " << PORT_C << std::endl;
	boost::asio::connect(*socket, endpoint);
}

bool NetworkingModel::connectAsServer()
{
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));
	boost::system::error_code error;
	std::cout << std::endl << "Ready. Port " << PORT << " created" << std::endl;
	server_acceptor->accept(*socket, error);
	if (!error)
	{
		return true;
	}
	else //error connecting to client
	{
		return false;
	}

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
