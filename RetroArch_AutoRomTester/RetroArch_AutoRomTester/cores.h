#pragma once

#include "wiki_gen.h"

#include <string>
#include <vector>

namespace extra_info {

	struct kv_pair_str_t {
		std::string k, v;
	};

	struct file_extra_info_t {
		std::vector<kv_pair_str_t> info_dict;
		wiki::file_pointer_t file;
	};

	bool info_parse(file_extra_info_t& out, std::string info_file_path);

	bool info_lookup(file_extra_info_t& out, wiki::file_pointer_t file, std::string info_search_dir = constants::RETROARCH_INFO_DIR);
	
	std::string info_get_field(file_extra_info_t info, std::string key);

}