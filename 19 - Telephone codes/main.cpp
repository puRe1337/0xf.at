#include <iostream>
#include <string>
#include <chrono>

typedef struct {
	char letter;
	int iNumber;
}Codes_t;

Codes_t g_Codes[] = {
	{ 'a', 4 },
	{ 'b', 6 },
	{ 'c', 8 },
	{ 'd', 6 },
	{ 'e', 9 },
	{ 'f', 12 },
	{ 'g', 8 },
	{ 'h', 12 },
	{ 'i', 16 },
	{ 'j', 10 },
	{ 'k', 15 },
	{ 'l', 20 },
	{ 'm', 12 },
	{ 'n', 18 },
	{ 'o', 24 },
	{ 'p', 14 },
	{ 'q', 21 },
	{ 'r', 28 },
	{ 's', 34 },
	{ 't', 16 },
	{ 'u', 24 },
	{ 'v', 32 },
	{ 'w', 18 },
	{ 'x', 27 },
	{ 'y', 36 },
	{ 'z', 45 },
	{ '1', 1 },
	{ '2', 2 },
	{ '3', 3 },
	{ '4', 4 },
	{ '5', 5 },
	{ '6', 6 },
	{ '7', 7 },
	{ '8', 8 },
	{ '9', 9 },
	{ '0', 0 },
};

int	getSum( const std::string& strInput ) {
	
	int sum = 0;
	for ( auto letter : strInput ) {
		for ( auto letter2 : g_Codes ) {
			if ( letter2.letter == letter ) {
				sum += letter2.iNumber;
			}
		}
	}
	return sum;
}

int main( void ) {
	std::string strInput;
	std::cin >> strInput;

	auto start = std::chrono::high_resolution_clock::now( );

	auto summe = getSum( strInput );
	std::cout << summe << std::endl;

	auto end = std::chrono::high_resolution_clock::now( );
	std::cout << "took: " << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count( ) << " microseconds" << std::endl;

	std::cin.ignore( );
	std::cin.get( );
	return 1;
}