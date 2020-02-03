#include <iostream>
#include <regex>
#include "MySocket.h"

#define MAX_PORT		(65535)

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

static void misuse(void) {
	cout << "Invalid arguments. Run --help for help." << endl;
}

int main (int argc, char **argv) {

	int part, port = -1;
	string host;
	bool port_expected, host_expected, arg_expected;
	string arg, line, command, ans;

	smatch match;
	regex ip("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})");

	if (argc < 2) {
		misuse();
		return 1;
	}

	arg_expected = true;
	for (int i = 1; i < argc; i++) {
		arg = argv[i];

		if (arg.compare("--help") == 0) {
			help();
			return 0;
		}

		if (arg.compare("-p") == 0 || arg.compare("-h") == 0) {
			if (!arg_expected) {
				misuse();
				return 1;
			}
			arg_expected = false;
			port_expected = (arg.compare("-p") == 0 && port == -1);
			host_expected = (arg.compare("-h") == 0 && host.empty());
		} else if (arg_expected) {
			misuse();
			return 1;
		} else if (port_expected) {
			cout << "got port: " << arg << endl;

			try {
				port = stoi(arg);
			} catch (invalid_argument& e) {
				cout << "but port isn't a number. run --help for help." << endl;
				return 1;
			} catch (out_of_range& e) {
				cout << "but port isn't an allowed number (1-" << MAX_PORT
						<< "). run --help for help." << endl;
				return 1;
			}

			if (port > MAX_PORT || port <= 0) {
				cout << "but port isn't an allowed number (1-" << MAX_PORT
						<< "). run --help for help." << endl;
				return 1;
			}
			port_expected = false;
			arg_expected = true;
		} else if (host_expected) {
			cout << "got host: " << arg << endl;

			host = arg;

			if (!regex_match(host, match, ip)) {
				cout << "but host isn't in IP format." << endl;
				return 1;
			}

			for (uint i=1; i < match.size(); i++) {
				part = stoi(match.str(i));
				if (part > 255) {
					cout << "but part of the host(" << part << ") is invalid" << endl;
					return 1;
				}
			}
			host_expected = false;
			arg_expected = true;
		} else {
			misuse();
			return 1;
		}
	}

	command = "";
	cout << ">>> ";
	while (getline(cin, line)) {
		command += line + "\n";
		cout << ">>> ";
	}

	cout << endl << endl << "Command is:" << endl << command;

	MySocket s(host, port);
	cout << "Starting connection..." << endl;
	s.conn();

	cout << "Connection Established!" << endl << "Sending Message..." << endl;
	s.sendMsg(command);
	cout << "Waiting for response..." << endl;
	if(s.getMsg(ans))
		cout << "Answer Received!" << endl << ans;
	else
		cout << "Error getting message!" << endl;

	return 0;
}
