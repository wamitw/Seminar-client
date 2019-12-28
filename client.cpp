#include <iostream>
#include "MySocket.h"

using namespace std;

int main (int argc, char **argv) {

	int port;
	string host;
	if (argc < 2) {
		cout << "missing arguments. run --help for help.\n";
		return 1;
	}

	host = "127.0.0.1";
	port = 8080;

	MySocket s(host, port);
	s.conn();
	s.sendMsg(command);
	ans = s.getMsg();
	cout << "Answer Received!" << "\n" << ans;

	return 0;
}
