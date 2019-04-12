/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
*/

#define ADDRESS "192.168.43.33"
#define PORT 4512

#include "RequestFormer.h"
#include "requests.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include <stdexcept>
#include <iostream>
#include <cstdio>
#include "ServerConnector.h"
#include "LogPrinter.h"

ServerConnector RequestFormer::_sc;

RequestFormer::RequestFormer()
{

}

RequestFormer::~RequestFormer()
{

}

void RequestFormer::connect_to_server()
{
    _sc.to_connect(ADDRESS, PORT);
}

void RequestFormer::disconnect()
{
    _sc.close_connection();
}

void RequestFormer::set_new_user(std::string& name, std::string& last_name,
				 std::string& middle_name, std::string& number,
				 std::string& password, std::string& type, std::string& foreman_number)
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

void RequestFormer::to_register(std::string name, std::string last_name,
			       std::string middle_name, std::string number, std::string password,
			       std::string type, std::string foreman_number)
{
	/*
	*First step: accept full data from user, generate it to JSON request
	*and send to the server.
	*/
	RequestFormer sx;
	if (type == "foreman")
		foreman_number = "NULL";
	sx.set_new_user(name, last_name, middle_name, number, password, type, foreman_number);
	rapidjson::Document document = sx.to_json(REQUEST_REGISTRATION);
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	const std::string& str = buffer.GetString();

	/*
	*Second step: accept answer from server, parse and trancfer to user.
	*Answer from server prints to LogPrinter object.
	*/
	std::string doc = _sc.request(str);
	rapidjson::Document new_doc;
	new_doc.Parse(doc.c_str());
	std::string buf;
	std::string _type_ = new_doc["type"].GetString();
	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf += _type_;
		LogPrinter::print(buf);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_doc["info"]["description"].GetString();
		LogPrinter::print(buf);
		throw (const char*)new_doc["info"]["description"].GetString();
	}
}

void RequestFormer::to_enter(std::string& name, std::string& last_name,
			       std::string& middle_name, std::string number, std::string password)
{

	/*
	*First step: accept full data from user, generate it to JSON request
	*and send to the server.
	*/
	RequestFormer sx;
	sx.enter_old_user(number, password);
	rapidjson::Document document = sx.to_json(REQUEST_LOGIN);
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	const std::string& str = buffer.GetString();

	/*
	*Second step: accept answer from server, parse and trancfer to user.
	*Answer from server prints to LogPrinter object.
	*/
	std::string doc = _sc.request(str);
	rapidjson::Document new_doc;
	new_doc.Parse(doc.c_str());
	std::string buf;
	std::string _type_ = new_doc["type"].GetString();
	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf = buf + _type_ + "\n\"info\" {\n\t";
		name = new_doc["info"]["name"].GetString();
		last_name = new_doc["info"]["last_name"].GetString();
		middle_name = new_doc["info"]["middle_name"].GetString();
		buf = buf + "\"name\" : " + name + "\n\t\"last_name\" : " +
			last_name + "\n\t\"middle_name\" : " + middle_name + "\n}";
		LogPrinter::print(buf);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_doc["info"]["description"].GetString();
		LogPrinter::print(buf);
		throw (const char*)new_doc["info"]["description"].GetString();
	}
}

std::queue <Material> RequestFormer::to_get_materials() 
{

	/*
	*First step: generate request to JSON format.
	*Request reports server that user want to get all materials.
	*/
	rapidjson::Value info_val;
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.SetObject();
	document.AddMember("request", REQUEST_GET_MATERIALS, allocator);
	info_val.SetObject();
	rapidjson::StringBuffer str_buf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(str_buf);
	document.Accept(writer);
	const std::string& str = str_buf.GetString();

	/*
	*Second step: send request to server, accept answer and parse it.
	*/
	std::string answer = _sc.request(str);
	rapidjson::Document new_document;
	new_document.Parse(answer.c_str());
	std::string _type_ = new_document["type"].GetString();

	/*
	*Third step: submit data in suitable format and send it to user.
	*/
	std::queue <Material> mtr;
	if (_type_ == "ok") {
		while (!new_document.HasMember("description")) {
			const rapidjson::Value& materials = new_document["info"]["materials"];
			assert(materials.IsArray());
			for (rapidjson::Value::ConstValueIterator itr = materials.Begin(); itr != materials.End(); ++itr) {
				Material X;			
				rapidjson::Value::ConstMemberIterator currentElement = itr->FindMember("title");
				X.title = currentElement->value.GetString();;
				currentElement = itr->FindMember("unions");
				X.unions = currentElement->value.GetString();;
				currentElement = itr->FindMember("price");
				X.price = std::stod(currentElement->value.GetString());;
				mtr.push(X);
			}
			answer = get_next_answer();
			new_document.Parse(answer.c_str());
		}
		return mtr;
	}
	else
		throw (const char*)new_document["info"]["description"].GetString();
		
}
