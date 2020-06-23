#include "../sokkar/client.h"
#include "../sokkar/server.h"
#include "../sokkar/stream/basic.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(){
	printf("??\n");
	ServerSocket server(7070);
	printf("??\n");
	Socket* sock = server.accept();
	if(sock == nullptr){
		printf("Connection failed!\n");
		return 0;
	}
	
	SocketStream stream(sock);
	stream.send_string("Hello client!!!");
	string from_client = stream.read_string();
	cout << "From client: " << from_client << endl;

	unsigned long i = (unsigned long) stream.read_long();

	cout << "Int from client: " << i << endl;
	
}