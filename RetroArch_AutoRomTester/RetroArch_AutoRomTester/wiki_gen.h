#pragma once

#include <string>
#include "const.h"

//Functions in wiki_gen are NOT pure functions (i.e. stateless)
namespace wiki {

	struct file_pointer_t { //Represents either a ROM or a core DLL. Combine two to get a runnable RetroArch.
		std::string pName  = constants::empty_val;  //The pretty name (Mesen)
		std::string tName  = constants::empty_val;  //The technical name (mesen_libretro.dll)
		std::string path   = constants::empty_val;  //The file path
		std::string group  = constants::empty_val;  //Archive set or console
	};

	struct test_state_t {

		bool status_loads;    //Does it load into RetroArch?
		bool status_graphics; //Do the graphics display properly?
		bool status_sound;    //Does the sound work properly?
		bool status_controls; //Do the controls work properly?
	};
	
	void wpg_set_rom(file_pointer_t rom);
	void wpg_add_core_config(file_pointer_t core, test_state_t test_state);
	void wpg_write_to_stream(std::ostream& out);

	file_pointer_t queryinfo_rom(std::string path);
	file_pointer_t queryinfo_core(std::string path);
	test_state_t queryinfo_test_results();
}