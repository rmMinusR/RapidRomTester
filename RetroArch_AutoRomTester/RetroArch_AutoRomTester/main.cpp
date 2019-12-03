#include <iostream> //for console io
#include <fstream>
#include <future> //for async
#include <chrono> //for delay()

//#include "const.h" //Explodes for some reason
#include "util.h"
#include "retro_call.h"
#include "wiki_gen.h"
#include "cores.h"
#include "user_command.h"

//using namespace std;

int main(int argc, char** argv) {

	std::cout << "Rapid ROM Tester microshell v0.7 by Robert Christensen" << std::endl;
	std::cout << "For use in the Champlain College Game History Teaching Collection" << std::endl;
	
	//Status variables
	wiki::file_pointer_t rom;
	wiki::file_pointer_t core;
	do {
		{ //Output status info
			std::cout << std::endl;
			std::string pNameRom  = utils::split_filename_from_path(rom .path); if(pNameRom  == constants::empty_val) pNameRom  = "not loaded"; else pNameRom  = "'"+pNameRom +"'";
			std::string pNameCore = utils::split_filename_from_path(core.path); if(pNameCore == constants::empty_val) pNameCore = "not loaded"; else pNameCore = "'"+pNameCore+"'";
			std::cout << "ROM: "  << pNameRom  << std::endl;
			std::cout << "Core: " << pNameCore << std::endl;
		}
		std::string user_input = utils::query_user_s("> ");

		std::string command, args;
		utils::rip_split(user_input, command, args);
		
		//Process the command
		if (command == "rom") { //Try to load a rom
			user_command::do_load_rom(rom, core, args);
		}
		else if (command == "core") { //Try to load a core
			user_command::do_load_core(rom, core, args);
		}
		else if(command == "go") { //Attempt to launch a RetroArch instance
			user_command::do_try_launch(rom, core, args);
		}
		else if (command == "wiki") { //Wiki page functions
			user_command::wiki_generic(rom, core, args);
		}
		else if (command == "exit") { //Exit the program
			break;
		}
		else { //Something not recognized
			std::cout << "Command not recognized. [rom, core, go, wiki, exit]" << std::endl;
		}

	} while (true);

	return EXIT_SUCCESS;
}