#pragma once

#include <string>
#include "const.h"
#include "cores.h"
#include "filesys.h"

//Functions in wiki_gen are NOT pure functions (i.e. stateless)
namespace wiki {

	struct test_state_t {

		bool status_loads;    //Does it load into RetroArch?
		bool status_graphics; //Do the graphics display properly?
		bool status_sound;    //Does the sound work properly?
		bool status_controls; //Do the controls work properly?
	};
	
	void wpg_set_rom(fs::basic_file_pointer_t rom);
	void wpg_add_core_config(fs::basic_file_pointer_t core, test_state_t test_state);
	void wpg_write_to_stream(std::ostream& out);

	fs::basic_file_pointer_t queryinfo_rom(std::string path);
	fs::basic_file_pointer_t queryinfo_core(std::string path);
	test_state_t queryinfo_test_results();
}