#pragma once

#include "filesys.h"
#include "wiki_gen.h"

#include <string>
#include <vector>

namespace metadata {

	//Attempt to parse a .info file into &out
	bool info_parse(fs::metadata_t& out, std::string info_file_path);

	//Search for a specific .info file, then parse that into &out (if found)
	bool info_lookup(fs::metadata_t& out, fs::basic_file_pointer_t file, std::string info_search_dir = constants::RETROARCH_INFO_DIR);
	
	//From a file_extra_info_t, find a specific key and return the value
	std::string info_get_field(fs::metadata_t info, std::string key);
	
	//(UNRELIABLE - LONG PROCESS TIME) List all known consoles (using constants::RETROARCH_INFO_DIR)
	std::vector<std::string> list_known_consoles(std::string info_search_dir = constants::RETROARCH_INFO_DIR);
}