#include	"nc_tcp_server.h"

#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>

#include	"nc_server.h"
#include	"nc_tcp_connection.h"

NCTCPServer::NCTCPServer()
	: socket_descriptor_(0), port_(0)
{
	::memset(&socket_address_, 0, sizeof(socket_address_));
}

NCTCPServer::~NCTCPServer()
{
	this->close();
}

void NCTCPServer::open(int port)
{
	port_ = port;
	socket_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor_ == -1) {
		// TODO(2/8):perrorではなくExceptionをthrowすべき
		perror("socket");
		return;
	}
	
	socket_address_.sin_family = AF_INET;
	socket_address_.sin_port = htons(port_);
	socket_address_.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(	socket_descriptor_, 
			(struct sockaddr*)(&socket_address_),
			sizeof(socket_address_))			== -1) {
		perror("bind");
		this->close();
		return;
	}

	if (listen(socket_descriptor_, CONNECTION_QUEUE_MAX) == -1) {
		perror("listen");
		this->close();
		return;
	}
}


NCConnection& NCTCPServer::waitForConnection()
{
	int descriptor = accept(socket_descriptor_, NULL, NULL);

	if (descriptor == -1) {
		perror("accept");
		this->close();
	}
	
	NCTCPConnection* connection = new NCTCPConnection();

	connection->connection_descriptor_ = descriptor;

	connections_.push_back(connection);		

	return *connection;
}

void NCTCPServer::close()
{
	std::vector<NCConnection*>::iterator itr = connections_.begin();

	while (itr != connections_.end()) {
		(*(itr))->close();
		itr++;
	}

	::close(socket_descriptor_);
}
