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

#define	BUFFER_SIZE				(1024)

class MySocket {
protected:
	std::string host;
	int fd;
	uint16_t port;
	struct sockaddr_in serv_addr;

public:
	MySocket(std::string host, uint16_t port);
	int conn(void);
	size_t sendMsg(std::string);
	int getMsg(std::string &);
	~MySocket(void);
};

#endif /* MYSOCKET_H_ */
