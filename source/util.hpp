#pragma once

#include "includes.hpp"

namespace util
{
	namespace hooking
	{
		inline HHOOK hook_mouse;

		DWORD __stdcall work( );
		LRESULT __stdcall mouse( int nCode, WPARAM wParam, LPARAM lParam );
	}

	namespace input
	{
		void left_down( );
		void left_up( );
		void right_down();
		void right_up();
	}


	namespace string
	{
		template<typename ... args>
		static std::string format( const std::string &format, args ... arg )
		{
			const size_t size = std::snprintf( nullptr, 0, format.c_str( ), arg ... ) + 1;
			std::unique_ptr<char[]> buf( new char[ size ] );
			std::snprintf( buf.get( ), size, format.c_str( ), arg ... );
			return std::string( buf.get( ), buf.get( ) + size - 1 );
		}

		inline std::string random( int i_size )
		{
			static auto &chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

			thread_local static std::mt19937 rg { std::random_device{}( ) };
			thread_local static std::uniform_int_distribution<std::string::size_type> pick( 0, sizeof( chars ) - 2 );

			std::string string;
			string.reserve( i_size );

			while ( i_size-- )
				string += chars[ pick( rg ) ];

			return string;
		}

		inline std::string to_lower( std::string str )
		{
			transform( str.begin( ), str.end( ), str.begin( ), static_cast< int( * )( int ) >( ::tolower ) );
			return str;
		}

		inline std::string to_upper( std::string str )
		{
			transform( str.begin( ), str.end( ), str.begin( ), static_cast< int( * )( int ) >( ::toupper ) );
			return str;
		}
	}

	namespace math
	{
		inline int random_int( int i_start, int i_end )
		{
			std::random_device rd;
			std::mt19937 rng( rd( ) );
			const std::uniform_int_distribution<int> uni( i_start, i_end );

			return static_cast< int >( uni( rng ) );
		}
	}

	namespace window
	{
		inline std::string get_active_window_title( )
		{
			char title[ 256 ];
			HWND hwnd = LI_FN( GetForegroundWindow ).cached( )( );
			LI_FN( GetWindowTextA ).cached( )( hwnd, title, sizeof( title ) );
			return title;
		}

		inline HWND get_active_window_handle( )
		{
			return LI_FN( GetForegroundWindow ).cached( )( );
		}
	}

}
