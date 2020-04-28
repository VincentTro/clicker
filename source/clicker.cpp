#pragma once

#include "clicker.hpp"

DWORD __stdcall clicker::work( LPVOID lParam )
{
	do
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );

		if ( config.clicker.enabled && var::b_mouse_down && util::window::get_active_window_title( ).find( config.clicker.window_title ) != std::string::npos )
		{
			if ( var::b_first_click )
			{
				std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
				util::input::left_up( );
				var::b_first_click = false;
			}
			else
			{
				auto random_delay = util::integer::random( ( int ) config.clicker.min_cps * 10, ( int ) config.clicker.max_cps * 10 );

				var::i_current_cps = random_delay / 10;

				if ( ( std::clock( ) - var::l_last_click_time ) > random_delay )
				{
					util::input::left_down( );
					var::l_last_click_time = std::clock( );

					std::this_thread::sleep_for( std::chrono::milliseconds( util::integer::random( 30, 50 ) ) );
					util::input::left_up( );

					var::i_clicks_this_session++;

					_log( LDEBUG, "random_delay %d clock %d last click time %d", random_delay, std::clock( ), var::l_last_click_time );

				}
			}
		}

	} while ( true );
}