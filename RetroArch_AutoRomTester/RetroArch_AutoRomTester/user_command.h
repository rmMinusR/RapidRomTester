#pragma once

#include "wiki_gen.h"

namespace user_command
{
	bool do_load_rom(wiki::file_pointer_t& rom, std::string arg_chunk);
	std::vector<wiki::file_pointer_t> do_load_core(std::string arg_chunk);
	bool do_try_launch(wiki::file_pointer_t rom, wiki::file_pointer_t core);
	bool do_try_batch(wiki::file_pointer_t rom, std::vector<wiki::file_pointer_t> cores);


	void wiki_generic(wiki::file_pointer_t rom, wiki::file_pointer_t core, std::string arg_chunk);
	void wiki_do_add(wiki::file_pointer_t rom, wiki::file_pointer_t core);
	void wiki_do_out(wiki::file_pointer_t rom, wiki::file_pointer_t core, std::string arg_chunk);
}