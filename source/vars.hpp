#pragma once

#include "includes.hpp"

namespace var
{
	inline bool b_mouse_down { false };
	inline bool b_first_click { false };

	inline bool b_is_clicked { false };
	inline bool b_is_down { false };

	inline bool r_mouse_down{ false };
	inline bool r_first_click{ false };

	inline bool r_is_clicked{ false };
	inline bool r_is_down{ false };

	inline int i_clicks_this_session { 0 };

	inline long l_last_click_time;

	inline int r_clicks_this_session{ 0 };

	inline long r_last_click_time;
}