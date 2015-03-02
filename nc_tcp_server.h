#ifndef	NC_TCPSERVER_H_
#define	NC_TCPSERVER_H_

#include	<stdio.h>
#include	<unistd.h>
#include	<netinet/in.h>

#include	<vector>

#include	"nc_server.h"

class NCTCPServer : public NCServer {
public:
	static const int CONNECTION_QUEUE_MAX = 128;

	NCTCPServer();
	virtual ~NCTCPServer();

	// Override(NCServer)
	void open(int port);
	NCConnection& waitForConnection();
	void close();


private:
	int socket_descriptor_;
	struct sockaddr_in socket_address_;
	std::vector<NCConnection*> connections_;
	
	int port_;
};
#endif	// NC_TCPSERVER_H_
