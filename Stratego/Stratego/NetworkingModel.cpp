#include "NetworkingModel.h"
#include <iostream>
#include <boost/exception/all.hpp>

NetworkingModel::NetworkingModel()
{
	timeout_counter = 0;
	//Flags
	name_saved = false;
	tried_as_client = false;
	tried_as_server = false;
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
		return true;
	}
}

void NetworkingModel::TryToConnect(void)
{
	if (!name_saved)
	{
		char user_name[256];
		std::ifstream name_file("./temporal.txt");
		name_file.getline(user_name, 255); //Consigo el nombre de mi usuario.
		std::string user_nameS(user_name);
		setMe(user_nameS);
		setNameSavedTrue();
	}

	if (getServer() == UNINITIALIZED)
	{
		bool ConnectedAsClient = false;
		if (!(GetTriedAsClient()))
		{
			srand(time(NULL));
			int waiting_time = 2000 + (rand() % 3000); //genera un tiempo de espera aleatorio entre 2000 y 5000 milisegundos.
			ConnectedAsClient = connectAsClient(waiting_time, ip);
		}
		if (ConnectedAsClient)
		{
			setServer(CLIENT);

		}
		else
		{
			if (connectAsServer()) //si tuvo exito manda el paquete de name
			{
				char pckg[1];
				setServer(SERVER);
			}
		}


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

bool NetworkingModel::GetNameSaved()const
{
	return name_saved;
}

bool NetworkingModel::GetTriedAsClient()const
{
	return tried_as_client;
}

serverStatus NetworkingModel::getServer()const
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
bool NetworkingModel::TimeEnded()const
{
	if (timeout_counter >= TIMEOUT)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void NetworkingModel::IncrementTime()
{
	timeout_counter++;
}

void NetworkingModel::ResetTimeout()
{
	timeout_counter = 0;
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
	try
	{
		endpoint_a = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), PORT);
		std::cout << "Trying to connect to " << ip << " on port " << PORT_C << std::endl;
		deadline_->expires_from_now(boost::posix_time::milliseconds(time)); //Tiempo a tratar la conexion.
		deadline_->async_wait(boost::bind(&NetworkingModel::timer_handler, this, boost::asio::placeholders::error));
		socket_a->async_connect(*endpoint_a, boost::bind(&NetworkingModel::client_connect_handler, this,
			boost::asio::placeholders::error));
		IO_handler->run();
		IO_handler->reset();
		tried_as_client = true;

		if (time_done)
		{
			time_done = false;
			comm_error = false;
			return false;
		}
		else
		{
			return true;
		}
	}
	catch(boost::exception const&  ex)
	{
		std::cout << std::endl << diagnostic_information(ex) << std::endl;
		return false;
	}
	

}

bool NetworkingModel::connectAsServer()
{
	try
	{
		if (!tried_as_server)
		{
			server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
				boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));
			boost::system::error_code error;
			std::cout << std::endl << "Ready. Port " << PORT << " created" << std::endl;
			server_acceptor->async_accept(*socket_a, boost::bind(&NetworkingModel::server_connect_handler,
				this, boost::asio::placeholders::error));
		}

		IO_handler->poll(); 
		if ((!comm_error)&&(serverStat==SERVER))
		{
			tried_as_server = true;
			IO_handler->reset();
			return true;
		}
		else
		{
			tried_as_server = true;
			return false;

		}
	}
	catch (boost::exception const&  ex)
	{
		std::cout << std::endl << diagnostic_information(ex) << std::endl;
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
		socket_a = nullptr;
	}

	if (endpoint_a != nullptr) //destruyo el endpoint
	{
		delete endpoint_a;
		endpoint_a = nullptr;
	}

	if (server_acceptor != nullptr) //destruyo el acceptor.
	{
		if (server_acceptor->is_open())
		{
			server_acceptor->close();
		}
		delete server_acceptor;
		server_acceptor = nullptr;
	}
	if (deadline_ != nullptr) //destruyo el timer de boost.
	{
		delete deadline_;
		deadline_ = nullptr;
	}

	if (IO_handler != nullptr) //destruyo el servicio de boost.
	{
		delete IO_handler;
		IO_handler = nullptr;
	}
}

void NetworkingModel::Shutdown()
{
	if (socket_a != nullptr)
	{
		if (socket_a->is_open())
		{
			socket_a->close();
		}
	}
	

	if (server_acceptor != nullptr)
	{
		if (server_acceptor->is_open())
		{
			server_acceptor->close();
		}
	}
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
						comm_error = true;
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
	reading = false;
	package_recieved = true;
	if (comm_error)
	{
		buffer_for_reading[0] = READING_ERROR;
		package_size = 1;
	}
	else if (!error)
	{
		package_size = bytes_transferred;
		if (comm_error)
		{
			buffer_for_reading[0] = READING_ERROR;
			package_size = 1;
		}
		
	}
	else
	{
		std::cout << std::endl << error.message() << std::endl;
		comm_error = true;
		buffer_for_reading[0] = READING_ERROR;
		package_size = 1;
	}
}

void NetworkingModel::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	finished_writing = true;
	if(error)
	{
		std::cout << std::endl << error.message() << std::endl;
		comm_error = true;
		Shutdown();
	}
}

void NetworkingModel::setNameSavedTrue()
{
	name_saved = true;
}