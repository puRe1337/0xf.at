#pragma once
#include <vector>
#include <string>

namespace Utils {
	static std::vector<std::string> &split( std::string &s, char find, std::vector<std::string>& elements ) {
		std::stringstream ss( s );
		std::string item;
		while ( getline( ss, item, find ) ) {
			elements.push_back( item );
		}
		return elements;
	}

	static std::vector<std::string> split( std::string &s, char find ) {
		std::vector<std::string> elements;
		split( s, find, elements );
		return elements;
	}
}