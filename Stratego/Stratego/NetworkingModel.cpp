#include "NetworkingModel.h"
#include <iostream>


NetworkingModel::NetworkingModel()
{
	//Flags
	package_recieved = false;
	comm_error = false;
	reading = false;
	finished_writing = false;
	time_done = false;
	serverStat = UNINITIALIZED;
	server_Finished_placing_fichas = false;

	//Recursos de Boost
	IO_handler = new boost::asio::io_service;
	deadline_= new deadline_timer(*IO_handler);
	socket_a = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = nullptr;
	endpoint_a = nullptr;

}

bool NetworkingModel::sendPackage(char * message, int size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		buffer_for_writing[i] = message[i];
	}
	buffer_for_writing[i] = '\0';
	boost::asio::async_write(*socket_a, boost::asio::buffer(buffer_for_writing, size),
							boost::bind(&NetworkingModel::write_handler, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred) );
	while (!finished_writing)
	{
		IO_handler->poll(); //Se fija si hay handlers que dispatchear hasta que termina de escribir.
	}
	finished_writing = false;
	if (comm_error)
	{
		return false;
	}
	else
	{
		IO_handler->reset();
		return true;
	}
}

void NetworkingModel::StartReading()
{
	reading = true;
	boost::asio::async_read(*socket_a, boost::asio::buffer(buffer_for_reading),
							boost::bind(&NetworkingModel::completion_condition, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred),
							boost::bind(&NetworkingModel::read_handler, this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));

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

bool NetworkingModel::GetReading()
{
	IO_handler->poll();
	return reading;
}

bool NetworkingModel::WasPackageRecieved()const
{
	return package_recieved;
}
void NetworkingModel::setYou(std::string you_)
{
	you = you_;
}

std::string  NetworkingModel::GetPackage()
{
	package_recieved = false;
	IO_handler->reset();
	std::string aux;
	for (unsigned int i = 0; i < package_size; i++)
	{
		aux += buffer_for_reading[i];
	}
	return aux;
	
}
bool NetworkingModel::GetServerFinishedPlacing()const
{
	return server_Finished_placing_fichas;
}

void NetworkingModel::SetServerFinishedPlacing(bool value)
{
	server_Finished_placing_fichas = value;
}

bool NetworkingModel::connectAsClient(int time,char * ip)	
{															
	endpoint_a = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), PORT);
	std::cout << "Trying to connect to " << ip << " on port " << PORT_C << std::endl;
	deadline_->expires_from_now(boost::posix_time::milliseconds(time)); //Tiempo a tratar la conexion.
	deadline_->async_wait(boost::bind(&NetworkingModel::timer_handler, this, boost::asio::placeholders::error));
	socket_a->async_connect(*endpoint_a, boost::bind(&NetworkingModel::client_connect_handler, this,
            boost::asio::placeholders::error) );
	IO_handler->run();

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
	server_acceptor->async_accept(*socket_a, boost::bind(&NetworkingModel::server_connect_handler,
								this, boost::asio::placeholders::error));
	IO_handler->reset();
	IO_handler->run(); //Como esta ahora, bloquea hasta conectarse como server o que haya error.
	IO_handler->reset();
	if (!comm_error)
	{
		return true;
	}
	else
	{
		Shutdown();
		return false;

	}
}


NetworkingModel::~NetworkingModel()
{
	if (socket_a != nullptr)	//cierro y destruyo el socket.
	{
		if (socket_a->is_open())
		{
			socket_a->close();
		}
		delete socket_a;
	}

	if (endpoint_a != nullptr) //destruyo el endpoint
	{
		delete endpoint_a;
	}

	if (server_acceptor != nullptr) //destruyo el acceptor.
	{
		server_acceptor->close();
		delete server_acceptor;
	}
	if (deadline_ != nullptr) //destruyo el timer de boost.
	{
		delete deadline_;
	}

	if (IO_handler != nullptr) //destruyo el servicio de boost.
	{
		delete IO_handler;
	}
}

void NetworkingModel::Shutdown()
{
	if (socket_a->is_open())
	{
		socket_a->close();
	}

	deadline_->cancel();
}


void NetworkingModel::client_connect_handler(const boost::system::error_code& error)
{
	
	if (!error)
	{
		deadline_->expires_at(boost::posix_time::pos_infin); //Para que no vuelva a llamarlo hasta que se defina nuevo tiempo.
		std::cout << "Connected Succesfully As Client." << std::endl;
		serverStat = CLIENT;
	}
	else
	{
		std::cout << error.message() << std::endl;
		comm_error = true;
	}
}

void  NetworkingModel::server_connect_handler(const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "Connected Succesfully As Server." << std::endl;
		serverStat = SERVER;
	}
	else
	{
		std::cout << error.message() << std::endl;
		comm_error = true;
	}
}

void NetworkingModel::timer_handler(const boost::system::error_code& error)
{
	if (!error)
	{
		//Expiro el timer.
		time_done = true;
		socket_a->close(); //Interrumpe la conexion.
		deadline_->expires_at(boost::posix_time::pos_infin); //Para que no vuelva a llamarlo hasta que se defina nuevo tiempo.
	}
	else if(error && error != boost::asio::error::operation_aborted)
	{
		std::cout << error.message() << std::endl;
		socket_a->close(); //Interrumpe la conexion.
	}
}

std::size_t NetworkingModel::completion_condition(const boost::system::error_code& error,
													std::size_t bytes_transferred)
{
	if (!error)
	{
		unsigned char name_size = 0;
		if (bytes_transferred > 0)
		{
			switch (buffer_for_reading[0])
			{
				case ACK_HEADER:
				case NAME_HEADER:
				case YOU_START_HEADER:
				case I_START_HEADER:
				case R_U_READY_HEADER:
				case I_AM_READY_HEADER:
				case YOU_WON_HEADER:
				case PLAY_AGAIN_HEADER:
				case GAME_OVER_HEADER:
				case QUIT_HEADER:
				case ERROR_HEADER:
						if (bytes_transferred == 1)
						{
							return 0;
						}
						else
						{
							comm_error = true; //error
							return 0;
						}
						break;
				case NAME_IS_HEADER:
					
					if (bytes_transferred > 1)
					{
						name_size = buffer_for_reading[1];
						return (name_size + 2 - bytes_transferred); //Vale 0 cuando se recibio el paquete completo.
					}
					else
					{
						return 1;
					}
					break;
				case MOVE_HEADER:
					if (bytes_transferred < 6)
					{
						return (5 - bytes_transferred);
					}
					else
					{
						comm_error;
						return 0;
					}
					break;
				case ATTACK_HEADER:
					if (bytes_transferred < 3)
					{
						return (2 - bytes_transferred);
					}
					else
					{
						comm_error = true;
						return 0;
					}
					break;
				default:
					comm_error = true; //error
					return 0;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		comm_error = true;
		std::cout << std::endl << error.message() << std::endl;
		return 0;
	}
}

void NetworkingModel::read_handler(const boost::system::error_code& error,
					std::size_t bytes_transferred)
{
	if (!error)
	{
		reading = false;
		package_recieved = true;
		package_size = bytes_transferred;
		if (comm_error)
		{
			Shutdown();
		}
		
	}
	else
	{
		std::cout << std::endl << error.message() << std::endl;
		comm_error = true;
		Shutdown();
	}
}

void NetworkingModel::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		finished_writing = true;
	}
	else
	{
		std::cout << std::endl << error.message() << std::endl;
		comm_error = true;
		Shutdown();
	}
}