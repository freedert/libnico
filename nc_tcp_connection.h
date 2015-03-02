#ifndef	NC_TCP_CONNECTION_H_
#define	NC_TCP_CONNECTION_H_

#include	"nc_connection.h"

class NCTCPConnection : public NCConnection {
public:
	static const int BUFFER_SIZE = 4096;

	NCTCPConnection();
	virtual ~NCTCPConnection();
		
	int read(NCByteArray& read_buffer);
	int write(NCByteArray& write_buffer);
	int close();

protected:
	int connection_descriptor_;
	friend class NCTCPServer;
	friend class NCTCPClient;
};

#endif
