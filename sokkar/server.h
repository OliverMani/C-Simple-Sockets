#pragma once
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include "client.h"

class ServerSocket {
private:
	int port;
	bool closed;

	int server_fd, valread;
	struct sockaddr_in address;
	int opt;
	int addrlen;
	char buffer[1024];

public:
	ServerSocket(int);

	~ServerSocket(){
		this->close();
	}

	Socket* accept();
	int get_port();
	bool is_closed();
	void close();
};