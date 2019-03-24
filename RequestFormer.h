/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
*/

#ifndef REQUEST_FORMER_H
#define REQUEST_FORMER_H

#include "rapidjson/document.h"
#include <string>
#include "rapidjson/writer.h"
#include "ServerConnector.h"
#include "LogPrinter.h"

class RequestFormer {
private:
	std::string _name;
	std::string _last_name;
	std::string _middle_name;
	std::string _number;
	std::string _password;
	std::string _type;
	std::string _foreman_number;
	static ServerConnector _sc;

	/*
	*set_new_user() - need for more comfortable using in registration process.
	*/
	void set_new_user(std::string& name, std::string& last_name,
		std::string& middle_name, std::string& number,
		std::string& password, std::string& type, std::string& foreman_number);

	/*
	*enter_old_user() - need for more comfortable using in entrance process.
	*/
	void enter_old_user(std::string& number, std::string& password);

	/*
	*to_json() - generate JSON request by rapidjson.
	*It uses in another methods - to_enter() and to_register().
	*/
	rapidjson::Document to_json(std::string request);

	/*
	*serialize() - make JSON request more suitable and useful for working with server.
	*This method is nessesary in process of formation request.
	*/
	template <typename Writer>
	void serialize(Writer& writer) const;

public:
	RequestFormer();

	~RequestFormer();

	static void connect_to_server();

	static void disconnect();

	/*
	*to_register() - register a new user's account.
	*It's first function which you need.
	*Method returns "1", if user exists and his data is right.
	*Else method returns error tied with server or user.
	*Can throw "Such user already exists", "Password is too short" or
	*"Number of foreman is not right" of type const char *.
	*/
	static std::string to_register(std::string name, std::string last_name, std::string middle_name,
		std::string number, std::string password, std::string type,
		std::string foreman_number);

	/*
	*to_enter() - enter to user's account. It's second function which you need.
	*Method returns "1", if user exists and his data is right.
	*Else method returns error tied with server or user.
	*Can throw "User does not exist" or "Password is failed" of type const char *.
	*/
	static std::string to_enter(std::string number, std::string password);

};

#endif // REQUEST_FORMER_H
