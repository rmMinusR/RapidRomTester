#include "user_command.h"

#include "cores.h"
#include "retro_call.h"

#include <iostream>
#include <fstream>

namespace user_command {

	//> rom *
	//Attempt to load a ROM from a file
	bool do_load_rom(fs::basic_file_pointer_t& rom, std::string arg_chunk_in) {
		std::string arg_chunk = utils::strip_quotes(arg_chunk_in);
		if (fs::file_exists(arg_chunk)) {
			//Buggy, disabled
			//utils::vector_print(extra_info::list_known_consoles());
			rom = wiki::queryinfo_rom(arg_chunk);
			wiki::wpg_set_rom(rom);
			std::cout << "Loaded ROM '" << rom.tName << "'" << std::endl;
			return true;
		} else {
			std::cout << "File not found: '" << arg_chunk << "'" << std::endl;
			return false;
		}
	}

	//> core * (file or folder)
	//Attempt to load a core or set of cores from a file or folder
	std::vector<fs::file_pointer_t> do_load_core(std::string arg_chunk) {
		std::vector<fs::file_pointer_t> cores;
		arg_chunk = utils::strip_quotes(arg_chunk);

		if (arg_chunk.at(arg_chunk.length() - 1) == constants::FS_DELIM) {
			//It's a folder, batch process

			std::vector<std::string> dlls = fs::dir_list(arg_chunk, constants::FEXT_CORE);
			for (std::string dll : dlls) {

				fs::file_pointer_t temp;
				temp.path = fs::trailingSlashIt(arg_chunk)+dll;
				temp.tName = fs::split_filename_from_path(temp.path);

				fs::metadata_t metadata;
				if (metadata::info_lookup(metadata, temp)) {
					std::cout << "Detected metadata file: " << temp.tName << std::endl;
					temp.pName = metadata::info_get_field(metadata, constants::dict_keys_cores::corename);
					temp.group = metadata::info_get_field(metadata, constants::dict_keys_cores::systemid);
					cores.push_back(temp);
				}
				else if (metadata::info_lookup(metadata, temp, constants::CUSTOM_METADATA_DIR)) {
					std::cout << "Detected metadata file: " << temp.tName << std::endl;
					temp.pName = metadata::info_get_field(metadata, constants::dict_keys_cores::corename);
					temp.group = metadata::info_get_field(metadata, constants::dict_keys_cores::systemid);
					cores.push_back(temp);
				}
				else {
					std::cout << "Could not detect metadata file: " << temp.tName << std::endl;
					cores.push_back(wiki::queryinfo_core(arg_chunk));
				}

			}
		}
		else {
			//It's a file, single process

			if (fs::file_exists(arg_chunk)) { //Make sure the core file exists
			
				fs::file_pointer_t temp;
				temp.path = arg_chunk;
				temp.tName = fs::split_filename_from_path(temp.path);
			
				fs::metadata_t metadata;
				if (metadata::info_lookup(metadata, temp)) {
					std::cout << "Detected metadata file!" << std::endl;
					temp.pName = metadata::info_get_field(metadata, constants::dict_keys_cores::corename);
					temp.group = metadata::info_get_field(metadata, constants::dict_keys_cores::systemid);
					cores.push_back(temp);
				}
				else {
					std::cout << "Could not detect metadata file!" << std::endl;
					cores.push_back(wiki::queryinfo_core(arg_chunk));
				}

				std::cout << "Loaded core '" << cores[cores.size()-1].tName << "'" << std::endl;
			} else {
				std::cout << "File not found: '" << arg_chunk << "'" << std::endl;
			}
		}

		return cores;
	}
	
	//> go
	//Try to start an instance of RetroArch using the given config
	bool do_try_launch(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core) {
		if (rom.path == constants::empty_val) { //Make sure the rom is selected
			std::cout << "Cannot launch without a ROM!" << std::endl;
			return false;
		}
		if (core.path == constants::empty_val) { //Make sure the core is selected
			std::cout << "Cannot launch without a core!" << std::endl;
			return false;
		}

		//Files are selected for both core and rom, launch
		std::cout << "Launching RetroArch..." << std::endl;
		retro_call::run_rom(core.path, rom.path);

		return true;
	}

	//> batch
	//Batch-processing mode - equivalent to looped "> load > go > wiki add"
	bool do_try_batch(fs::basic_file_pointer_t rom, std::vector<fs::file_pointer_t> cores) {
		
		for (fs::file_pointer_t core : cores) {
			std::cout << "Testing " << core.pName << std::endl;
			fs::metadata_t metadata;
			metadata::info_lookup(metadata, core);

			if (metadata::info_get_field(metadata, constants::dict_keys_cores::systemid) == rom.group) {
				user_command::do_try_launch(rom, core);
				user_command::wiki_do_add(rom, core);
			}

		}

		return true;
	}

	//> wiki *
	//Delegates based on sub-command
	void wiki_generic(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core, std::string arg_chunk) {
		std::string subcmd, subcmd_args;
		utils::rip_split(arg_chunk, subcmd, subcmd_args);

		if (subcmd == "add") {
			wiki_do_add(rom, core);
		}
		else if (subcmd == "out") {
			wiki_do_out(rom, core, subcmd_args);
		}
		else {
			std::cout << "Subcommand not recognized. [add, out]" << std::endl;
		}
	}
	
	//> wiki add *
	//Add test results
	void wiki_do_add(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core) {
		wiki::wpg_add_core_config(core, wiki::queryinfo_test_results());
	}

	//> wiki out
	//Output the wikifile
	void wiki_do_out(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core, std::string arg_chunk) {
		if (arg_chunk.length() > 0) { //An argument was supplied

			if (arg_chunk == "preview") {
				wiki::wpg_write_to_stream(std::cout);
			}
			else {
				std::ofstream fout(arg_chunk);
				if (fout.good()) {
					wiki::wpg_write_to_stream(fout);
				}
				else {
					std::cout << "Failed to open a file with that name." << std::endl;
				}
				fout.close();
			}

		}
		else { //No argument supplied
			std::cout << "The command 'wiki out' requires an output argument. ['preview' or a filepath]" << std::endl;
		}
	}
	
}