#pragma once

#include "const.h"

#include <string>
#include <vector>

namespace fs {

	//Represents either a ROM or a core DLL. Combine two to get a runnable RetroArch.
	struct basic_file_pointer_t {
		std::string pName = constants::empty_val;  //The pretty name (Mesen)
		std::string tName = constants::empty_val;  //The technical name (mesen_libretro.dll)
		std::string path  = constants::empty_val;  //The file path
		std::string group = constants::empty_val;  //Archive set or console
	};

	//Represents a key-value string pair in a dictionary
	struct kv_pair_str_t {
		std::string k, v;
	};

	//Represents a file with extended info (metadata)
	struct metadata_t {
		std::vector<fs::kv_pair_str_t> info_dict;
	};

	//Represents a ROM/DLL plus any metadata known about it.
	struct file_pointer_t : basic_file_pointer_t {
		bool has_metadata = false;
		metadata_t file_metadata;
	};



	//Check if a file exists
	bool file_exists(std::string path);

	//Extract only the filename from a full filepath
	std::string split_filename_from_path(std::string path, char delim = '\\');

	//NOT CROSSPLATFORM - only works for windows
	//Taken from https://stackoverflow.com/a/20847429
	//List all files in a directory
	std::vector<std::string> dir_list(std::string dirpath, std::string fext = ".*");

	//REPLace File EXTension
	std::string repl_fext(std::string file, std::string ext);

}