/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
*/

/*Ворзвращать ФИО(передача аргументов по ссылке), тип пользователя, static method, save answer to LogPrinter, warning of error in header of method, create an ServerConnection object in comstructor an destructor, info about server give from define*/

#define ADRESS "192.168.43.33"
#define PORT 4512

#include "RequestFormer.h"
#include "requests.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include <stdexcept>
#include <iostream>
#include <cstdio>
#include "ServerConnector.h"
//#include "LogPrinter"

RequestFormer::RequestFormer()
{
  _sc.to_connect(ADRESS, PORT);
}

RequestFormer::~RequestFormer()
{

}

void RequestFormer::set_new_user(std::string& name, std::string& last_name,
 std::string& middle_name, std::string& number, std::string& password,
  std::string& type, std::string& foreman_number)
{
	_name = name;
	_last_name = last_name;
	_middle_name = middle_name;
	_number = number;
	_password = password;
	_type = type;
	_foreman_number = foreman_number;
}

void RequestFormer::enter_old_user(std::string& number, std::string& password)
{
	_name = "";
	_last_name = "";
	_middle_name = "";
	_number = number;
	_password = password;
	_type = "";
	_foreman_number = "";
}

rapidjson::Document RequestFormer::to_json(std::string request)
{
	rapidjson::Value info_val, tmp;
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	if (request == REQUEST_REGISTRATION) {
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
	}
	else
	{
		document.SetObject();
		document.AddMember("request", REQUEST_LOGIN, allocator);
		info_val.SetObject();
		tmp.SetString(rapidjson::StringRef(_number.c_str()));
		info_val.AddMember("number", tmp, allocator);
		tmp.SetString(rapidjson::StringRef(_password.c_str()));
		info_val.AddMember("password", tmp, allocator);
		document.AddMember("info", info_val, allocator);
	}
	return document;
}

template <typename Writer>
void RequestFormer::serialize(Writer& writer) const
{
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

std::string RequestFormer::to_register(std::string name, std::string last_name,
 std::string middle_name, std::string number, std::string password,
  std::string type, std::string foreman_number)
{
	try {
		/*First step: accept full data from user, generate it to JSON request
		*and send to the server.*/
		RequestFormer sx;
    if (type == "foreman")
      foreman_number = "NULL";
    sx.set_new_user(name, last_name, middle_name, number, password, type, foreman_number);
		rapidjson::Document document = sx.to_json(REQUEST_REGISTRATION);
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		const std::string& str = buffer.GetString();
		/*Second step: accept answer from server, parse and trancfer to user.*/
		std::string doc = _sc.request(str);
		rapidjson::Document new_doc;
		new_doc.Parse(doc.c_str());
		std::string _type_ = new_doc["type"].GetString();
		if (_type_ == "ok")
			return _type_;
		else
			throw (const char*)new_doc["info"]["description"].GetString();
	}
	catch (const char *error) {
		return error;
	}
}

std::string RequestFormer::to_enter(std::string number, std::string password)
{
	try {
		/*First step: accept full data from user, generate it to JSON request
		*and send to the server.*/
		RequestFormer sx;
		sx.enter_old_user(number, password);
		rapidjson::Document document = sx.to_json(REQUEST_LOGIN);
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		const std::string& str = buffer.GetString();

		/*Second step: accept answer from server, parse and trancfer to user.*/
		std::string doc = _sc.request(str);
		rapidjson::Document new_doc;
		new_doc.Parse(doc.c_str());
		std::string _type_ = new_doc["type"].GetString();
		if (_type_ == "ok")
			return _type_;
		else
			return new_doc["info"]["description"].GetString();

    //LogPrinter::print();
	}
	catch (const char *error) {
		return error;
	}
}
