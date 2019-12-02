#pragma once

#include <string>
#include "util.h"

namespace constants {

	const std::string empty_val = "[EMPTY]";

	//const std::string RETROARCH_DIR = "C:\\Users\\gameshow\\AppData\\Roaming\\RetroArch\\";
	//const std::string RETROARCH_EXE = utils::trailingSlashIt(RETROARCH_DIR) + "retroarch.exe";

	const std::string RETROARCH_BASE_DIR = "D:\\Programs\\RetroArch\\";
	const std::string RETROARCH_EXE = utils::trailingSlashIt(RETROARCH_BASE_DIR) + "retroarch.exe";
	const std::string RETROARCH_INFO_DIR = utils::trailingSlashIt( utils::trailingSlashIt(RETROARCH_BASE_DIR) + "info" );
	const std::string RETROARCH_CORE_DIR = utils::trailingSlashIt(utils::trailingSlashIt(RETROARCH_BASE_DIR) + "cores");

	const std::string FEXT_CORE = ".dll";
	const std::string FEXT_INFO = ".info";

}