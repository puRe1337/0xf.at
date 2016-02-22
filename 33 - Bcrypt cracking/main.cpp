#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include "bcrypt.h"


std::vector< std::string > g_vPasswords;
std::vector< std::string > g_vHashes;

void ReadPasswords( void ) {
	std::ifstream pws( "commonpasswords.txt", std::ifstream::in );
	if ( pws.is_open( ) ) {
		std::string strLine;
		while ( std::getline( pws, strLine ) ) {
			g_vPasswords.push_back( strLine );
		}
		pws.close( );
	}
}

void ReadHashes( void ) {
	std::ifstream hashes( "hashes.txt", std::ifstream::in );
	if ( hashes.is_open( ) ) {
		std::string strLine;
		while ( std::getline( hashes, strLine ) ) {
			g_vHashes.push_back( strLine );
		}
		hashes.close( );
	}
}

std::string findPasswordFromHash( void ) {
	std::string strFound;
	for ( auto& word : g_vPasswords ) {
		if ( !strFound.empty( ) )
			return strFound;

		std::vector<std::thread> vThreads;
		std::mutex mu;
		for ( auto& hash : g_vHashes ) {
			vThreads.push_back( std::thread( [ & ]( ) {
				mu.lock( );
				Bcrypt bcrypt;
				bcrypt.setPrefix( "2y" );
				bcrypt.setCost( 10 );
				bcrypt.setKey( word );
				bcrypt.setHash( hash );
				if ( bcrypt.compare( ) ) {
					strFound = word;
					std::cout << "Found! Hash: " << hash << " Word: " << word << std::endl;
				}
				mu.unlock( );
			} ) );
		}
		for ( auto& thread : vThreads )
			thread.join( );

	}
	return "nope";
}


int main( void ) {
	ReadPasswords( );
	ReadHashes( );

	auto start = std::chrono::high_resolution_clock::now( );

	auto pw = findPasswordFromHash( );
	std::cout << pw << std::endl;

	auto end = std::chrono::high_resolution_clock::now( );

	std::cout << "took: " << std::chrono::duration_cast< std::chrono::minutes >( end - start ).count( ) << " min" << std::endl;

	std::cin.ignore( );
	std::cin.get( );
	return 1;
}
