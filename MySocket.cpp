/*
 * socket.cpp
 *
 *  Created on: 11 Oct 2019
 *      Author: amit
 */

#include <string>
#include "MySocket.h"

using namespace std;

MySocket::MySocket(string host, int port) {
	this->host = host;
	this->port = port;
	this->fd = -1;
}
