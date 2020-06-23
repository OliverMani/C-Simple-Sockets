#pragma once
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <string>
#include <netdb.h>

using namespace std;

#define SIZE 4096

class Socket {
private:
	int sock, valread;
	struct sockaddr_in serv_addr;
	char buffer[SIZE];

	string address;
	int port;
	bool connected;

	int bytes_read;

	bool __connect();

	char* get_ip_of_domain(char*);
public:
	Socket(string address, int port) {
		for(int i = SIZE; 0 <-- i;)
			this->buffer[i] = 0;
		this->address = address;
		this->port = port;
		this->sock = 0;
		this->connected = false;

		if(!this->__connect()){
			printf("Connection failed!\n");
		}
	}

	Socket(int id) {
		for(int i = SIZE; 0 <-- i;)
			this->buffer[i] = 0;
		this->sock = id;
		this->connected = true;
	}

	~Socket(){
		this->close();
	}

	void close();
	void send(char*, int);
	int read(char*, int);
};