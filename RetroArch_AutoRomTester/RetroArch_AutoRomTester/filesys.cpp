#include "filesys.h"

#include <fstream>

namespace fs {

	bool file_exists(std::string path) {
		std::ifstream f(path.c_str());
		bool exists = f.good();
		f.close();
		return exists;
	}

	std::string split_filename_from_path(std::string path, char delim) {
		size_t last_delim = path.find_last_of(delim);

		if (last_delim == std::string::npos) return path;

		return path.substr(last_delim + 1, path.length() - last_delim - 1);
	}

	std::vector<std::string> dir_list(std::string dirpath, std::string fext) {
		std::vector<std::string> names;
		std::string search_path = dirpath + "/*" + fext;//"/*.*";
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return names;
	}

	std::string repl_fext(std::string file, std::string ext) {
		return file.substr(0, file.find_last_of('.')) + ext;
	}

}