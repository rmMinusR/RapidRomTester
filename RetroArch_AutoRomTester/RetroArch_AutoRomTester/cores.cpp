#include "cores.h"
#include "util.h"

#include <fstream>
#include <vector>
#include <string>

namespace extra_info {

	bool info_parse(file_extra_info_t& out, std::string info_file_path) {
		std::vector<kv_pair_str_t> dict(0); dict.reserve(32);

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

			//Push into dict
			dict.push_back(kv_pair_str_t{ utils::strip_quotes(key), utils::strip_quotes(val) }); //Why does $pair disappear on the next line?
		}

		out.info_dict = dict;
		return true;
	}

	bool info_lookup(file_extra_info_t& out, wiki::file_pointer_t resource_file, std::string info_search_dir) {
		std::string fname_target = resource_file.tName.substr(0, resource_file.tName.length() - constants::FEXT_CORE.length()) + constants::FEXT_INFO;

		std::vector<std::string> info_files = utils::dir_list(info_search_dir);
		for (int i = 0; i < info_files.size(); i++) {
			std::string fname = info_files[i];

			if (fname == utils::repl_fext(resource_file.tName, constants::FEXT_INFO)) {

				std::string fpath = utils::trailingSlashIt(info_search_dir) + fname;
				
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