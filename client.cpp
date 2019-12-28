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

	if ((index = arguments.find('-')) == string::npos) {
		cout << "missing arguments. run --help for help." << endl;
		return 1;
	}

	while (index != string::npos) {
		next = arguments.find('-', index + 1);
		/* --argument Case */
		if (next == index + 1) {
			index = next;
			next = arguments.find('-', index + 1);
		}

		argument = substring(arguments, index, next);

		space = argument.find(' ');
		perfix = substring(argument, 1, space);
		suffix = substring(argument, space + 1, 0);

		if (perfix.compare("help") == 0) {
			help();
			return 1;
		} else if (perfix.compare("h") == 0) {
			cout << "got host: " << suffix << endl;

			if (suffix.empty()) {
				cout << "but host is already defined. run --help for help."
						<< endl;
				return 1;
			}

			host = suffix;
			trim(host);

			if (!regex_match(host, match, ip)) {
				cout << "but host isn't in IP format." << endl;
				return 1;
			}

			int length = match.size();
			for (int i=1; i < length; i++) {
				int part = stoi(match.str(i));
				if (part > 255) {
					cout << "but part of the host(" << part << ") is invalid" << endl;
					return 1;
				}
			}

		} else if (perfix.compare("p") == 0) {

			cout << "got port: " << suffix << endl;

			if (port != -1) {
				cout << "but port is already defined. run --help for help."
						<< endl;
				return 1;
			}

			try {
				port = stoi(suffix);
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

		} else {
			cout << "arguments error. run --help for help." << endl;
			return 1;
		}

		index = next;
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
	ans = s.getMsg();
	cout << "Answer Received!" << endl << ans;

	return 0;
}
