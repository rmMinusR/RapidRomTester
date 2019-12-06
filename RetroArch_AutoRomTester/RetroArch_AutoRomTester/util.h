#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>

namespace fs {

	//Add a trailing delimiter
	std::string trailingSlashIt(std::string path, char delim = '\\');

}

namespace utils {

	//String utils
	
	//Add quotes to escape the following string&
	void quote_escape(std::string& s);

	//Remove quotes from the string, inline
	std::string strip_quotes(std::string s);
	
	//Extract a single argument
	void rip_split(std::string full, std::string& part0, std::string& part1, char delim = ' ');

	//Make a string URL-safe
	//Algorithm pulled from https://stackoverflow.com/a/4643526
	std::string make_url_safe(std::string in);

	//Trim extra characters
	void trim_padding(std::string& s, char delim = ' ');

	//Print array
	void vector_print(std::vector<std::string> x);


	
	//Misc stuff
	
	//Replaces system("pause")
	void pause();

	//Check to see if a vector contains an element
	bool vector_contains(std::string element, std::vector<std::string> vec);
	


	//User query functions

	//Query for a std::string
	std::string query_user_s(std::string msg);
	//Query for a const char*
	const char* query_user_cs_c(std::string msg);
	//Query for a char*
	char* query_user_cs(std::string msg);
	//Query for a boolean
	bool query_user_b(std::string msg);
	//Query for a defaulted boolean
	bool query_user_b(std::string msg, bool val_default);

}