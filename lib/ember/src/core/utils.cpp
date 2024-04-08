#include "utils.hpp"

#include <fstream>

std::optional<std::string> ember::readFile(std::filesystem::path path) {
	std::ifstream f(path);

	if(!f.is_open()) {
		return {};
	}

	f.seekg(0, std::ios::end);
	auto size = f.tellg();
	std::string buffer(size, ' ');
	f.seekg(0);
	f.read(&buffer[0], size); 

	return buffer;
}