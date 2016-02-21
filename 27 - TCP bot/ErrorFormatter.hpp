#pragma once
#include <string>
#include <sstream>

class ErrorFormatter {
public:
	ErrorFormatter( ) {}
	~ErrorFormatter( ) {}

	template<typename T>
	ErrorFormatter& operator<<( const T& t ) {
		m_sstream << t;
		return *this;
	}

	std::string str( void ) const { return m_sstream.str( ); }
	operator std::string( ) const { return m_sstream.str( ); }

	enum ConvertToString {
		to_str
	};
	std::string operator >> ( ConvertToString ) { return m_sstream.str( ); }
private:
	std::stringstream m_sstream;
};