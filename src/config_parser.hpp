#pragma once
#include <string>
#include <map>

// INI parser
class config_parser {
	public:
		config_parser(const std::string &filename);
		std::string get_value(const std::string &section, const std::string &key);
		std::map<std::string, std::map<std::string, std::string>> data;

	private:
		std::string trim(const std::string &str);
};
