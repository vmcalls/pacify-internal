#pragma once

namespace hooks
{
	inline HWND window;

	bool initialize( );
	bool release( );
}

namespace hooks::post_render
{
	void __stdcall hook( SDK::UObject* viewport_client, SDK::UCanvas* canvas );
	using draw_transition = void( * )( SDK::UObject* viewport_client, SDK::UCanvas* canvas );
	inline draw_transition draw_transition_o = 0;
}

namespace hooks::present
{
	inline std::once_flag flag;
	using fn = long( __stdcall* )( IDXGISwapChain*, unsigned int, unsigned int );
	inline fn original;
	long __stdcall hook( IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags );
}

namespace hooks::wndproc
{
	using fn = std::int64_t( __stdcall* )( HWND, UINT, WPARAM, LPARAM );
	inline fn original;
	std::int64_t __stdcall hook( HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam );
}