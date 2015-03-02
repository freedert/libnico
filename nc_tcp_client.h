#ifndef	NC_TCP_CLIENT_H_
#define	NC_TCP_CLIENT_H_

#include	<stdio.h>
#include	<unistd.h>
#include	<netinet/in.h>

#include	<string>
#include	"nc_tcp_connection.h"


class NCTCPClient : public NCTCPConnection {
public:
	NCTCPClient();
	virtual ~NCTCPClient();

	int open(const std::string host_name, const int port);

private:
	struct sockaddr_in socket_address_;

	int port_;
	std::string host_name_;
};	

#endif	// NC_TCP_CLIENT_H_

