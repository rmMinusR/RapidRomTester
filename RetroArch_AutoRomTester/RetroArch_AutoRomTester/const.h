#pragma once

#include <string>
#include "util.h"

namespace constants {

	const std::string empty_val = "[EMPTY]";

	//const std::string RETROARCH_DIR = "C:\\Users\\gameshow\\AppData\\Roaming\\RetroArch\\";
	//const std::string RETROARCH_EXE = utils::trailingSlashIt(RETROARCH_DIR) + "retroarch.exe";

	const std::string RETROARCH_DIR = "D:\\Programs\\RetroArch\\";
	const std::string RETROARCH_EXE = utils::trailingSlashIt(RETROARCH_DIR) + "retroarch.exe";

}