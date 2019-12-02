#include "cores.h"
#include "util.h"

#include <fstream>
#include <vector>
#include <string>

namespace extra_info {

	bool info_parse(file_extra_info_t& out, std::string info_file_path) {
		std::vector<kv_pair_str_t> dict(0);

		std::ifstream fin(info_file_path);
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

			//Ensure both a key and value are present
			if (key.length() <= 0 || val.length() <= 0) continue;

			//Convert to KV pair
			kv_pair_str_t pair;
			pair.k = key.c_str();
			pair.v = val.c_str();

			//Push into dict
			dict.push_back(pair);
		}

		out.info_dict = dict;
		return true;
	}

	bool info_lookup(file_extra_info_t& out, wiki::file_pointer_t file, std::string info_search_dir) {
		std::string fname_target = file.tName.substr(0, file.tName.length() - constants::FEXT_CORE.length()) + constants::FEXT_INFO;

#pragma message("WARNING MISSING FILE LISTING ALGORITHM IN CORES.CPP")
		//TODO how to list all files in directory?
		char** info_files;
		int n_info_files;
		for (int i = 0; i < n_info_files; i++) {
			char* fname = info_files[i];
			
			if (fname == file.tName) {

				char* fpath = const_cast<char*>((utils::trailingSlashIt(info_search_dir) + fname).c_str());
				
				//TODO find better way to do this using pointers
				file_extra_info_t temp;
				info_parse(temp, fpath);

				out.info_dict = temp.info_dict;
				
				return true;
			}
		}

		return false;
	}

	std::string info_get_field(file_extra_info_t info, std::string key) {
		for (int i = 0; i < info.info_dict.size(); i++) {
			if (info.info_dict[i].k == key) return info.info_dict[i].v;
		}
		return constants::empty_val;
	}

}