#include "NetworkingModel.h"
#include <iostream>

void timer_handler(const boost::system::error_code& error);

NetworkingModel::NetworkingModel(boost::asio::io_service* serv) : deadline_(*serv), heartbeat_timer_(*serv)
{
	boost::asio::io_service* IO_handler = serv;
	time_done = false;
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	socket->non_blocking(true);
	serverStat = UNINITIALIZED;
	server_Finished_placing_fichas = false;
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

serverStatus NetworkingModel::getServer()
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


bool NetworkingModel::GetServerFinishedPlacing()const
{
	return server_Finished_placing_fichas;
}

void NetworkingModel::SetServerFinishedPlacing(bool value)
{
	server_Finished_placing_fichas = value;
}

bool NetworkingModel::connectAsClient(int time,char * ip)	// Fijarse el tema del IP.
{															
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, PORT_C));
	std::cout << "Trying to connect to " << ip << " on port " << PORT_C << std::endl;
	//boost::asio::connect(*socket, endpoint);
	deadline_.expires_from_now(boost::posix_time::milliseconds(time)); //Tiempo a tratar la conexion.
	deadline_.async_wait(&NetworkingModel::timer_handler);
	boost::asio::async_connect(*socket, endpoint, &NetworkingModel::client_connect_handler); //Creo que seria asi para que funque con timer
	while (  (!time_done)&&(serverStat!= CLIENT) )
	{
		//Espera hasta que se conecte como cliente o hasta que termine el tiempo de time out.
	};

	if (time_done)
	{
		time_done = false;
		return false;
	}
	else
	{
		return true;
	}

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

void NetworkingModel::Shutdown()
{
	time_done = true;
	boost::system::error_code ignored_ec;
	(*socket).close(ignored_ec);
	deadline_.cancel();
	heartbeat_timer_.cancel();
}


void NetworkingModel::client_connect_handler(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iterator_)
{
	if (time_done)
	{
		return;
	}
		


	if (!(socket->is_open()))
	{
		std::cout << "Connect timed out\n";
	}

	// Check if the connect operation failed before the deadline expired.
	else if (error)
	{
		std::cout << "Connect error: " << error.message() << std::endl;

		socket->close();
	}
	else
	{
		std::cout << "Connected to " << iterator_->endpoint() << std::endl;
		serverStat = CLIENT;
	}
}

void NetworkingModel::timer_handler(const boost::system::error_code& error)
{
	if (!error)
	{
		//Expiro el timer.
		time_done = true;
		socket->close(); //Interrumpe la conexion.
		deadline_.expires_at(boost::posix_time::pos_infin); //Para que no vuelva a llamarlo hasta que se defina nuevo tiempo.
	}
}