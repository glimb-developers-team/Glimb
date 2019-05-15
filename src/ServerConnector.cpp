/*
* Polyakov Daniil
* Mail: arjentix@gmail.com
* Github: Arjentix
* Date: 09.03.19
*/

/*
* This file defines methods of class ServerConnector, which is described in ServerConnector.h
* See all methods description in the header file.
*/

#include <iostream>
#include "ServerConnector.h"
#include "requests.h"
#ifdef __unix__
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>

	#define SOCK int
	#define SOCKET_ERROR -1

	void sock_init()
	{
		return;
	}

	void sock_close(int sock)
	{
		close(sock);
	}
#elif defined _WIN32
	#include <WS2tcpip.h>

	#define SOCK SOCKET

    void sock_init()
	{
		// Initializing WinSock
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0) {
			throw "Failed to initialize WinSock";
		}
	}

	void sock_close(SOCKET s)
	{
		closesocket(s);
		WSACleanup();
	}
#endif

ServerConnector::ServerConnector() : _connected(false)
{
    sock_init();
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);

#ifdef __unix__
	if(_sockfd < 0) {
#elif defined _WIN32
    if(_sockfd == INVALID_SOCKET) {
#endif
        throw "Can't establish socket";
	}
}

ServerConnector::~ServerConnector()
{
	close_connection();
}

void ServerConnector::to_connect(std::string address, int port)
{
	/* Initialization */
	struct sockaddr_in socket_address;
	int result;

	/* Setting address */
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(address.c_str());
	socket_address.sin_port = htons(port);

	/* Connecting */
	result = connect(_sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address));
    if (result == SOCKET_ERROR) {
		throw "Failed to connect to the server";
	}

	_connected = true;
}

void ServerConnector::close_connection()
{
	if (!_connected) {
		return;
	}
    sock_close(_sockfd);
	_connected = false;
}

bool ServerConnector::is_connected()
{
	return _connected;
}

std::string ServerConnector::request(std::string request)
{
	if (_connected == false) {
		throw "No connection to the server";
	}

	/* Initialization */
	char buffer[BUFFER_SIZE];
	int result;

	/* Sending request to the server */
	snprintf(buffer, BUFFER_SIZE, "%s", request.c_str());
	result = send(_sockfd, buffer, BUFFER_SIZE, 0);
	if (result < 0) {
		throw "Failed to send request to the server";
	}

	/* Receiving answer form the server */
	result = recv(_sockfd, buffer, BUFFER_SIZE, 0);
	if (result <= 0) {
		throw "Failed to receive answer from the server";
	}

	return buffer;
}

void ServerConnector::simple_request(std::string request)
{
	if (_connected == false) {
		throw "No connection to the server";
	}

	/* Initialization */
	char buffer[BUFFER_SIZE];
	int result;

	/* Sending request to the server */
	snprintf(buffer, BUFFER_SIZE, "%s", request.c_str());
	result = send(_sockfd, buffer, BUFFER_SIZE, 0);
	if (result < 0) {
		throw "Failed to send request to the server";
	}
}

std::string ServerConnector::get_next_answer()
{
	if (_connected == false) {
		throw "No connection to the server";
	}

	/* Initialization */
	char buffer[BUFFER_SIZE];
	int result;

	/* Receiving answer from the server */
	result = recv(_sockfd, buffer, BUFFER_SIZE, 0);
	if (result <= 0) {
		throw "Failed to receive answer from the server";
	}

	return buffer;
}
