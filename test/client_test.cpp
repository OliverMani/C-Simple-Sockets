#include "../sokkar/client.h"
#include "../sokkar/stream/basic.h"
#include <iostream>
#include <stdio.h>

using namespace std;



int main(){
	/*Socket sock("0.0.0.0", 7070);
	string message = "hello server";
	
	SocketStream stream(&sock);

	string from_server = stream.read_string();

	cout << "From server: " << from_server << endl;

	sock.send((char*) message.c_str(), message.length());
	stream.send_long(123456);
	sock.close();*/

	string host = "olivermani.com";

	Socket ping(host, 25565);
	SocketStream stream(&ping);

	stream.append_short(0xFEFD);
	stream.append_byte(0x09);
	stream.append_int(0x00000001);
	//stream.append_int(0x0091295B);


	stream.flush();

	string response = stream.read_string();

	cout << response << endl;

	ping.close();
}