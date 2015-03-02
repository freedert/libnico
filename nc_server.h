#ifndef	NC_SERVER_H_
#define	NC_SERVER_H_

class NCConnection;

class NCServer {
public:
	virtual void open(int port) = 0;
	virtual NCConnection& waitForConnection() = 0;
	virtual void close() = 0;
};


#endif	// NC_SERVER_H_
