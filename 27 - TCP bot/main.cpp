#include <iostream>
#include "Client.h"
#include "Utils.hpp"

bool g_botOn = false;

void recvCallback( Client* pClient, const std::string& strText ) {
	std::cout << strText << std::endl;
	if ( g_botOn ) {
		std::vector<std::string> splitted;
		if ( strText.find( "*" ) != std::string::npos ) {
			splitted = Utils::split( strText, '*' );
			if ( splitted.size( ) > 1 ) {
				// splitted.back( ).resize( splitted.back( ).size( ) - 3 );
				// std::stoi will ignore any text - http://en.cppreference.com/w/cpp/string/basic_string/stol

				int sum = std::stoi( splitted.front( ) ) * std::stoi( splitted.back( ) );

				pClient->Send( std::to_string( sum ).c_str( ) );;
			}
		}
	}

	if ( strText.find( "GO" ) != std::string::npos )
		g_botOn = true;
}

int main( ) {
	SetConsoleTitle( "0xf.at TCP Bot" );
	try
	{
		Client client( "212.17.118.125", 2727 );
		client.SetRecvCallback( recvCallback );
		std::string strLine;
		while ( strLine.compare("quit") != 0 ) {
			std::getline( std::cin, strLine );
			client.Send( strLine );
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}
	}
	catch ( const std::exception& e ) {
		std::cerr << e.what( ) << std::endl;
	}
	std::cin.get( );
	return 0;
}