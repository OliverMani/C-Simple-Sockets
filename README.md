# C-Simple-Sockets

C++ code that makes socket connections easier...

## Examples

### Client
```c++
int main(){
	Socket sock("example.com", 80);
	SocketStream stream(&sock);
	stream.send_string("GET / HTTP/1.1\r\nHOST: example.com\r\n\r\n");
	string response = stream.read_string();
	cout << response << endl;
	sock.close();
}
```
