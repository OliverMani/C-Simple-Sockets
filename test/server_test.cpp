#include "../sokkar/client.h"
#include "../sokkar/server.h"
#include "../sokkar/stream/basic.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(){
	ServerSocket server(12345);

	Socket* sock = server.accept();
	SocketStream stream(sock);

	string from_client = stream.read_string();
	cout << from_client << endl;

	stream.send_string("Hello from server :)");

	server.close();
}