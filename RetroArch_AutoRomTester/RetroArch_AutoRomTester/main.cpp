#include <iostream> //for console io
#include <fstream>
#include <future> //for async
#include <chrono> //for delay()

//#include "const.h" //Explodes for some reason
#include "util.h"
#include "retro_call.h"
#include "wiki_gen.h"
#include "cores.h"

using namespace std;

int main(int argc, char** argv) {

	std::cout << "Rapid ROM Tester microshell v0.7 by Robert Christensen" << std::endl;
	std::cout << "For use in the Champlain College Game History Teaching Collection" << std::endl;
	
	//Status variables
	wiki::file_pointer_t last_selected_rom;
	wiki::file_pointer_t last_selected_core;
	do {
		{ //Output status info
			std::cout << std::endl;
			string pNameRom  = utils::split_filename_from_path(last_selected_rom .path); if(pNameRom  == constants::empty_val) pNameRom  = "not loaded"; else pNameRom  = "'"+pNameRom +"'";
			string pNameCore = utils::split_filename_from_path(last_selected_core.path); if(pNameCore == constants::empty_val) pNameCore = "not loaded"; else pNameCore = "'"+pNameCore+"'";
			std::cout << "ROM: "  << pNameRom  << std::endl;
			std::cout << "Core: " << pNameCore << std::endl;
		}
		string user_input = utils::query_user_s("> ");

		string command, args;
		utils::rip_split(user_input, command, args);
		
		//Process the command
		if (command == "rom") { //Try to load a rom
			
			args = utils::strip_quotes(args);
			if (utils::file_exists(args)) {
				last_selected_rom = wiki::queryinfo_rom(args);
				wiki::wpg_set_rom(last_selected_rom);
				std::cout << "Loaded ROM '" << last_selected_rom.tName << "'" << std::endl;
			} else {
				std::cout << "File not found: '" << args << "'" << std::endl;
			}

		}
		else if (command == "core") { //Try to load a core and launch RetroArch

			args = utils::strip_quotes(args);
			if (utils::file_exists(args)) { //Make sure the core file exists
				last_selected_core = wiki::queryinfo_core(args);
				std::cout << "Loaded core '" << last_selected_core.tName << "'" << std::endl;

				extra_info::file_extra_info_t a;
				std::cout << extra_info::info_lookup(a, last_selected_core) << utils::file_exists(last_selected_core.path) << std::endl;
				std::cout << a.info_dict.size() << "" << extra_info::info_get_field(a, "systemname") << std::endl;
			}
			else {
				std::cout << "File not found: '" << args << "'" << std::endl;
			}

		}
		else if(command == "test") { //Attempt to launch a RetroArch instance

			bool can_run = true;

			if (last_selected_rom.path == constants::empty_val) { //Make sure the rom is selected
				std::cout << "Cannot test without a ROM!" << std::endl;
				can_run = false;
			}
			if (last_selected_core.path == constants::empty_val) { //Make sure the core is selected
				std::cout << "Cannot test without a core!" << std::endl;
				can_run = false;
			}

			if (can_run) { //If files are selected for both core and rom, launch
				std::cout << "Launching RetroArch..." << std::endl;
				retro_call::run_rom(last_selected_core.path, last_selected_rom.path);
			}

		}
		else if (command == "wiki") { //Wiki page functions
			std::string subcmd, subargs;
			utils::rip_split(args, subcmd, subargs);

			if (subcmd == "add") {
				wiki::wpg_add_core_config(last_selected_core, wiki::queryinfo_test_results());
			}
			else if (subcmd == "out") {
				if (subargs.length() > 0) { //An argument was supplied

					if (subargs == "preview") {
						wiki::wpg_write_to_stream(cout);
					}
					else {
						std::ofstream fout(subargs);
						if (fout.good()) {
							wiki::wpg_write_to_stream(fout);
						}
						else {
							std::cout << "Failed to open a file with that name." << endl;
						}
						fout.close();
					}

				}
				else { //No argument supplied
					std::cout << "The command 'wiki out' requires an output argument. ['preview' or a filepath]" << std::endl;
				}
			}
			else {
				std::cout << "Subcommand not recognized. [add, out]" << std::endl;
			}
		}
		else if (command == "exit") { //Exit the program
			break;
		}
		else { //Something not recognized
			std::cout << "Command not recognized. [rom, core, exit, test]" << std::endl;
		}

	} while (true);

	return EXIT_SUCCESS;
}