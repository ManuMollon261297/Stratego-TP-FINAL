#pragma once

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define		PORT	13225
#define		PORT_C	"13225"

enum serverStatus {SERVER,CLIENT,UNINITIALIZED};
class NetworkingModel
{
public:
	NetworkingModel();
	bool sendPackage(char * message, int size); //envia un paquete de chars de tamanio size
	std::vector<char> readPackage(); // busca si llego un package 
	int getState();
	void setState(int state_);
	bool getServer();
	void setServer(serverStatus server_);
	std::string getMe();
	void setMe(std::string me_);
	std::string getYou();
	void setYou(std::string you_);
	bool connectAsClient(int timer, char * ip); //trata de conectarse al puerto como client por un determinado tiempo
	bool connectAsServer();
	~NetworkingModel();
private:
	int state;
	int port;
	serverStatus serverStat;
	std::string me;
	std::string you;
	//boost
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};

