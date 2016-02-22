#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

int main( void ) {
	std::string strInput;
	std::getline( std::cin, strInput );

	auto start = std::chrono::high_resolution_clock::now( );

	std::cout << strInput;
	strInput.resize( strInput.size( ) - 1 );
	std::reverse( strInput.begin( ), strInput.end( ) );
	std::cout << strInput << std::endl;

	auto end = std::chrono::high_resolution_clock::now( );
	std::cout << "took: " << std::chrono::duration< double, std::milli >( end - start ).count( ) << " ms" << std::endl;

	std::cin.ignore( );
	std::cin.get( );
	return 1;
}