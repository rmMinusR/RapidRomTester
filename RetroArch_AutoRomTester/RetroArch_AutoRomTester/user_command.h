#pragma once

#include "wiki_gen.h"

namespace user_command
{
	bool do_load_rom(fs::basic_file_pointer_t& rom, std::string arg_chunk);
	std::vector<fs::file_pointer_t> do_load_core(std::string arg_chunk);
	bool do_try_launch(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core);
	bool do_try_batch(fs::basic_file_pointer_t rom, std::vector<fs::file_pointer_t> cores);


	void wiki_generic(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core, std::string arg_chunk);
	void wiki_do_add(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core);
	void wiki_do_out(fs::basic_file_pointer_t rom, fs::basic_file_pointer_t core, std::string arg_chunk);
}