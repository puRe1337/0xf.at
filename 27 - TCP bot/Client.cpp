#include "Client.h"


Client::Client( std::string strIP, __int32 iPort )
{
	Connect( strIP, iPort );
}

Client::~Client( )
{
}

void Client::Send( const std::string& strText )
{
	send( m_iSocket, strText.c_str( ), strText.length( ), 0 );
}

void Client::SetRecvCallback( std::function<void( Client*, const std::string& )> fn )
{
	m_fnRecvCallback = fn;
}

void Client::Connect( std::string strIP, __int32 iPort )
{
	WSADATA wsaData;
	auto res = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	if ( res != 0 ) {
		WSACleanup( );
		return throw std::exception( (ErrorFormatter( ) << "Error at WSAStartup(), Error: " << res >> ErrorFormatter::to_str).c_str() );
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory( &hints, sizeof( hints ) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	res = getaddrinfo( strIP.c_str( ), std::to_string( iPort ).c_str( ), &hints, &result );
	if ( res != 0 ) {
		WSACleanup( );
		return throw std::exception( ( ErrorFormatter( ) << "Error at getaddrinfo(), Error: " << res >> ErrorFormatter::to_str ).c_str( ) );
	}

	for ( ptr = result; ptr != NULL; ptr = ptr->ai_next ) {
		m_iSocket = socket( ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol );
		if ( m_iSocket == INVALID_SOCKET ) {
			WSACleanup( );
			return throw std::exception( ( ErrorFormatter( ) << "Error at socket(), Error: " << WSAGetLastError( ) >> ErrorFormatter::to_str ).c_str( ) );
		}

		res = connect( m_iSocket, ptr->ai_addr, ( int )ptr->ai_addrlen );
		if ( res == SOCKET_ERROR ) {
			closesocket( m_iSocket );
			m_iSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo( result );

	if ( m_iSocket == INVALID_SOCKET ) {
		WSACleanup( );
		return throw std::exception( ( ErrorFormatter( ) << "Can't connect to server" >> ErrorFormatter::to_str ).c_str( ) );
	}

	std::thread( &Client::InfiniteRead, this ).detach( );
}

void Client::InfiniteRead( void )
{
	int res = 0;
	do 
	{
		std::string strText( "", 2048 );
		res = recv( m_iSocket, &strText[ 0 ], strText.length( ), NULL );
		if ( res > 0 ) {
			strText.resize( res );

			m_fnRecvCallback( this, strText );
		}
		
	} while ( res != 0 );
	std::cout << "Connection closed" << std::endl;
}