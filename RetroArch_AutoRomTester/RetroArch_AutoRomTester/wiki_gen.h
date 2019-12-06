#pragma once

#include "const.h"
#include "cores.h"
#include "filesys.h"

#include <string>
#include <vector>

//Functions in wiki_gen are NOT pure functions (i.e. stateless)
namespace wiki {

	struct test_state_t {

		bool status_loads;    //Does it load into RetroArch?
		bool status_graphics; //Do the graphics display properly?
		bool status_sound;    //Does the sound work properly?
		bool status_controls; //Do the controls work properly?
	};
	
	struct wiki_page_t {
		fs::file_pointer_t rom;
		std::vector<fs::file_pointer_t> cores;
		std::vector<test_state_t> test_results;
	};

	void wpg_set_rom(fs::basic_file_pointer_t rom);
	void wpg_add_core_config(fs::basic_file_pointer_t core, test_state_t test_state);
	void wpg_write_to_stream(std::ostream& out);

	fs::file_pointer_t queryinfo_rom(std::string path);
	fs::file_pointer_t queryinfo_core(std::string path);
	test_state_t queryinfo_test_results();
}