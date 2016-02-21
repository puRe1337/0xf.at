#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <chrono>

std::vector<std::string> g_vDictionary;

void ReadDictionary( void ) {
	std::ifstream dic( "dictionary.txt", std::ifstream::in );
	if ( dic.is_open( ) ) {
		std::string strLine;
		while ( std::getline( dic, strLine ) ) {
			g_vDictionary.push_back( strLine );
		}
		dic.close( );
	}
}

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

inline bool scanLength( const std::string& w1, const std::string& w2 ) {
	if ( w1.length( ) == w2.length( ) )
		return true;
	return false;
}

int main( void ) {
	ReadDictionary( );

	std::string strInput;
	std::cin >> strInput;

	auto start = std::chrono::high_resolution_clock::now( );
	
	auto splitted = split( strInput, ';' );

	auto sortFn = []( char a, char b ) { return a < b; };

	std::vector<std::string> vResults;

	for ( auto word : splitted ) {

		for ( auto dic : g_vDictionary ) {

			if ( !scanLength( word, dic ) )
				continue;

			std::string strInputSort = word;
			std::string strDicSort = dic;

			std::sort( strInputSort.begin( ), strInputSort.end( ), sortFn );
			std::sort( strDicSort.begin( ), strDicSort.end( ), sortFn );

			if ( strInputSort == strDicSort ) {
				vResults.push_back( dic );
				break;
			}
		}
	}

	if ( !vResults.empty( ) ) {
		std::copy( vResults.begin( ), vResults.end( ) - 1, std::ostream_iterator<std::string>( std::cout, ";" ) );
		std::cout << vResults.back( ) << std::endl;
	}
	else {
		std::cout << "FeelsBadMan :(" << std::endl;
	}

	auto end = std::chrono::high_resolution_clock::now( );
	std::cout << "took: " << std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count( ) << " ms" << std::endl;



	std::cin.ignore( );
	std::cin.get( );
	return 1;
}