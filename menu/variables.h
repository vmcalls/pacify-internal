#pragma once

namespace ui_items
{
	struct entry { std::string name; SDK::AActor* actor = nullptr; };

	inline std::vector<entry> cache;
	inline char search_buf[ 128 ] = {};
	inline int selected = -1;

	inline void refresh( SDK::UWorld* world )
	{
		cache.clear( );
		if ( !world ) return;

		for ( int li = 0; li < world->Levels.Num( ); ++li )
		{
			auto level = world->Levels[ li ];
			if ( !level ) continue;

			for ( int ai = 0; ai < level->Actors.Num( ); ++ai )
			{
				auto actor = level->Actors[ ai ];
				if ( !actor ) continue;

				std::string nm = actor->GetName( );
				cache.push_back( { nm, actor } );
			}
		}
		if ( selected >= ( int )cache.size( ) ) selected = -1;
	}

	inline bool name_matches( const std::string& nm, const char* needle )
	{
		if ( !needle || !*needle ) return true;
		return nm.find( needle ) != std::string::npos;
	}
}

namespace variables::globals
{
	inline SDK::UWorld* world = nullptr;
	inline SDK::APawn* my_player = nullptr;
	inline SDK::APlayerController* player_controller = nullptr;
}

namespace variables::menu
{
	inline bool opened{ true };
}

namespace variables::players
{
	inline bool name{ false };
	inline bool skeleton{ false };
	inline bool snapline{ false };

	inline float survivor_color[ 4 ]{ 1.f, 1.f, 1.f, 1.f };
	inline float killer_color[ 4 ]{ 1.f, 0.f, 0.f, 1.f };
}

namespace itemhelper
{
	void tp_player_to_actor( SDK::APawn* my_player, SDK::AActor* target );
	void bring_actor_to_player( SDK::APawn* my_player, SDK::AActor* target );
}

namespace ghost_filter
{
	struct see_pawn_params { SDK::APawn* pawn; };

	// void (UPrimitiveComponent* overlapped_comp, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult& sweep_result)
	struct begin_overlap_params
	{
		SDK::UPrimitiveComponent* overlapped_comp;
		SDK::AActor* other_actor;
		SDK::UPrimitiveComponent* other_comp;
		int32_t                   other_body_index;
		bool                      b_from_sweep;
		uint8_t                   pad_[ 3 ];
		SDK::FHitResult           sweep_result;
	};

	inline bool should_block_for_me( SDK::UObject* obj, SDK::UFunction* fn, void* params )
	{
		if ( !obj || !fn || !params ) return false;

		std::string obj_name = obj->GetName( );
		if ( obj_name.find( "HungryGhost" ) == std::string::npos && obj_name.find( "Scary_" ) == std::string::npos ) return false;

		std::string fn_name = fn->GetFullName( );
		if ( fn_name.empty( ) ) fn_name = fn->GetName( );

		if ( fn_name.find( "SeePawnDelegate" ) != std::string::npos )
		{
			auto* p = reinterpret_cast< see_pawn_params* >( params );
			return ( p && p->pawn == variables::globals::my_player );
		}

		if ( fn_name.find( "ComponentBeginOverlapSignature" ) != std::string::npos )
		{
			auto* p = reinterpret_cast< begin_overlap_params* >( params );
			return ( p && p->other_actor == reinterpret_cast< SDK::AActor* >( variables::globals::my_player ) );
		}

		return false;
	}
}

namespace variables::entities
{
	inline bool hungryghost_esp{ false };
	inline float hungryghost_color[ 4 ]{ 0.2f, 0.5f, 0.9f, 1.f };

	inline bool chicken_esp{ false };
	inline float chicken_color[ 4 ]{ 0.2f, 0.5f, 0.9f, 1.f };

	inline bool poile_esp{ false };
	inline float poile_color[ 4 ]{ 0.2f, 0.5f, 0.9f, 1.f };

	inline bool windmil_esp{ false };
	inline float windmil_color[ 4 ]{ 0.2f, 0.5f, 0.9f, 1.f };

	inline bool poisonbag_esp{ false };
	inline float poisonbag_color[ 4 ]{ 0.2f, 0.5f, 0.9f, 1.f };

	inline float max_distance{ 30.f };
}

namespace variables::misc
{
	inline bool fly_ex{ false };
	inline bool speed_ex{ false };
	inline bool fullbright{ false };
	inline bool ignore_by_ai{ false };
	inline bool freeze_ghost{ false };

}
