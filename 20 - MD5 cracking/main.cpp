#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "md5.h"
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

std::vector< std::string > g_vPasswords;

void ReadPasswords( void ) {
	std::ifstream pws( "wordlist.txt", std::ifstream::in );
	if ( pws.is_open( ) ) {
		std::string strLine;
		while ( std::getline( pws, strLine ) ) {
			g_vPasswords.push_back( strLine );
		}
		pws.close( );
	}
}

std::string findPasswordFromHash( const std::string& strHash ) {
	for ( auto word1 : g_vPasswords ) {
		for ( auto word2 : g_vPasswords ) {
			std::string strModHash = word1 + word2;
			MD5 md5;
			md5( strModHash );
			if ( strHash.compare( md5.getHash( ) ) == 0 ) {
				return strModHash;
			}
		}
	}
	return "nope";
}

int main( void ) {
	ReadPasswords( );

	std::string strLine;
	std::cin >> strLine;

	auto start = std::chrono::high_resolution_clock::now( );

	auto pw = findPasswordFromHash( strLine );
	std::cout << pw << std::endl;
	OutputDebugString( pw.c_str( ) );
	OutputDebugString( "\n" );

	auto end = std::chrono::high_resolution_clock::now( );

	std::cout << "took: " << std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count( ) << " min" << std::endl;

	std::cin.ignore( );
	std::cin.get( );
	system( "pause" );
	return 1;
}