#include	<string>

#include	"nc_tcp_server.h"
#include	"nc_connection.h"

int main(int argc, char** argv)
{
	NCTCPServer srv;
	NCByteArray buffer;
	int readed = 0;

	srv.open(8080);

	NCConnection& connection = srv.waitForConnection();

	readed = connection.read(buffer);

	std::string bufstr(buffer.begin(), buffer.end());

	printf("received: [%s](%d)\n", bufstr.c_str(), readed);

	connection.close();

	srv.close();

	return 0;
}
