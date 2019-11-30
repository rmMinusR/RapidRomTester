#pragma once

namespace utils {
	namespace cores {

		enum e {
			BNES,
			EMUX_NES,
			FCEUMM,
			MESEN,
			NESTOPIA,
			QUICKNES,
			
			N_KNOWN_CORES //Shortcut for number of known, registered cores
		};

		int CORES_NES[] = {
				BNES,
				EMUX_NES,
				FCEUMM,
				MESEN,
				NESTOPIA,
				QUICKNES
		};

		const char* core_get_dll(int core);

	}
}