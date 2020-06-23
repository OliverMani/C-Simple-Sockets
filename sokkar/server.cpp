#include "server.h"
#include <iostream>

ServerSocket::ServerSocket(int port) {
	this->port = port;
	this->closed = false;
	this->opt = 1;
	this->addrlen = sizeof(this->address);
	for(int i; 0 <-- i;)
		this->buffer[i] = 0;

	if((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		cout << "socket failed!\n";
		return;
	}

	if(setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                              &this->opt, sizeof(this->opt))) {
		cout << "setsockopt failed!\n";
		
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);

	if(bind(server_fd, (struct sockaddr*)&address, this->addrlen) < 0) {
		cout << "bind failed\n";
		return;
	}

	if(listen(server_fd, 3) < 0) {
		cout << "listen failed\n";
		return;
	}
}

Socket* ServerSocket::accept(){

	int new_socket = ::accept(this->server_fd, (struct sockaddr *)&this->address, (socklen_t*)&this->addrlen);
	if(new_socket < 0)
		return nullptr;
	return new Socket(new_socket);
}

bool ServerSocket::is_closed() {
	return this->closed;
}

void ServerSocket::close(){
	if(this->closed)
		return;
	this->closed = true;
	::close(this->server_fd);
}

int ServerSocket::get_port(){
	return this->port;
}

/*
int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
char *hello = "Hello from server"; 
   
// Creating socket file descriptor 
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
{ 
    perror("socket failed"); 
    exit(EXIT_FAILURE); 
} 
   
// Forcefully attaching socket to the port 8080 
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                              &opt, sizeof(opt))) 
{ 
    perror("setsockopt"); 
    exit(EXIT_FAILURE); 
} 
address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons( PORT ); 
   
// Forcefully attaching socket to the port 8080 
if (bind(server_fd, (struct sockaddr *)&address,  
                             sizeof(address))<0) 
{ 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
} 
if (listen(server_fd, 3) < 0) 
{ 
    perror("listen"); 
    exit(EXIT_FAILURE); 
} 
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                   (socklen_t*)&addrlen))<0) 
{ 
    perror("accept"); 
    exit(EXIT_FAILURE); 
} 
valread = read( new_socket , buffer, 1024); 
printf("%s\n",buffer ); 
send(new_socket , hello , strlen(hello) , 0 ); 
printf("Hello message sent\n"); 
*/