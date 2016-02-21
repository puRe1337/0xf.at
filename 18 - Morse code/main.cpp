#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

typedef struct {
	std::string letter;
	std::string strMorse;
}Codes_t;

Codes_t g_Codes[] = {
	{ "a", ".-" },
	{ "b", "-..." },
	{ "c", "-.-." },
	{ "d", "-.." },
	{ "e", "." },
	{ "f", "..-." },
	{ "g", "--." },
	{ "h", "...." },
	{ "i", ".." },
	{ "j", ".---" },
	{ "k", "-.-" },
	{ "l", ".-.." },
	{ "m", "--" },
	{ "n", "-." },
	{ "o", "---" },
	{ "p", ".--." },
	{ "q", "--.-" },
	{ "r", ".-." },
	{ "s", "..." },
	{ "t", "-" },
	{ "u", "..-" },
	{ "v", "...-" },
	{ "w", ".--" },
	{ "x", "-..-" },
	{ "y", "-.--" },
	{ "z", "--.." },
	{ "1", ".----" },
	{ "2", "..---" },
	{ "3", "...--" },
	{ "4", "....-" },
	{ "5", "....." },
	{ "6", "-...." },
	{ "7", "--..." },
	{ "8", "---.." },
	{ "9", "----." },
	{ "0", "-----" }
};

std::vector<std::string> &split( std::string &s, char find, std::vector<std::string>& elements ) {
	std::stringstream ss( s );
	std::string item;
	while ( getline( ss, item, find ) ) {
		elements.push_back( item );
	}
	return elements;
}

std::vector<std::string> split( std::string &s, char find ) {
	std::vector<std::string> elements;
	split( s, find, elements );
	return elements;
}

std::string getPassword( std::string& strInput ) {
	auto splitted = split( strInput, ' ' );
	std::string strOut;
	for ( auto single : splitted ) {
		for ( auto code : g_Codes ) {
			if ( single.compare( code.strMorse ) == 0 ) {
				strOut.append( code.letter );
			}
		}
	}
	return strOut;
}


int main( void ) {
	std::string strInput;
	std::getline( std::cin, strInput );

	auto start = std::chrono::high_resolution_clock::now( );

	auto pw = getPassword( strInput );
	std::cout << pw << std::endl;

	auto end = std::chrono::high_resolution_clock::now( );
	std::cout << "took: " << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count( ) << " microseconds" << std::endl;

	std::cin.ignore( );
	std::cin.get( );
	system( "pause" );
	return 1;
}