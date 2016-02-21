#include <iostream>
#include "Client.h"

int main( ) {
	SetConsoleTitle( "0xf.at TCP Bot" );
	try
	{
		Client client( "212.17.118.125", 2727 );
		while ( 1 ) {
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}
	}
	catch ( const std::exception& e ) {
		std::cerr << e.what( ) << std::endl;
	}
	std::cin.get( );
	return 0;
}