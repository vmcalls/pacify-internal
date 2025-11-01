#include <includes.h>
#include "../hooks.h"

void __stdcall hooks::post_render::hook( SDK::UObject* viewport_client, SDK::UCanvas* canvas )
{
    render::canvas = canvas;
    render::text( { 50.f, 50.f }, L"PACIFY INTERNAL", { 1.f, 1.f, 1.f, 1.f } );

    SDK::UWorld* world = SDK::UWorld::GetWorld( );
    if ( !world ) return;

    auto gi = world->OwningGameInstance;
    if ( !gi ) return;

    auto locals = gi->LocalPlayers;
    if ( !locals ) return;

    auto local_player = locals[ 0 ];
    if ( !local_player );

    auto pc = local_player->PlayerController;
    if ( !pc ) return;

    SDK::APawn* my_player = pc->AcknowledgedPawn;
    if ( !my_player ) return;

    globals::viewport_client = ( SDK::UGameViewportClient* )viewport_client;
    globals::canvas = canvas;

    globals::clipX = canvas->ClipX;
    globals::clipY = canvas->ClipY;

    globals::centerX = globals::clipX / 2;
    globals::centerY = globals::centerY / 2;

    globals::screenSize = { globals::clipX, globals::clipY };

    menu::handle_input( my_player, pc );
    features::run( world, my_player, pc );
    hooks::post_render::draw_transition_o( viewport_client, canvas );
}