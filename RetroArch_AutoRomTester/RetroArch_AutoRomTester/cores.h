#pragma once

#include "wiki_gen.h"

#include <string>
#include <vector>

namespace core_metadata {

	//Represents a key-value string pair in a dictionary
	struct kv_pair_str_t {
		std::string k, v;
	};

	//Represents a file with extended info (metadata)
	struct file_extra_info_t {
		std::vector<kv_pair_str_t> info_dict;
		wiki::file_pointer_t file;
	};

	//Attempt to parse a .info file into &out
	bool info_parse(file_extra_info_t& out, std::string info_file_path);

	//Search for a specific .info file, then parse that into &out (if found)
	bool info_lookup(file_extra_info_t& out, wiki::file_pointer_t file, std::string info_search_dir = constants::RETROARCH_INFO_DIR);
	
	//From a file_extra_info_t, find a specific key and return the value
	std::string info_get_field(file_extra_info_t info, std::string key);
	
	//(UNRELIABLE - LONG PROCESS TIME) List all known consoles (using constants::RETROARCH_INFO_DIR)
	std::vector<std::string> list_known_consoles(std::string info_search_dir = constants::RETROARCH_INFO_DIR);
}