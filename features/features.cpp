#include <includes.h>

void itemhelper::tp_player_to_actor( SDK::APawn* my_player, SDK::AActor* target )
{
	if ( !my_player || !target ) return;
	SDK::FVector loc = target->K2_GetActorLocation( );
	my_player->K2_SetActorLocation( loc, false, nullptr, true );
}

void itemhelper::bring_actor_to_player( SDK::APawn* my_player, SDK::AActor* target )
{
	if ( !my_player || !target ) return;
	SDK::FVector me = my_player->K2_GetActorLocation( );
	target->K2_SetActorLocation( me, false, nullptr, true );
}

void features::run( SDK::UWorld* world, SDK::APawn* my_player, SDK::APlayerController* player_controller )
{
	if ( !world || !my_player || !player_controller )
		return;

	variables::globals::world = world;
	variables::globals::my_player = my_player;
	variables::globals::player_controller = player_controller;

	auto game_state = world->GameState;
	if ( !game_state ) return;

	auto players = game_state->PlayerArray;
	for ( int i = 0; i < players.Num( ); i++ )
	{
		auto player_state = players[ i ];
		if ( !player_state ) continue;

		auto pawn = player_state->PawnPrivate;
		if ( !pawn ) continue;

		auto character = reinterpret_cast< SDK::ACharacter* >( pawn );
		if ( !character || !character->Mesh ) continue;

		if ( pawn == my_player )
		{
			auto state = pawn->PlayerState;
			if ( !state ) continue;

			//features::exploits::fly::run( character );
			features::exploits::speed::run( character );
			features::exploits::fullbright::run( world );
			features::exploits::freeze_ghost::run( world );
			features::debug::lookatnames::run( player_controller );
			continue;
		}

		auto mesh = character->Mesh;
		features::esp::players::draw( pawn, my_player, mesh, player_controller );
	}

	for ( int i = 0; i < world->Levels.Num( ); i++ )
	{
		auto level = world->Levels[ i ];
		if ( !level )
			continue;

		for ( int j = 0; j < level->Actors.Num( ); j++ )
		{
			auto actor = level->Actors[ j ];
			if ( !actor )
				continue;

			features::esp::entities::draw_ghost( actor, my_player, player_controller );
			features::debug::draw_hungryghost_bone_ids( actor, player_controller );
			features::esp::entities::draw( actor, my_player, player_controller );
		}
	}
}

/*auto players = world->game_state->player_array;
	for ( auto i = 0; i < players.size( ); i++ )
	{
		const auto player = players[ i ];
		if ( !player ) continue;

		const auto pawn = player->pawn_private;
		if ( !pawn ) continue;
		if ( pawn == my_player )
		{
			const auto state = pawn->player_state;
			if ( !state ) continue;

			continue;
		}

		const auto mesh = pawn->mesh;
		if ( !mesh ) continue;

		features::esp::players::draw( pawn, my_player, mesh, player_controller );
	}*/