#include "../sokkar/client.h"
#include "../sokkar/stream/basic.h"
#include <iostream>
#include <stdio.h>

using namespace std;



int main(){
	Socket sock("localhost", 12345); // Connect to example.com, the website
	SocketStream stream(&sock);
	stream.send_string("Hello from client!!");
	string response = stream.read_string();
	cout << response << endl;
	sock.close();
}