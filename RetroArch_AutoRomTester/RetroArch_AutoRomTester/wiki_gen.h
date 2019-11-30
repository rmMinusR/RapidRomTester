#pragma once

#include <string>
#include "const.h"

//Functions in wiki_gen are NOT pure functions (i.e. stateless)
namespace wiki {

	struct HALF_CONFIG_STATE { //Represents either a ROM or a core DLL. Combine two to get a runnable RetroArch.
		std::string pName  = constants::empty_val;  //The pretty name (Mesen)
		std::string tName  = constants::empty_val;  //The technical name (mesen_libretro.dll)
		std::string path   = constants::empty_val;  //The file path
		std::string family = constants::empty_val;  //The family of the file (NES)
	};

	struct TEST_STATE {
		//HALF_CONFIG_STATE core, rom;

		bool status_loads;    //Does it load into RetroArch?
		bool status_graphics; //Do the graphics display properly?
		bool status_sound;    //Does the sound work properly?
		bool status_controls; //Do the controls work properly?
	};
	
	void wpg_set_rom(HALF_CONFIG_STATE rom);
	void wpg_add_core_config(HALF_CONFIG_STATE core, TEST_STATE test_state);
	void wpg_write_to_stream(std::ostream& out);

	HALF_CONFIG_STATE queryinfo_rom(std::string path);
	HALF_CONFIG_STATE queryinfo_core(std::string path);
	TEST_STATE queryinfo_test_results();
}