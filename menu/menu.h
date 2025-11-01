#pragma once
#include "variables.h"

namespace menu
{
	bool initialize( );
	void handle_input( SDK::APawn* my_player, SDK::APlayerController* player_controller );
	void render( );
}