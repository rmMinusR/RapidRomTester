#include "cores.h"
#include "util.h"

#include <fstream>
#include <vector>
#include <string>

namespace extra_info {

	bool info_parse(file_extra_info_t& out, wiki::file_pointer_t file) {
		std::vector<kv_pair_str_t> dict(0);

		std::ifstream fin(file.path);
		if (!fin.good()) return false;

		std::string line;
		while(true) {
			//Pull a line and check it
			std::getline(fin, line);
			if (line.c_str()[0] == EOF || line.length() <= 1) break;

			//Rip-split it
			std::string key, val;
			utils::rip_split(line, key, val, '=');
			utils::trim_padding(key, ' ');
			utils::trim_padding(val, ' ');

			//Convert to KV pair
			kv_pair_str_t pair;
			pair.k = key.c_str();
			pair.v = val.c_str();

			//Push into dict
			dict.push_back(pair);
		}

		
	}

	std::string info_get_field(file_extra_info_t info, char* key) {
		return "";
	}

}