/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
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
//#include "RequestFormation.h"

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
		~RequestFormation() {

    }

		RequestFormation(const std::string& name, const std::string& last_name,
     const std::string& middle_name, const std::string& number, const std::string& password,
		  const std::string& type, const std::string& foreman_number) : _name(name), _last_name(last_name),
			 _middle_name(middle_name), _number(number), _password(password), _type(type), _foreman_number(foreman_number) { };

/*
*to_json() - generate JSON request by rapidjson.
*This method should not called manually.
*It uses in another methods - to_enter() and to_register()(future method).
*/
		rapidjson::Document to_json() {
				rapidjson::Value info_val, tmp;
        rapidjson::Document document;
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

			 	document.SetObject();
			 	document.AddMember("request", REQUEST_REGISTRATION, allocator);
       	info_val.SetObject();
			 	tmp.SetString(rapidjson::StringRef(_name.c_str()));
       	info_val.AddMember("name", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_last_name.c_str()));
       	info_val.AddMember("last_name", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_middle_name.c_str()));
       	info_val.AddMember("middle_name", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_number.c_str()));
       	info_val.AddMember("number", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_password.c_str()));
       	info_val.AddMember("password", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_type.c_str()));
       	info_val.AddMember("type", tmp, allocator);
			 	tmp.SetString(rapidjson::StringRef(_foreman_number.c_str()));
       	info_val.AddMember("foreman_number", tmp, allocator);
			 	document.AddMember("info", info_val, allocator);
       	return document;
		}

/*
*serialize() - make JSON request more suitable and useful
*for working with server.
*This method is nessesary in process of formation request.
*/
		template <typename Writer>
		void serialize(Writer& writer) const {
		writer.String("name");
		#if RAPIDJSON_HAS_STDSTRING
		writer.String(_name);
		writer.String(_last_name);
		writer.String(_middle_name);
		writer.String(_number);
		writer.String(_password);
		writer.String(_type);
		writer.String(_foreman_number);
		#else
		writer.String(_name.c_str(), static_cast<rapidjson::SizeType>(_name.length()));
		writer.String(_last_name.c_str(), static_cast<rapidjson::SizeType>(_last_name.length()));
		writer.String(_middle_name.c_str(), static_cast<rapidjson::SizeType>(_middle_name.length()));
		writer.String(_number.c_str(), static_cast<rapidjson::SizeType>(_number.length()));
		writer.String(_password.c_str(), static_cast<rapidjson::SizeType>(_password.length()));
		writer.String(_type.c_str(), static_cast<rapidjson::SizeType>(_type.length()));
		writer.String(_foreman_number.c_str(), static_cast<rapidjson::SizeType>(_foreman_number.length()));
		#endif
		}

/*
*to_enter() - enter to user's account
*/
		void to_enter(RequestFormation& sx) {
			try {
				/*First step: accept full data from user, generate it to JSON request
				*and send to the server.*/
				rapidjson::Document document = sx.to_json();
		  	rapidjson::StringBuffer buffer;
		  	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		  	document.Accept(writer);
		  	const std::string& str = buffer.GetString();
		  	std::cout << "Serialized:" << std::endl;
		  	std::cout << str << std::endl;
				ServerConnector sc = ServerConnector();
				std::cout << "HI" << std::endl;
				sc.to_connect("192.168.43.33", 4512);

				/*Second step: accept answer from server, parse and trancfer to user.*/
				std::string doc = sc.request(str);
				rapidjson::Document qwe;
				qwe.Parse(doc.c_str());
				std::string _type_ = qwe["type"].GetString();
				if (_type_ == "ok")
						return ;
				else
						throw (const char*)qwe["info"]["description"].GetString();
		  	//std::cout << "Answer:" << std::endl;
				//std::cout << _document_ << std::endl;
			}
			catch (const char *error) {
				std::cout << error << std::endl;
			}



		}
};
