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

static string substring(string str, size_t from, size_t to) {
	if (from >= str.length())
		return "";
	if (from > to)
		to = str.length();
	return str.substr(from, to - from);
}

int main (int argc, char **argv) {
	int port;
	string host;
	char c;
	string arguments, command, ans;

	if (argc < 2) {
		cout << "missing arguments. run --help for help." << endl;
		return 1;
	}

	arguments = "";
	for (int i = 1; i < argc; i++) {
		arguments += argv[i];
		arguments += " ";
	}



	command = "";
	cout << ">>> ";
	while (getline(cin, line)) {
		command += line + "\n";
		cout << ">>> ";
	}


	host = "127.0.0.1";
	port = 8080;
	cout << endl << endl << "Command is:" << endl << command;

	MySocket s(host, port);
	cout << "Starting connection..." << endl;
	s.conn();

	cout << "Connection Established!" << endl << "Sending Message..." << endl;
	s.sendMsg(command);
	ans = s.getMsg();
	cout << "Answer Received!" << endl << ans;

	return 0;
}
