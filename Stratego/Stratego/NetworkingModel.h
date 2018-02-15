#pragma once

#include "GenericModel.h"
#include <string>
#include <vector>
#include <fstream>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using boost::asio::deadline_timer;

//Headers de los paquetes
#define ACK_HEADER (char)0x01
#define NAME_HEADER (char)0x10
#define NAME_IS_HEADER (char)0x11
#define YOU_START_HEADER (char)0x20
#define I_START_HEADER (char)0x21
#define R_U_READY_HEADER (char)0x22
#define I_AM_READY_HEADER (char)0x23
#define MOVE_HEADER (char)0x30
#define ATTACK_HEADER (char)0x31
#define YOU_WON_HEADER (char)0x40
#define PLAY_AGAIN_HEADER (char)0x50
#define GAME_OVER_HEADER (char)0x51
#define ERROR_HEADER (char)0xFE
#define QUIT_HEADER (char)0xFF

#define READING_ERROR (char)0xCC //No es del protocolo de comunicacion,
								//sirve para detectar errores de lectura.

#define		PORT	13225
#define		PORT_C	"13225"

//Timer
#define TIMEOUT 150 //despues de 2 minutos y medio sin respuesta 
					//se asumme que se perdio la comunicacion.

#define MAX_IP_LENGTH 45


enum serverStatus {SERVER,CLIENT,UNINITIALIZED};
class NetworkingModel : public GenericModel
{
public:
	NetworkingModel();
	bool sendPackage(char * message, int size); //envia un paquete de chars de tamanio size
	void StartReading(); // busca si llego un package 
	void TryToConnect(void);
	serverStatus getServer()const;
	void setServer(serverStatus server_);
	bool GetServerFinishedPlacing()const;
	void SetServerFinishedPlacing(bool);
	std::string getMe();
	void setMe(std::string me_);
	bool GetReading();
	bool GetNameSaved()const;
	bool GetTriedAsClient()const;
	bool WasPackageRecieved()const;
	std::string GetPackage();
	bool TimeEnded()const;
	void IncrementTime();
	void ResetTimeout();
	void setNameSavedTrue();
	bool connectAsClient(int timer, char * ip); //trata de conectarse al puerto como client por un determinado tiempo
	bool connectAsServer();
	void Shutdown();
	char ip[MAX_IP_LENGTH + 1]; //ip del otro jugador
	~NetworkingModel();
private:
	bool name_saved; //Guarda si ya se consiguio el nombre del usuario
	bool tried_as_client; //Inica si ya se intento conectar como cliente.
	bool tried_as_server;
	bool comm_error;
	bool server_Finished_placing_fichas;
	bool time_done;
	bool reading; //Indica si se termino de llenar el buffer o no.
	bool finished_writing;
	std::size_t package_size;
	bool package_recieved;
	unsigned int timeout_counter;
	char buffer_for_reading[300];
	char buffer_for_writing[300];
	serverStatus serverStat;
	std::string me;

	//Handlers
	void client_connect_handler(const boost::system::error_code& error);
	void server_connect_handler(const boost::system::error_code& error);
	void timer_handler(const boost::system::error_code& error);
	std::size_t completion_condition(const boost::system::error_code& error,
									std::size_t bytes_transferred);

	void read_handler(const boost::system::error_code& error,
					std::size_t bytes_transferred );
	void write_handler(const boost::system::error_code& error,
		std::size_t bytes_transferred);

	//boost
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_a;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	boost::asio::ip::tcp::endpoint* endpoint_a;
	deadline_timer* deadline_;
};

