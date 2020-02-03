/*
 * socket.cpp
 *
 *  Created on: 11 Oct 2019
 *      Author: amit
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include "MySocket.h"

using namespace std;

MySocket::MySocket(string host, uint16_t port) {
	this->host = host;
	this->port = port;
	this->fd = -1;
}

int MySocket::conn(void) {
	int res;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cerr << __func__ << ": Error creating socket" << "\n";
		perror("");
		return fd;
	}

	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if ((res = inet_pton(AF_INET, host.c_str(), &this->serv_addr.sin_addr)) <= 0) {
		cerr << __func__ << ": Couldn't create socket to " << host << ":"
				<< port << "\n";
		perror("");
		return res;
	}

	if ((res = connect(fd, reinterpret_cast<const sockaddr *>(&serv_addr), sizeof(serv_addr))) < 0) {
		perror("Connection Failed");
		return res;
	}
	return 0;
}

size_t MySocket::sendMsg(string msg) {
	size_t res;

	if ((res = send(fd, msg.c_str(), msg.length(), 0)) == -1UL) {
		perror("Error sending message");
		return res;
	}

	cout << "Message sent" << "\n";
	return 0;
}

int MySocket::getMsg(std::string &msg) {

	size_t status, bytes = 1024;
	char *buffer = new char[bytes];
	msg = "";

	while ((status = read(fd, &buffer, bytes)) > 0)
		msg += buffer;

	if (status == -1UL) {
		perror ("Error getting message");
		return -1;
	}

	return 0;
}

