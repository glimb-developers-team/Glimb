/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
*/

#ifdef REQUEST_FORMATION.H
#define REQUEST_FORMATION.H

/*
* This file describes class RequestFormation,
* which helps to generate and parse JSON requests.
*/

#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include <cstdio>
#include <string>
#include <iostream>
#include "ServerConnector.cpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "requests.h"
#include <stdexcept>

class RequestFormation {
private:
    const std::string _req;
	  const std::string _name;
	  const std::string _last_name;
	  const std::string _middle_name;
    const std::string _number;
	  const std::string _password;
	  const std::string _type;
	  const std::string _foreman_number;

public:
    ~RequestFormation();

		RequestFormation(const std::string& name, const std::string& last_name,
     const std::string& middle_name, const std::string& number, const std::string& password,
		  const std::string& type, const std::string& foreman_number);

    /*
    *to_json() - generate JSON request by rapidjson.
    *This method should not called manually.
    *It uses in another methods - to_enter() and to_register()(future method).
    */
		rapidjson::Document to_json();

    /*
    *serialize() - make JSON request more suitable and useful
    *for working with server.
    *This method is nessesary in process of formation request.
    */
		template <typename Writer>
    void serialize(Writer& writer) const;

    /*
    *to_enter() - enter to user's account
    */
		void to_enter(RequestFormation& sx);

};

#endif // RE
