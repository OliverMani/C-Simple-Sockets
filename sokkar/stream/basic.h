#pragma once
#include "../client.h"
#include <string>

using namespace std;

class SocketStream {
private:
	Socket* sock;
	char* buffer;
	short buff_i;
	int buffer_size;
public:
	SocketStream(Socket* sock, int buffer_size){
		this->sock = sock;
		this->buffer_size = buffer_size;
		this->buffer = new char[buffer_size];
		this->buff_i = 0;
		this->reset_buffer();
	}

	SocketStream(Socket* sock) {
		this->sock = sock;
		this->buffer_size = 1024;
		this->buffer = new char[buffer_size];
		this->buff_i = 0;
		this->reset_buffer();
	}

	~SocketStream(){
		delete [] this->buffer;
	}

	char read_byte();
	short read_short();
	int read_int();
	long read_long();
	string read_string();

	void send_byte(char ch);
	void send_short(short sh);
	void send_int(int i);
	void send_long(long l);
	void send_string(string str);
	void send_data(char* buffer, int len);

	void flush();
	void reset_buffer();

	void append_byte(char ch);
	void append_short(short sh);
	void append_int(int i);
	void append_long(long l);
	void append_string(string str);
	void append_data(char* buffer, int len);


};