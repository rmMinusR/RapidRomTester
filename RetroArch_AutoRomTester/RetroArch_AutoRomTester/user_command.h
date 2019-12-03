#pragma once

#include "wiki_gen.h"

namespace user_command
{
	void do_load_rom(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);
	void do_load_core(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);
	bool do_try_launch(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);

	void wiki_generic(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);
	void wiki_do_add(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);
	void wiki_do_out(wiki::file_pointer_t& rom, wiki::file_pointer_t& core, std::string arg_chunk);
}