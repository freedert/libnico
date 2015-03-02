#include	"nc_tcp_connection.h"

#include	<stdio.h>
#include	<unistd.h>

NCTCPConnection::NCTCPConnection()
{
	// Nothing to do	
}

NCTCPConnection::~NCTCPConnection()
{
	this->close();
}
		
int NCTCPConnection::read(NCByteArray& read_buffer)
{
	uint8_t	read_buffer_array[BUFFER_SIZE] = {0};
	int receive_size = ::read(connection_descriptor_,
				read_buffer_array,
				sizeof(read_buffer_array));

	if (receive_size == -1) {
		perror("read");
		this->close(); 
		return 0;
	}

	NCByteArray buffer_array(read_buffer_array, read_buffer_array + BUFFER_SIZE);
	read_buffer.insert(read_buffer.end(), buffer_array.begin(), buffer_array.end());
	
	return receive_size;	
}

int NCTCPConnection::write(NCByteArray& write_buffer)
{
	uint8_t	write_buffer_array[BUFFER_SIZE] = {0};
	int send_size = 0;

	NCByteArray::iterator itr = write_buffer.begin();

	do {
		int buffer_count = 0;

		// バッファにコピー出来る分だけコピー
		while ((itr != write_buffer.end()) && (buffer_count < BUFFER_SIZE)) {
			write_buffer_array[buffer_count] = *itr;

			++buffer_count;
			++itr;
		}

		send_size += ::write(connection_descriptor_,
					write_buffer_array,
					buffer_count );	

	} while (itr != write_buffer.end());

	return send_size;
}

int NCTCPConnection::close()
{
	return ::close(connection_descriptor_);
}
