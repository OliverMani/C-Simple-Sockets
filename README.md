# C-Simple-Sockets

C++ code that makes socket connections easier...

## Examples

### Server
```c++
int main(){
	ServerSocket server(12345);

	Socket sock = server.accept();
	SocketStream stream(&sock);

	string from_client = stream.read_string();
	cout << from_client << endl;

	stream.send_string("Hello from server :)");

	server.close();
}
```


### Client
```c++
int main(){
	Socket* sock("localhost", 12345);
	SocketStream stream(sock);
	stream.send_string("Hello from client!!");
	string response = stream.read_string();
	cout << response << endl;
	sock.close();
}
```
