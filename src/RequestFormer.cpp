/*
* Khomenko Jane
* Mail: tyryry221@gmail.com
* Github: JaneKKTTme
* Date: 14.03.19
*/

#define MATERIAL_SYM_LENGTH 256

#include "RequestFormer.h"
#include "requests.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"
#include <stdexcept>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "ServerConnector.h"
#include "LogPrinter.h"
#include "ConfigReader.h"

ServerConnector RequestFormer::_sc;

RequestFormer::RequestFormer()
{

}

RequestFormer::~RequestFormer()
{

}

void RequestFormer::connect_to_server()
{
    _sc.to_connect(ConfigReader::get("IP-address"), std::stoi(ConfigReader::get("Port")));
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
	else if (request == REQUEST_LOGIN) {
		document.SetObject();
		document.AddMember("request", REQUEST_LOGIN, allocator);
		info_val.SetObject();
		tmp.SetString(rapidjson::StringRef(_number.c_str()));
		info_val.AddMember("number", tmp, allocator);
		tmp.SetString(rapidjson::StringRef(_password.c_str()));
		info_val.AddMember("password", tmp, allocator);
		document.AddMember("info", info_val, allocator);
	}
	else if (request == REQUEST_GET_MATERIALS) {
		document.SetObject();
		document.AddMember("request", REQUEST_GET_MATERIALS, allocator);
		info_val.SetObject();
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
	std::string answer = _sc.request(str);
	rapidjson::Document new_document;
	new_document.Parse(answer.c_str());
	std::string buf;
	std::string _type_ = new_document["type"].GetString();
	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf += _type_;
		LogPrinter::print(buf);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_document["info"]["description"].GetString();
		LogPrinter::print(buf);
		throw (const char*)new_document["info"]["description"].GetString();
	}
}

void RequestFormer::to_enter(std::string number, std::string password,
				std::string& name, std::string& last_name,
				std::string& middle_name, std::string& type,
				std::queue <std::string>& clients_numbers)
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
	std::string answer = _sc.request(str);
	rapidjson::Document new_document;
	new_document.Parse(answer.c_str());
	std::string buf;
	std::string _type_ = new_document["type"].GetString();
	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf = buf + _type_ + "\n\"info\" {\n\t";
		name = new_document["info"]["name"].GetString();
		last_name = new_document["info"]["last_name"].GetString();
		middle_name = new_document["info"]["middle_name"].GetString();
		type = new_document["info"]["user_type"].GetString();
		buf = buf + "\"name\" : " + name + "\n\t\"last_name\" : " + last_name
				+ "\n\t\"middle_name\" : " + middle_name + "\n\t\"type\" : " + type;
		if (new_document["info"].HasMember("clients_numbers"))
		{
			buf = buf + "\n\t\"clients_numbers\" : [\n";
			const rapidjson::Value& clients = new_document["info"]["clients_numbers"];
			for (rapidjson::Value::ConstValueIterator itr = clients.Begin(); itr != clients.End(); ++itr)
			{
				std::string tmp = itr->GetString();
				clients_numbers.push(tmp);
				buf = buf + "\t\t" + tmp + "\n";
			}
		}
		buf += "}";
		LogPrinter::print(answer);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_document["info"]["description"].GetString();
		LogPrinter::print(buf);
		throw (const char*)new_document["info"]["description"].GetString();
	}
}

std::queue <Material> RequestFormer::to_get_materials()
{
	/*
	*First step: generate request to JSON format.
	*Request reports server that user want to get all materials.
	*/
	RequestFormer sx;
	rapidjson::Document document = sx.to_json(REQUEST_GET_MATERIALS);
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
	if (_type_ == "ok")
	{
		while (!new_document["info"].HasMember("description"))
		{
                        LogPrinter::print(answer);
			const rapidjson::Value& materials = new_document["info"]["materials"];
			for (rapidjson::Value::ConstValueIterator itr = materials.Begin(); itr != materials.End(); ++itr)
			{
				Material tmp;
				rapidjson::Value::ConstMemberIterator currentElement = itr->FindMember("title");
				tmp.title = currentElement->value.GetString();
				currentElement = itr->FindMember("unions");
				tmp.unions = currentElement->value.GetString();
				currentElement = itr->FindMember("price");
				tmp.price = currentElement->value.GetDouble();

				mtr.push(tmp);
			}

			answer = _sc.get_next_answer();
			new_document.Parse(answer.c_str());
		}

		LogPrinter::print(answer);
		std::cout << answer << std::endl;

		return mtr;
	}
	else
		throw (const char*)new_document["info"]["description"].GetString();

}

void RequestFormer::to_send_purchase(std::string foreman_number, std::string client_number, 
					double total_cost, std::queue <Purchase> table)
{
	/*
	*First step: generate data to JSON format from current table.
	*/
	rapidjson::Document document;
	rapidjson::Value info;
	rapidjson::Value mat;
	rapidjson::Value obj, tmp;
	rapidjson::Document::AllocatorType& alloc = document.GetAllocator();

	/*
	*Processing table data and data validation.
	*/
	while (!table.empty())
	{
		document.SetObject();
		document.AddMember("request", REQUEST_SEND_PURCHASE, alloc);
		info.SetObject();
		tmp.SetString(rapidjson::StringRef(foreman_number.c_str()));
		info.AddMember("foreman_num", tmp, alloc);
		tmp.SetString(rapidjson::StringRef(client_number.c_str()));
		info.AddMember("client_num", tmp, alloc);
		tmp = rapidjson::Value(total_cost);
		info.AddMember("total_cost", tmp, alloc);
		mat.SetArray();
		int i = 0;

		while ((BUFFER_SIZE - MATERIAL_SYM_LENGTH*(++i) >= 128) && (!table.empty()))
		{
			obj.SetObject();
			std::string tmp_s = table.front().title.c_str();
			tmp.SetString(table.front().title.c_str(), alloc);
			obj.AddMember("title", tmp, alloc);
			
			if (sizeof(table.front().quantity) <= sizeof(long))
			{
				tmp = rapidjson::Value(table.front().quantity);
				obj.AddMember("quantity", tmp, alloc);
			}
			tmp = rapidjson::Value(table.front().price);
			obj.AddMember("cost", tmp, alloc);

			mat.PushBack(obj, alloc);
			table.pop();
		}

		info.AddMember("purchase", mat, alloc);
		document.AddMember("info", info, alloc);

		rapidjson::StringBuffer str_buf;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(str_buf);
		document.Accept(writer);
		const std::string& str = str_buf.GetString();

		_sc.simple_request(str);
	}

	/*
	*Sign of data end for database.
	*/
	document.SetObject();
	document.AddMember("request", REQUEST_SEND_PURCHASE, alloc);
	info.SetObject();
	info.AddMember("description", "end", alloc);
	document.AddMember("info", info, alloc);

	rapidjson::StringBuffer str_buf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(str_buf);
	document.Accept(writer);
	const std::string& str = str_buf.GetString();

	std::string answer = _sc.request(str);

	/*
	*Second step: send request to server, accept answer and parse it.
	*/
	rapidjson::Document new_document;
	new_document.Parse(answer.c_str());
	std::string buf;
	std::string _type_ = new_document["type"].GetString();

	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf = buf + _type_ + "\n\"info\" {\n\t\n}";
		//LogPrinter::print(buf);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_document["info"]["description"].GetString();
		//LogPrinter::print(buf);
		throw (const char*)new_document["info"]["description"].GetString();
	}
}

std::queue <ShoppingList> RequestFormer::to_show_purchases(std::string foreman_number, std::string client_number)
{
	/*
	*First step: generate request to JSON format.
	*Request reports server that foreman want to see all puschases.
	*/
	rapidjson::Document document;
	rapidjson::Value info;
	rapidjson::Value mat;
	rapidjson::Value obj, tmp;
	rapidjson::Document::AllocatorType& alloc = document.GetAllocator();
	document.SetObject();

	document.AddMember("request", REQUEST_GET_PURCHASES, alloc);
	info.SetObject();
	tmp.SetString(rapidjson::StringRef(foreman_number.c_str()));
	info.AddMember("foreman_num", tmp, alloc);
	tmp.SetString(rapidjson::StringRef(client_number.c_str()));
	info.AddMember("client_num", tmp, alloc);
	document.AddMember("info", info, alloc);

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
	LogPrinter::print(answer);
	std::string _type_ = new_document["type"].GetString();

	/*
	*Third step: submit data in suitable format and send it to user.
	*/
	std::queue <ShoppingList> frm;
	if (_type_ == "ok")
	{
		
		std::string _method_ = new_document["info"]["method"].GetString();
		while (_method_ != "end of translation")
		{

			ShoppingList tmp_sl;
			tmp_sl.purchase_id = new_document["info"]["purchase_id"].GetInt();
			tmp_sl.total_cost = new_document["info"]["total_cost"].GetDouble();
			tmp_sl.status = new_document["info"]["status"].GetString();

			_method_ = new_document["info"]["method"].GetString();

			answer = _sc.get_next_answer();
			new_document.Parse(answer.c_str());

			LogPrinter::print(answer);
	
			while (_method_ != "end")
			{				

				const rapidjson::Value& mat = new_document["info"]["materials"];
				std::queue <Buying> tmp_qb;
				for (rapidjson::Value::ConstValueIterator itr = mat.Begin(); itr != mat.End(); ++itr)
				{
					Buying tmp_b;
					rapidjson::Value::ConstMemberIterator curElem = itr->FindMember("title");
					tmp_b.title = curElem->value.GetString();
					curElem = itr->FindMember("quantity");
					tmp_b.quantity = curElem->value.GetDouble();
					curElem = itr->FindMember("cost");
					tmp_b.cost = curElem->value.GetDouble();
						
					tmp_qb.push(tmp_b);
				}

				tmp_sl.purchase = tmp_qb;
				frm.push(tmp_sl);

				answer = _sc.get_next_answer();
				new_document.Parse(answer.c_str());

				LogPrinter::print(answer);

				if (new_document["info"].HasMember("method"))	
					_method_ = new_document["info"]["method"].GetString();
			}

			answer = _sc.get_next_answer();
			new_document.Parse(answer.c_str());

			LogPrinter::print(answer);

			if (new_document["info"].HasMember("method"))	
					_method_ = new_document["info"]["method"].GetString();
		}
		
		return frm;
	}
	else
		throw (const char*)new_document["info"]["description"].GetString();
}

void RequestFormer::to_send_evaluations(std::string client_number, std::queue <Evaluation> table)
{
	/*
	*First step: generate data to JSON format from current table.
	*/
	rapidjson::Document document;
	rapidjson::Value info;
	rapidjson::Value spl;
	rapidjson::Value obj, tmp;
	rapidjson::Document::AllocatorType& alloc = document.GetAllocator();

	/*
	*Processing table data and data validation.
	*/
	while (!table.empty())
	{
		document.SetObject();
		document.AddMember("request", REQUEST_SEND_EVALUATIONS, alloc);
		info.SetObject();
		tmp.SetString(rapidjson::StringRef(client_number.c_str()));
		info.AddMember("client_num", tmp, alloc);
		spl.SetArray();
		int i = 0;

		while ((BUFFER_SIZE - MATERIAL_SYM_LENGTH*(++i) >= 128) && (!table.empty()))
		{
			obj.SetObject();
			std::string tmp_s = table.front().id.c_str();
			tmp.SetString(table.front().id.c_str(), alloc);
			obj.AddMember("id", tmp, alloc);
			tmp.SetString(table.front().evaluation.c_str(), alloc);
			obj.AddMember("evaluation", tmp, alloc);

			spl.PushBack(obj, alloc);
			table.pop();
		}
		info.AddMember("purchases", spl, alloc);
		document.AddMember("info", info, alloc);

		rapidjson::StringBuffer str_buf;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(str_buf);
		document.Accept(writer);
		const std::string& str = str_buf.GetString();

		_sc.simple_request(str);
	}

	/*
	*Sign of data end for database.
	*/
	document.SetObject();
	document.AddMember("request", REQUEST_SEND_EVALUATIONS, alloc);
	info.SetObject();
	info.AddMember("description", "end", alloc);
	document.AddMember("info", info, alloc);

	rapidjson::StringBuffer str_buf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(str_buf);
	document.Accept(writer);
	const std::string& str = str_buf.GetString();

	std::string answer = _sc.request(str);

	/*
	*Second step: send request to server, accept answer and parse it.
	*/
	rapidjson::Document new_document;
	new_document.Parse(answer.c_str());
	std::string buf;
	std::string _type_ = new_document["type"].GetString();
	if (_type_ == "ok")
	{
		buf = "\"type\" : ";
		buf = buf + _type_ + "\n\"info\" {\n\t\n}";
		LogPrinter::print(buf);
	}
	else
	{
		buf = "\"error\" : ";
		buf = buf + new_document["info"]["description"].GetString();
		LogPrinter::print(buf);
		throw (const char*)new_document["info"]["description"].GetString();
	}
}
