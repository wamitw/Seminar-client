#include <iostream>
#include "MySocket.h"

using namespace std;

static void help(void) {
	cout << "RemotePy - A Program to Run Python Commands From Remote" << endl << endl;
	cout << "Options:" << endl;
	cout << "--help \t\t show brief help" << endl;
	cout << "-h \t\t specify an ip to connect to" << endl;
	cout << "-p \t\t specify a port (default - 8080)" << endl;
	cout << endl;
	cout << "Example: -h 127.0.0.1 -p 8080" << endl;
}


int main (int argc, char **argv) {
	int port;
	string host;
	char c;
	string arguments, command, ans;

	if (argc < 2) {
		cout << "missing arguments. run --help for help.\n";
		return 1;
	}

	arguments = "";
	for (int i = 1; i < argc; i++) {
		arguments += argv[i];
		arguments += " ";
	}


	help();

	command = "";
	cout << ">>> ";
	while(cin.get(c)) {
		if(c == '\n')
			cout << "\n" << ">>> ";
		else
			cout << c;
		command += c;
	}

	cout << "\n\n" << "Command is:" << "\n" << command;

	host = "127.0.0.1";
	port = 8080;

	MySocket s(host, port);
	s.conn();
	s.sendMsg(command);
	ans = s.getMsg();
	cout << "Answer Received!" << "\n" << ans;

	return 0;
}
