#include "client.h"
#include <iostream>

char* Socket::get_ip_of_domain(char* domain) {
	struct hostent *he;
	he = gethostbyname(domain);
	if(he == NULL)
		return nullptr;
	return strdup(inet_ntoa(*((struct in_addr *) he->h_addr_list[0])));
}

bool Socket::__connect() {
	if((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Socket creation error!\n";
		return 0;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);

	bool tried_domain = 0;

	while(inet_pton(AF_INET, (char*)this->address.c_str(), &serv_addr.sin_addr)<=0)  
    {
    	if(tried_domain) {
    		cout << "Invalid address!\n";
    	}
    	char* cstr = (char*)this->address.c_str();
    	char* addr = this->get_ip_of_domain(cstr);
    	if(addr == nullptr) {
    		cout << "Invalid address!\n";
        	return 0; 
    	}

    	this->address = string(addr);

    	//cout << "Address: " << this->address << endl;

    	tried_domain = 1;

        
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        cout << "Connection Failed \n"; 
        return 0; 
    } 
    this->connected = true;
    this->bytes_read = 0;

	return 1;
}



void Socket::close() {
	if(this->connected){
		this->connected = false;
		::close(this->sock);
	}
}

void Socket::send(char* buffer, int size) {
	if(this->connected)
		::send(this->sock, buffer, size, 0);
}

int Socket::read(char* buffer, int size) {
	if(this->connected)
		return ::read(sock, buffer, size);
	return -2;
}

/**

// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 

} 
*/