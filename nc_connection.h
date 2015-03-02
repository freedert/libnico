#ifndef	NC_CONNECTION_H_
#define	NC_CONNECTION_H_

#include	<stdint.h>
#include	<vector>

typedef	std::vector<uint8_t>	NCByteArray;

class NCConnection {
public:
	virtual int read(NCByteArray& read_buffer) = 0;
	virtual int write(NCByteArray& write_buffer) = 0;
	virtual int close() = 0;
};	

#endif	// NC_CONNECTION_H_

