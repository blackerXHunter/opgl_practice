#pragma once
#include <string>
#include <sstream>

std::string int_to_string(const int i) {
	return std::to_string(i);
}

int string_to_int(const std::string &s) {
	return std::stoi(s.c_str());
}