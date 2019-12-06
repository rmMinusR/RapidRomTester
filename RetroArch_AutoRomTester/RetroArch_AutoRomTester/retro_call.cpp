#include "retro_call.h"

#include "util.h"
#include "const.h"

#include <string>


#include <windows.h>

#include <processthreadsapi.h>
#include <synchapi.h>
#include <handleapi.h>

namespace retro_call {

	int run_program(std::string exe, std::string pwd, std::string args) {

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		//Clear (zero) the si and pi structures
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		memset(&pi, 0, sizeof(pi));

		char* cs_args = const_cast<char*>( args.c_str() );

		bool processCreationStatus = CreateProcessA(
			exe.c_str(),
			cs_args,
			NULL,
			NULL,
			false,
			0,
			NULL,
			pwd.c_str(),
			&si,
			&pi
		);

		WaitForSingleObject(pi.hProcess, INFINITY); //Doesn't work?

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		
		return EXIT_SUCCESS;
	}

	//Run a rom using absolute paths for core and rom
	int run_rom(std::string core, std::string rom) {
		std::string core_path = core;
		std::string rom_path = rom;

		utils::quote_escape(core_path);
		utils::quote_escape(rom_path);

		std::string args = fs::split_filename_from_path(constants::RETROARCH_EXE)+" -L " + core_path + " " + rom_path;

		run_program(constants::RETROARCH_EXE, constants::RETROARCH_BASE_DIR, args);

		return EXIT_SUCCESS;
	}

	//Check to make sure the core path is valid
	int fancy_path_check(std::string path) {

		std::cout << path << (fs::file_exists(path) ? " [OK]" : " [NOT OK]") << std::endl;

		if (!fs::file_exists(path)) return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}

}