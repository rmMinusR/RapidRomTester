#pragma once

#include "wiki_gen.h"

#include <string>
#include <vector>

namespace extra_info {

	struct kv_pair_str_t {
		const char* k;
		const char* v;
	};

	struct file_extra_info_t {
		std::vector<kv_pair_str_t> info_dict;
		wiki::file_pointer_t file;
	};

	bool info_parse(file_extra_info_t& out, std::string info_file_path);

	bool info_lookup(file_extra_info_t& out, wiki::file_pointer_t file, std::string info_search_dir = constants::RETROARCH_INFO_DIR);
	
	std::string info_get_field(file_extra_info_t info, std::string key);

	/*
	namespace keys_core {
		const char* display_name = "display_name";
		const char* authors = "authors";
		const char* supported_extensions = "supported_extensions";
		const char* corename = "corename";
		const char* manufacturer = "manufacturer";
		const char* categories = "categories";
		const char* systemname = "systemname";
		const char* systemid = "systemid";
		const char* database = "database";
		const char* license = "license";
		const char* permissions = "permissions";
		const char* display_version = "display_version";
		const char* supports_no_game = "supports_no_game";
		const char* firmware_count = "firmware_count";
		const char* firmwareN_desc = "firmware%s_desc";
		const char* firmwareN_path = "firmware%s_path";
		const char* firmwareN_opt = "firmware%s_opt";
		const char* notes = "notes";

		/*
		SAMPLE: Mesen
		
		display_name = "Nintendo - NES / Famicom (Mesen)"
		authors = "M. Bibaud (aka Sour)"
		supported_extensions = "nes|fds|unf|unif"
		corename = "Mesen"
		manufacturer = "Nintendo"
		categories = "Emulator"
		systemname = "Nintendo Entertainment System"
		systemid = "nes"
		database = "Nintendo - Nintendo Entertainment System|Nintendo - Family Computer Disk System"
		license = "GPLv3"
		permissions = ""
		display_version = "0.9.4"
		supports_no_game = "false"
		firmware_count = 1
		firmware0_desc = "disksys.rom (Family Computer Disk System BIOS)"
		firmware0_path = "disksys.rom"
		firmware0_opt = "true"
		notes = "(!) disksys.rom (md5): ca30b50f880eb660a320674ed365ef7a|Press Retropad R1 to switch disk side.|HD Packs go in %system%/HdPacks/%game_name%|Custom palette in %system%/MesenPalette.pal"
	}
	*/
}