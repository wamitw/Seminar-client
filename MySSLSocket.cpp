/*
 * socket.cpp
 *
 *  Created on: 11 Oct 2019
 *      Author: amit
 */

#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "MySocket.h"
#include "MySSLSocket.h"

using namespace std;

static SSL_CTX* InitCTX(void)
{
    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

/* Public */

MySSLSocket::MySSLSocket(string host, uint16_t port) : MySocket::MySocket(host, port) {
	SSL_library_init();
}

int MySSLSocket::conn(void) {
	int res;

	res = MySocket::conn();
	if (res) {
		cout << "Error establishing regular connection" << endl;
		return res;
	}

    ctx = InitCTX();
    ssl = SSL_new(ctx);				/* create new SSL connection state */
    SSL_set_fd(ssl, this->fd);		/* attach the socket descriptor */
	res = SSL_connect(ssl);			/* perform the connection */
    if (res != SSL_CLIENT_HELLO_SUCCESS) {
		ERR_print_errors_fp(stderr);
		return res;
	}

	/* TODO: Verify Certificate */

	return 0;
}

int MySSLSocket::sendMsg(string msg) {
	int res;
	const char *msg_in_bytes;

	msg_in_bytes = msg.c_str();
	res = SSL_write(ssl, msg_in_bytes, static_cast<int>(msg.length()));   /* encrypt & send message */
	if (res < 0) {
		perror("Error sending message");
		return res;
	}

	cout << "Message sent" << "\n";
	return 0;
}

int MySSLSocket::getMsg(std::string &msg) {
	int status;
	char buffer[BUFFER_SIZE];
	msg = "";

	while ((status = SSL_read(ssl, buffer, BUFFER_SIZE)) > 0)
		msg += buffer;

	if (status < 0) {
		perror ("Error getting message");
		return status;
	}

	return 0;
}

MySSLSocket::~MySSLSocket(void) {
	SSL_free(ssl);
	close(fd);
	SSL_CTX_free(ctx);
}