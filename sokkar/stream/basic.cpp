#include "basic.h"

#include <iostream>
#include <stdio.h>

char SocketStream::read_byte() {
	char tmp_buf[1];
	this->sock->read(tmp_buf, 1);
	return tmp_buf[0];
}

short SocketStream::read_short() {
	char tmp_buf[2];
	this->sock->read(tmp_buf, 2);

	return (tmp_buf[1] << 8) | tmp_buf[0];

}

int SocketStream::read_int() {
	char tmp_buf[4];
	this->sock->read(tmp_buf, 4);

	unsigned int res = 0;

	for(int i = 0; i < 4; i++) {
		
		res |= ((tmp_buf[i] & 0xff) << (i * 8));
	}

	return (int)res;
}

long SocketStream::read_long() {
	char tmp_buf[8];
	this->sock->read(tmp_buf, 8);

	unsigned long res = 0;

	for(int i = 0; i < 8; i++) {
		
		res |= ((tmp_buf[i] & 0xff) << (i * 8));
	}

	return (long)res;
}

string SocketStream::read_string() {
	const int chunk_size = 1024;
	char buffer[chunk_size];
	string str = "";
	int bytes_read = 0, read = 0;
	
	do {
		for(int i = 0; i < chunk_size; i++)
			buffer[i] = 0;
		read = this->sock->read(buffer, chunk_size);
		bytes_read += read;
		if(read < 0){
			cout << "Error!";
			break;
		}

		bool end = false;
		for(int i = 0; i < read; i++){
			if(!buffer[i])
				end = true;
		}

		str += string(buffer);

		if(read < chunk_size)
			break;
		

	} while(read);



	return str;
}


void SocketStream::send_byte(char ch) {
	char tmp_buf[1] = {ch};
	this->sock->send(tmp_buf, 1);
}

void SocketStream::send_short(short sh) {
	char tmp_buf[2];
	for(int i = 0; i < 2; i++) {
		char tmp = (sh >> 8 * i) & 255;
		tmp_buf[i] = tmp;
	}
	this->sock->send(tmp_buf, 2);
}

void SocketStream::send_int(int j) {
	char tmp_buf[4];
	for(int i = 0; i < 4; i++) {
		char tmp = (j >> 8 * i) & 255;
		tmp_buf[i] = tmp;
	}
	this->sock->send(tmp_buf, 4);
}

void SocketStream::send_long(long l) {
	char tmp_buf[8];
	for(int i = 0; i < 8; i++) {
		char tmp = (l >> 8 * i) & 255;
		tmp_buf[i] = tmp;
	}
	this->sock->send(tmp_buf, 8);
}

void SocketStream::send_string(string str) {
	unsigned int length = str.length();
	this->sock->send((char*)str.c_str(), length);
}


void SocketStream::flush() {
	this->sock->send(this->buffer, this->buff_i);
	this->reset_buffer();
}

void SocketStream::reset_buffer() {
	for(int i = 0; i < 1024; i++) {
		this->buffer[i] = 0;
	}
	this->buff_i = 0;
}


void SocketStream::append_byte(char ch) {
	this->buffer[this->buff_i++] = ch;
}

void SocketStream::append_short(short sh) {
	for(int i = 0; i < 2; i++) {
		char tmp = (sh >> 8 * i) & 255;
		this->buffer[this->buff_i + i] = tmp;
	}
	this->buff_i += 2;
}

void SocketStream::append_int(int j) {
	for(int i = 0; i < 4; i++) {
		char tmp = (j >> 8 * i) & 255;
		this->buffer[this->buff_i + i] = tmp;
	}
	this->buff_i += 4;
}

void SocketStream::append_long(long l) {
	for(int i = 0; i < 8; i++) {
		char tmp = (l >> 8 * i) & 255;
		this->buffer[this->buff_i + i] = tmp;
	}
	this->buff_i += 8;
}

void SocketStream::append_string(string str) {
	int len = str.length();
	for(int i = 0; i < len; i++) {
		this->buffer[this->buff_i + i] = str[i];
	}
	this->buff_i += len + 1;
}

void SocketStream::append_data(char* buffer, int len) {
	for(int i = 0; i < len; i++) {
		this->buffer[this->buff_i + i] = buffer[i];
	}
	this->buff_i += len;
}
