#include "user_command.h"

#include "cores.h"
#include "retro_call.h"

#include <iostream>
#include <fstream>

namespace user_command {

	//> rom *
	void do_load_rom(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
		arg_chunk = utils::strip_quotes(arg_chunk);
		if (utils::file_exists(arg_chunk)) {
			rom = wiki::queryinfo_rom(arg_chunk);
			wiki::wpg_set_rom(rom);
			std::cout << "Loaded ROM '" << rom.tName << "'" << std::endl;
		} else {
			std::cout << "File not found: '" << arg_chunk << "'" << std::endl;
		}
	}

	//> core *
	void do_load_core(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
		arg_chunk = utils::strip_quotes(arg_chunk);
		if (utils::file_exists(arg_chunk)) { //Make sure the core file exists
			
			wiki::file_pointer_t temp;
			temp.path = arg_chunk;
			temp.tName = utils::split_filename_from_path(temp.path);
			
			extra_info::file_extra_info_t metadata;
			if (extra_info::info_lookup(metadata, core)) {
				std::cout << "Detected metadata file!" << std::endl;
				temp.pName = extra_info::info_get_field(metadata, constants::dict_keys_cores::corename);
				temp.group = extra_info::info_get_field(metadata, constants::dict_keys_cores::systemid);
				core = temp;
			}
			else {
				std::cout << "Could not detect metadata file!" << std::endl;
				core = wiki::queryinfo_core(arg_chunk);
			}

			std::cout << "Loaded core '" << core.tName << "'" << std::endl;
		} else {
			std::cout << "File not found: '" << arg_chunk << "'" << std::endl;
		}
	}
	
	//> test
	bool do_try_launch(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
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

	//> wiki *
	void wiki_generic(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
		std::string subcmd, subcmd_args;
		utils::rip_split(arg_chunk, subcmd, subcmd_args);

		if (subcmd == "add") {
			wiki_do_add(rom, core, subcmd_args);
		}
		else if (subcmd == "out") {
			wiki_do_out(rom, core, subcmd_args);
		}
		else {
			std::cout << "Subcommand not recognized. [add, out]" << std::endl;
		}
	}
	
	//> wiki add *
	void wiki_do_add(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
		wiki::wpg_add_core_config(core, wiki::queryinfo_test_results());
	}

	//> wiki out
	void wiki_do_out(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk) {
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