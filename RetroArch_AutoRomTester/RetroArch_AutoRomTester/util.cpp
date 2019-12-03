#include "util.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
#include <Windows.h>
//#include <filesystem> //REQUIRES C++17

namespace utils {

	std::string trailingSlashIt(std::string path, char delim) {
		if (!path.empty() && path.back() != delim) {
			return path + delim;
		}
		else {
			return path;
		}
	}

	bool file_exists(std::string path) {
		std::ifstream f(path.c_str());
		bool exists = f.good();
		f.close();
		return exists;
	}

	void quote_escape(std::string& s) { s = "\"" + s + "\""; };

	//Pause until any key is pressed
	void pause() {
		std::cout << "Press any key to continue..." << std::endl;
		char c = _getch();
	}

	std::string split_filename_from_path(std::string path, char delim) {
		size_t last_delim = path.find_last_of(delim);

		if (last_delim == std::string::npos) return path;
		
		return path.substr(last_delim+1, path.length()-last_delim-1);
	}

	std::string strip_quotes(std::string s) {
		if (s.at(0) == '\"' || s.at(0) == '\'') {
			if (s.at(0) == s.at(s.length() - 1)) return s.substr(1, s.length() - 2);
		}
		return s;
	}

	std::string query_user_s(std::string msg) {
		std::cout << msg;
		std::string tmp;
		std::getline(std::cin, tmp);
		return tmp;
	}

	const char* query_user_cs_c(std::string msg) {
		return query_user_s(msg).c_str();
	}

	char* query_user_cs(std::string msg) {
		return const_cast<char*>(query_user_cs_c(msg));
	}

	bool query_user_b(std::string msg) {
		std::cout << msg << "(y/n) ";
		while (true) {
			char input = tolower(_getch());
			if (input == 'y') { std::cout << input << std::endl; return true; }
			if (input == 'n') { std::cout << input << std::endl; return false; }
		}
	}

	bool query_user_b(std::string msg, bool val_default) {
		if (val_default) {
			std::cout << msg << "(Y/n) ";
		} else {
			std::cout << msg << "(y/N) ";
		}
		while (true) {
			char input = tolower(_getch());
			
			if (input == 'y') { std::cout << input << std::endl; return true; }
			if (input == 'n') { std::cout << input << std::endl; return false; }

			if (input == '\n' || input == '\r' || input == ' ') { std::cout << (val_default?'y':'n') << std::endl; return val_default; }
		}
	}

	void rip_split(std::string full, std::string& part0, std::string& part1, char delim) {
		if (full.find(delim) != std::string::npos) { //Contains delim
			std::string o0 = full.substr(0, full.find(delim));
			std::string o1 = full.substr(full.find(delim) + 1, full.length() - full.find(delim));

			part0 = o0;
			part1 = o1;

			return;
		}
		else { //Doesn't contain delim
			part0 = full;
			part1 = "";
		}
	}

	std::string make_url_safe(std::string in) {
		std::string out(in);

		size_t index = 0;
		while (true) {
			/* Locate the substring to replace. */
			index = out.find(" ", index);
			if (index == std::string::npos) break;

			/* Make the replacement. */
			out.replace(index, 1, "_");

			/* Advance index forward so the next iteration doesn't pick it up as well. */
			index += 1;
		}

		return out;
	}

	void trim_padding(std::string& s, char delim) {
		size_t i_start;
		for (i_start = 0; s.c_str()[i_start] == delim && i_start < s.length(); i_start++);

		size_t i_end;
		for (i_end = s.length()-1; s.c_str()[i_end] == delim && i_end >= 0; i_end--);

		s = s.substr(i_start, i_end-i_start+1);
	}

	std::vector<std::string> dir_list(std::string dirpath, std::string fext) {
		std::vector<std::string> names;
		std::string search_path = dirpath + "/*"+fext;//"/*.*";
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

	void vector_print(std::vector<std::string> x) {
		std::cout << "{ ";
		for (std::string i : x) {
			std::cout << i << " ";
		}
		std::cout << "}";
	}

	bool vector_contains(std::string element, std::vector<std::string> vec) {
		for (std::string i : vec) {
			if (element == i) return true;
		}
		return false;
	}
}