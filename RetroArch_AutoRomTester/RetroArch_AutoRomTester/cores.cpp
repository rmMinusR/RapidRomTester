#include "cores.h"

namespace utils {
	namespace cores {

		const char* core_get_dll(int core) {
			switch (core) {

			//NES family
			case BNES:		return "bnes_libretro.dll";
			case EMUX_NES:	return "emux_nes_libretro.dll";
			case FCEUMM:	return "fceumm_libretro.dll";
			case MESEN:		return "mesen_libretro.dll";
			case NESTOPIA:	return "nestopia_libretro.dll";
			case QUICKNES:	return "quicknes_libretro.dll";

			default: return "INVALID CORE";
			}
		}

	}
}