#include <iostream> //for console io

//#include <future> //for async - unused
//#include <chrono> //for delay() - unused

#include "filesys.h"
#include "util.h"
#include "wiki_gen.h"
#include "user_command.h"

int main(int argc, char** argv) {

	std::cout << "Rapid ROM Tester microshell v0.7 by Robert Christensen" << std::endl;
	std::cout << "For use in the Champlain College Game History Teaching Collection" << std::endl;
	
	//Status variables
	fs::basic_file_pointer_t rom;
	std::vector<fs::basic_file_pointer_t> cores;
	do {
		{ //Output status info
			std::cout << std::endl;
			std::string pNameRom  = fs::split_filename_from_path(rom .path); if(pNameRom  == constants::empty_val) pNameRom  = "not loaded"; else pNameRom  = "'"+pNameRom +"'";
			std::string pNameCore = "[" + std::to_string(cores.size()) + " loaded]";
			std::cout << "ROM: "  << pNameRom  << std::endl;
			std::cout << "Core: " << pNameCore << std::endl;
		}
		std::string user_input = utils::query_user_s("> ");

		//Split into a command an arguments
		std::string command, args;
		utils::rip_split(user_input, command, args);
		
		//Process the command
		if (command == "rom") { //Try to load a rom
			user_command::do_load_rom(rom, args);
		}
		else if (command == "core") { //Try to load a core
			cores = user_command::do_load_core(args);
		}
		else if(command == "go") { //Attempt to launch a RetroArch instance
			if (cores.size() == 0) { std::cout << "No core loaded!" << std::endl; continue; }
			if (cores.size() >  1) { std::cout << "Too many cores loaded!" << std::endl; continue; }
			user_command::do_try_launch(rom, cores[0]);
		}
		else if (command == "batch") { //Start a batch test
			user_command::do_try_batch(rom, cores);
		}
		else if (command == "wiki") { //Wiki page functions
			user_command::wiki_generic(rom, cores[0], args);
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