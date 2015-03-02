#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<netdb.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>



#include	"nc_tcp_client.h"


NCTCPClient::NCTCPClient()
	: NCTCPConnection()
{
	::memset(&socket_address_, 0, sizeof(socket_address_));
}

NCTCPClient::~NCTCPClient()
{
	this->close();
}

int NCTCPClient::open(const std::string host_name, const int port)
{
	port_ = port;
	host_name_ = host_name;

	connection_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
	if (connection_descriptor_ == -1) {
			perror("socket");
			return -1;
	}
	
	socket_address_.sin_family = AF_INET;
	socket_address_.sin_port = htons(port_);

	struct hostent* host_entry = gethostbyname(host_name_.c_str());
	if (host_entry == NULL) {
		perror("gethostbyname");
		return -1;
	}

	memcpy(	&socket_address_.sin_addr, 
					host_entry->h_addr_list[0], 
					sizeof(socket_address_.sin_addr));

	if (connect(connection_descriptor_,
							(struct sockaddr*)&socket_address_,
							sizeof(struct sockaddr_in)) == -1) {
			perror("connect");
			return -1;
	}

	return 0;
}

