#pragma once

#include <iostream>

namespace utils {

	//File functions

	//Add a trailing delimiter
	std::string trailingSlashIt(std::string path, char delim = '\\');
	
	//Check if a file exists
	bool is_file_valid(std::string path);
	
	//Extract only the filename from a full filepath
	std::string split_filename_from_path(std::string path, char delim = '\\');


	//String utils
	
	//Add quotes to escape the following string&
	void quote_escape(std::string& s);

	//Remove quotes from the string, inline
	std::string strip_quotes(std::string s);
	
	//Extract a single argument
	void rip_arg(std::string full, std::string& part0, std::string& part1, char delim = ' ');

	//Make a string URL-safe
	//Algorithm pulled from https://stackoverflow.com/a/4643526
	std::string make_url_safe(std::string in);


	//Replaces system("pause")
	void pause();
	

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