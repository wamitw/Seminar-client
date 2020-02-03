/*
 * socket.h
 *
 *  Created on: 11 Oct 2019
 *      Author: amit
 */

#ifndef MYSOCKET_H_
#define MYSOCKET_H_

#include <arpa/inet.h>
#include <string>

class MySocket {
private:
	std::string host;
	int fd, port;
	struct sockaddr_in serv_addr;

public:
	MySocket(std::string, int);
	int conn(void);
	int sendMsg(std::string);
	int getMsg(std::string &);
};

#endif /* MYSOCKET_H_ */
