#pragma once

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define PORT	13225

class NetworkingModel
{
public:
	NetworkingModel();
	bool sendPackage(char * message, int size); //envia un paquete de chars de tamanio size
	std::vector<char> * readPackage(); // busca si llego un package 
	int getState();
	void setState(int state_);
	bool getServer();
	void setServer(bool server_);
	std::string getMe();
	void setMe(std::string me_);
	std::string getYou();
	void setYou(std::string you_);
	bool connectAsClient(int timer); //trata de conectarse al puerto como client por un determinado tiempo
	bool connectAsServer();
	~NetworkingModel();
private:
	int state;
	bool server;
	std::string me;
	std::string you;
	//boost
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};

/* CLIENT
Client::Client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

Client::~Client() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}
*/

/* SERVER
void Server::listening() {
server_acceptor->accept(*socket_forServer);
socket_forServer->non_blocking(true);
}


Server::Server(int port) {
IO_handler = new boost::asio::io_service();
socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));
std::cout << std::endl << "Ready. Port " << PORT << " created" << std::endl;
}

Server::~Server() {
server_acceptor->close();
socket_forServer->close();
delete server_acceptor;
delete socket_forServer;
delete IO_handler;
}
*/

