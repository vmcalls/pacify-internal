#include "includes.h"
#include "hooks/hooks.h"

void initialize( const HMODULE module )
{
	try
	{
		utils::console::initialize( _( "pacify internal" ) );
		ue4::sdk::initialize( );
		hooks::initialize( );
	}

	catch ( const std::runtime_error& error )
	{
		LI_FN( MessageBoxA )( nullptr, error.what( ), _( "pacify internal" ), MB_OK | MB_ICONERROR );
		LI_FN( FreeLibraryAndExitThread )( module, 0 );
	}

	while ( !LI_FN( GetAsyncKeyState )( VK_END ) )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
	}

	LI_FN( FreeLibraryAndExitThread )( module, 0 );
}

bool DllMain( const HMODULE module, const std::uint32_t call_reason, void* reserved [[maybe_unused]] )
{
	LI_FN( DisableThreadLibraryCalls )( module );

	if ( call_reason == DLL_PROCESS_ATTACH )
	{
		if ( const auto handle = LI_FN( CreateThread )( nullptr, NULL, reinterpret_cast< unsigned long( __stdcall* )( void* ) >( initialize ), module, NULL, nullptr ) )
			LI_FN( CloseHandle )( handle );
	}
	else if ( call_reason == DLL_PROCESS_DETACH )
	{
		hooks::release( );
	}

	return true;

}
