#pragma once

#include <string>

namespace constants {

	const std::string empty_val = "[EMPTY]";

	const std::string FEXT_CORE = ".dll";
	const std::string FEXT_INFO = ".info";

	const char FS_DELIM = '\\';

}

#include "filesys.h"
#include "util.h"

namespace constants {

	const std::string RETROARCH_BASE_DIR = "C:\\Users\\gameshow\\AppData\\Roaming\\RetroArch\\";
	
	//const std::string RETROARCH_BASE_DIR = "D:\\Programs\\RetroArch\\";
	const std::string RETROARCH_EXE = fs::trailingSlashIt(RETROARCH_BASE_DIR) + "retroarch.exe";
	const std::string RETROARCH_INFO_DIR = fs::trailingSlashIt(fs::trailingSlashIt(RETROARCH_BASE_DIR) + "info" );
	const std::string RETROARCH_CORE_DIR = fs::trailingSlashIt(fs::trailingSlashIt(RETROARCH_BASE_DIR) + "cores");

	namespace dict_keys_cores {
		const std::string display_name				= ("display_name"			);
		const std::string authors					= ("authors"				);
		const std::string supported_extensions		= ("supported_extensions"	);
		const std::string corename					= ("corename"				);
		const std::string manufacturer				= ("manufacturer"			);
		const std::string categories				= ("categories"				);
		const std::string systemname				= ("systemname"				);
		const std::string systemid					= ("systemid"				);
		const std::string database					= ("database"				);
		const std::string license					= ("license"				);
		const std::string permissions				= ("permissions"			);
		const std::string display_version			= ("display_version"		);
		const std::string supports_no_game			= ("supports_no_game"		);
		const std::string firmware_count			= ("firmware_count"			);
		const std::string firmwareN_desc			= ("firmware%s_desc"		);
		const std::string firmwareN_path			= ("firmware%s_path"		);
		const std::string firmwareN_opt				= ("firmware%s_opt"			);
		const std::string notes						= ("notes"					);

		/*
		SAMPLE: mesen_libretro.info
		
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
		*/
	}

}