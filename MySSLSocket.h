/*
 * socket.h
 *
 *  Created on: 11 Oct 2019
 *      Author: amit
 */

#ifndef _MYSSLSOCKET_H_
#define _MYSSLSOCKET_H_

#include <openssl/ssl.h>
#include "MySocket.h"

class MySSLSocket : MySocket {
private:
	SSL *ssl;
	SSL_CTX *ctx;

public:
	MySSLSocket(std::string host, uint16_t port);
	int conn(void);
	int sendMsg(std::string);
	int getMsg(std::string &);
};

#endif /* _MYSSLSOCKET_H_ */
