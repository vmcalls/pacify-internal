#include "../includes.h"
#include "hooks.h"
#include <unordered_set>

using t_processevent = void( __fastcall* )( SDK::UObject* self, SDK::UFunction* fn, void* params ); 
static t_processevent o_processevent = nullptr;

static std::unordered_set<std::string> seen;

void __fastcall hk_processevent( SDK::UObject* obj, SDK::UFunction* fn, void* params )
{
    if ( variables::misc::ignore_by_ai )
        if ( ghost_filter::should_block_for_me( obj, fn, params ) ) return;

    o_processevent( obj, fn, params );
}

bool hooks::initialize( )
{
    SDK::UWorld* world = SDK::UWorld::GetWorld( );
    if ( !world ) return false;

    auto gi = world->OwningGameInstance;
    if ( !gi ) return false;

    auto locals = gi->LocalPlayers;
    if ( !locals ) return false;

    auto local_player = locals[ 0 ];
    if ( !local_player );

    auto viewport = local_player->ViewportClient;
    if ( !viewport ) return false;

    auto any_obj = reinterpret_cast< SDK::UObject* >( world );
    if ( !any_obj ) return false;

    void** vtable = *reinterpret_cast< void*** >( any_obj );
    void* target = vtable[ SDK::Offsets::ProcessEventIdx ];

    if ( MH_Initialize( ) != MH_OK ) throw std::runtime_error( _( "failed to initialize min_hook" ) );
    if ( MH_CreateHook( target, &hk_processevent, reinterpret_cast< void** >( &o_processevent ) ) != MH_OK ) return false;

    if ( d3d11::initialize( ) )
    {
        if ( MH_CreateHook( reinterpret_cast< void* >( d3d11::get_present( ) ), &present::hook, reinterpret_cast< void** >( &present::original ) ) != MH_OK )
        throw std::runtime_error( _( "failed to hook present" ) );
    }

    if ( MH_EnableHook( nullptr ) != MH_OK )
    throw std::runtime_error( _( "failed to initialize hooks" ) );

    hooks::post_render::draw_transition_o = vmt<decltype( hooks::post_render::draw_transition_o )>( std::uintptr_t( viewport ), std::uintptr_t( hooks::post_render::hook ), 94 );
    return true;
}

bool hooks::release( )
{
    MH_Uninitialize( );

    MH_DisableHook( nullptr );
    MH_RemoveHook( nullptr );

    utils::console::release( );
    return true;
}