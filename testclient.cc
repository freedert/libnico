#include	<string>

#include	"nc_tcp_client.h"

int main(int argc, char** argv)
{
	NCTCPClient client;
	std::string teststring = "TEST Message";
	NCByteArray buffer( teststring.begin(), teststring.end());
	int wrote = 0;

	client.open("localhost", 8080);

	wrote = client.write(buffer);


	printf("wrote: [%s](%d)\n", teststring.c_str(), wrote);

	client.close();

	return 0;
}
