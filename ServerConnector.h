/*
* Polyakov Daniil
* Mail: arjentix@gmail.com
* Github: Arjentix
* Date: 09.03.19
*/

#ifndef SERVER_CONNECTOR_H
#define SERVER_CONNECTOR_H

#include <string>

/*
* This file describes class ServerConnector,
* which helps to connect and send requests to the server.
*/

class ServerConnector {
private:
	bool _connected;
	int _sockfd;

public:
	ServerConnector();
	~ServerConnector();

	/*
	* to_connect() - connects to the server with address and port passed by arguments.
	* This method should be called before all another methods.
	* Can thow "Can not connect to the server" of type const char *.
	*/
	void to_connect(std::string address, int port);

	/*
	* close_connection() - closes socket and connection between this program and server.
	*/
	void close_connection();

	/*
	* is_connected() - returns true if connection is established and false if not.
	*/
	bool is_connected();

	/*
	* request() - sends a request to the server and returns an answer.
	* request and asnwer should be in json format.
	* Can throw "No connection to the server", "Failed to send request to the server",
	* "Failed to receive answer from the server" of type const char *.
	*/
	std::string request(std::string request);
};

#endif // SERVER_CONNECTOR_H
