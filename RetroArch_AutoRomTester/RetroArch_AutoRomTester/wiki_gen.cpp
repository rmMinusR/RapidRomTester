#include "wiki_gen.h"

#include "util.h"
#include "filesys.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Functions in wiki_gen are NOT pure functions (i.e. stateless)
namespace wiki {
	
	fs::basic_file_pointer_t rom;
	std::vector<fs::basic_file_pointer_t> cores; //No need to make a struct to merge with test_results
	std::vector<test_state_t> test_results; //No need to make a struct to merge with cores

	//Wiki PaGe: set rom and clear cores and test results
	void wpg_set_rom(fs::basic_file_pointer_t rom) {
		wiki::rom = rom;
		cores.clear();
		test_results.clear();
	}
	
	//Wiki PaGe: register a core and its test results
	void wpg_add_core_config(fs::basic_file_pointer_t core, test_state_t test_state) {
		wiki::cores.push_back(core);
		wiki::test_results.push_back(test_state);
	}

	//Wiki PaGe: write to a stream
	void wpg_write_to_stream(std::ostream& out) {
		out << "h1. " << rom.pName << std::endl;
		out << std::endl;
		out << "Link to Wikipedia article about this game: https://en.wikipedia.org/wiki/" << utils::make_url_safe(rom.pName) << std::endl; //TODO not sure if it's Wikipedia-safe
		out << std::endl;
		out << "Any special considerations about how to play through the game in RetroArch." << std::endl;
		out << std::endl;
		//out << "$CORE_INFO $DISTRO_INFO" << std::endl;
		out << "|_.Core |_.Loads |_.Graphics |_.Sound |_.Controls |" << std::endl;
		for (unsigned int i = 0; i < cores.size(); i++) {
			out << "|" << cores[i].pName;
#define PRETTY_BOOL(x) (x?"={background-color: #bfb;}. PASS":"={background-color: #fbb;}. FAIL")
			out << "|" << PRETTY_BOOL(test_results[i].status_loads		);
			out << "|" << PRETTY_BOOL(test_results[i].status_graphics	);
			out << "|" << PRETTY_BOOL(test_results[i].status_sound		);
			out << "|" << PRETTY_BOOL(test_results[i].status_controls	);
#undef PRETTY_BOOL
			out << "|" << std::endl;
		}
		out << std::endl;
		out << "{{include(Launching_RetroArch)}}" << std::endl;
	}

	fs::basic_file_pointer_t queryinfo_rom(std::string path) {
		fs::basic_file_pointer_t out;

		out.path =  const_cast<char*>( path.c_str());
		out.tName = const_cast<char*>( fs::split_filename_from_path(path).c_str() );
		out.group = utils::query_user_s("What console? ");
		out.pName = utils::query_user_s("Game name? ");

		return out;
	}

	fs::basic_file_pointer_t queryinfo_core(std::string path) {
		fs::basic_file_pointer_t out;

		out.path = const_cast<char*>(path.c_str());
		out.tName = const_cast<char*>(fs::split_filename_from_path(path).c_str());
		out.group = utils::query_user_s("What console? ");
		out.pName = utils::query_user_s("Core name? "); //TODO make it read from the file

		return out;
	}

	test_state_t queryinfo_test_results() {
		test_state_t out;

		out.status_loads = utils::query_user_b("Does it load? ", true);

		if (out.status_loads) {
			out.status_graphics = utils::query_user_b("Does it display properly? ");
			out.status_sound = utils::query_user_b("Does it put out sound? ");
			out.status_controls = utils::query_user_b("Do the controls work? ");
		}
		else {
			out.status_graphics = false;
			out.status_sound = false;
			out.status_controls = false;
		}

		return out;
	}
}

/*
WIKI PAGE TEMPLATE

h1. $NAME

Link to Wikipedia article about this game: https://en.wikipedia.org/wiki/$NAME

Any special considerations about how to play through the game in RetroArch.

$CORE_INFO $DISTRO_INFO

{{include(Launching_RetroArch)}}



*/