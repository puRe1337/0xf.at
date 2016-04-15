#include <iostream>
#include "Client.h"

int main( ) {
	SetConsoleTitle( "0xf.at Easy Sockets" );
	try
	{
		Client client( "212.17.118.125", 2323 );
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