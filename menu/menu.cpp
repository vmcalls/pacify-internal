#include <includes.h>
#include "hooks/hooks.h"

bool menu::initialize( )
{
	ImGui::CreateContext( );
	ImGui_ImplWin32_Init( hooks::window );
	ImGui_ImplDX11_Init( d3d11::device, d3d11::context );

	auto& io = ImGui::GetIO( );
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui::StyleColorsDark( );

	auto& style = ImGui::GetStyle( );
	style.ScrollbarSize = 13.0f;
	style.WindowTitleAlign = ImVec2{ 0.5f, 0.5f };
	style.WindowRounding = 6.f;

	return true;
}

void menu::handle_input( SDK::APawn* my_player, SDK::APlayerController* player_controller )
{
	if ( variables::menu::opened )
	{
		my_player->DisableInput( player_controller );
	}
	else
	{
		my_player->EnableInput( player_controller );
	}
}

inline std::string to_lower( std::string s ) { for ( char& c : s ) c = ( char )tolower( ( unsigned char )c ); return s; }
inline bool contains_ci( const std::string& hay, const char* needle )
{
	if ( !needle || !*needle ) return true;
	std::string H = to_lower( hay ), N = to_lower( std::string( needle ) );
	return H.find( N ) != std::string::npos;
}

void menu::render( )
{
	auto& style = ImGui::GetStyle( );
	auto& io = ImGui::GetIO( );
	io.MouseDrawCursor = variables::menu::opened;

	static float alpha = 0.f;

	const auto& draw_list = ImGui::GetBackgroundDrawList( );
	draw_list->AddRectFilled( ImVec2{ 0.f, 0.f }, io.DisplaySize, ImColor{ 0.f, 0.f, 0.f, alpha } );

	if ( !variables::menu::opened )
	{
		alpha = std::fmax( alpha - io.DeltaTime * 3.0f, 0.f );
		style.Alpha = std::fmax( style.Alpha - io.DeltaTime * 6.0f, 0.f );
		return;
	}

	alpha = std::fmin( alpha + io.DeltaTime * 3.0f, 0.5f );
	style.Alpha = std::fmin( style.Alpha + io.DeltaTime * 6.0f, 1.f );

	static std::uint32_t selected_tab = 0;
	ImGui::SetNextWindowSize( ImVec2{ 560.f, 412.f }, ImGuiCond_Once );
	ImGui::Begin( _( "nigga.tw pacify" ), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );

	ImGui::BeginChild( _( "tabs" ), ImVec2{ 150, 0 }, true );

	static constexpr const char* tabs[ ]{
		"players",
		"entities",
		"misc",
		"items"
	};

	static constexpr const char* state_type[ ]{
		"none",
		"hooked",
		"trapped",
		"hiding",
		"dead",
		"caged"
	};

	for ( std::size_t i = 0; i < IM_ARRAYSIZE( tabs ); ++i )
	{
		if ( ImGui::Selectable( tabs[ i ], selected_tab == i ) )
		{
			selected_tab = i;
		}
	}

	ImGui::EndChild( );

	ImGui::SameLine( );

	ImGui::BeginGroup( );

	switch ( selected_tab )
	{
	case 0:
		ImGui::Text( _( "players esp" ) );
		ImGui::Separator( );
		ImGui::Spacing( );

		ImGui::Checkbox( "name", &variables::players::name );
		ImGui::Checkbox( "skeleton", &variables::players::skeleton );
		ImGui::Checkbox( "snapline", &variables::players::snapline );

		ImGui::Spacing( );
		ImGui::Spacing( );

		ImGui::Text( "survivor color" );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##survivor_color" ), variables::players::survivor_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Text( "killer color" );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##killer_color" ), variables::players::killer_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		break;
	case 1:
		ImGui::Text( "entities esp" );
		ImGui::Separator( );
		ImGui::Spacing( );

		ImGui::Checkbox( "Ghost", &variables::entities::hungryghost_esp );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##hungryghostesp" ), variables::entities::hungryghost_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Checkbox( "Chicken", &variables::entities::chicken_esp );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##chickenesp" ), variables::entities::chicken_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Checkbox( "Pan", &variables::entities::poile_esp );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##panesp" ), variables::entities::poile_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Checkbox( "Windmill Statue", &variables::entities::windmil_esp );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##windmillesp" ), variables::entities::windmil_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Checkbox( "Poison Bag", &variables::entities::poisonbag_esp );
		ImGui::SameLine( );
		ImGui::ColorEdit4( ( "##poinsonbgesp" ), variables::entities::poisonbag_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar );

		ImGui::Spacing( );
		ImGui::Spacing( );

		ImGui::Text( "max distance" );
		ImGui::SliderFloat( "##max_distance", &variables::entities::max_distance, 0.f, 100.f, "%.3gm", 1.f );
		break;
	case 2:
		ImGui::Text( "misc [MIGHT NOT WORK IF YOU ARE NOT THE HOST]" );
		ImGui::Separator( );
		ImGui::Spacing( );

		ImGui::Checkbox( "UFO (fly + noclip)", &variables::misc::fly_ex, false );
		ImGui::Checkbox( "Speed Hack", &variables::misc::speed_ex, false );
		ImGui::Checkbox( "Ghost ignores you", &variables::misc::ignore_by_ai, false );
		ImGui::Checkbox( "Freeze Ghost (BETA)", &variables::misc::freeze_ghost, false );
		break;
	case 3: // items
	{
		ImGui::Text( "items" );
		ImGui::Separator( );
		ImGui::Spacing( );

		// refresh controls
		if ( ImGui::Button( "refresh" ) )
		{
			ui_items::refresh( ( SDK::UWorld* )variables::globals::world ); // adjust to your world pointer
		}
		ImGui::SameLine( );
		ImGui::SetNextItemWidth( 220.f );
		ImGui::InputText( "search", ui_items::search_buf, IM_ARRAYSIZE( ui_items::search_buf ) );

		ImGui::Spacing( );

		// list + details
		ImGui::BeginChild( "items_list", ImVec2( 260.f, 260.f ), true );
		{
			// build filtered index list first
			static std::vector<int> filtered;
			filtered.clear( );
			filtered.reserve( ui_items::cache.size( ) );
			for ( int i = 0; i < ( int )ui_items::cache.size( ); ++i )
				if ( contains_ci( ui_items::cache[ i ].name, ui_items::search_buf ) )
					filtered.push_back( i );

			ImGuiListClipper clipper;
			clipper.Begin( ( int )filtered.size( ) );
			while ( clipper.Step( ) )
			{
				for ( int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row )
				{
					const int i = filtered[ row ];
					const auto& e = ui_items::cache[ i ];

					const bool is_sel = ( ui_items::selected == i );
					if ( ImGui::Selectable( e.name.c_str( ), is_sel ) )
						ui_items::selected = i;
				}
			}

			// clear selection if it fell out of filter
			if ( !ui_items::cache.empty( ) && ui_items::selected >= 0 )
			{
				bool still_visible = false;
				for ( int idx : filtered ) if ( idx == ui_items::selected ) { still_visible = true; break; }
				if ( !still_visible ) ui_items::selected = filtered.empty( ) ? -1 : filtered.front( );
			}
		}
		ImGui::EndChild( );

		ImGui::SameLine( );

		ImGui::BeginChild( "item_actions", ImVec2( 0, 260.f ), true );
		{
			if ( ui_items::selected >= 0 && ui_items::selected < ( int )ui_items::cache.size( ) )
			{
				auto* picked = ui_items::cache[ ui_items::selected ].actor;
				ImGui::Text( "selected:" );
				ImGui::TextWrapped( "%s", ui_items::cache[ ui_items::selected ].name.c_str( ) );
				ImGui::Spacing( );

				if ( ImGui::Button( "teleport to", ImVec2( 140.f, 0.f ) ) )
					itemhelper::tp_player_to_actor( ( SDK::APawn* )variables::globals::my_player, picked );


				if ( ImGui::Button( "bring to me", ImVec2( 140.f, 0.f ) ) )
					itemhelper::bring_actor_to_player( ( SDK::APawn* )variables::globals::my_player, picked );
			}
			else
			{
				ImGui::TextDisabled( "no item selected" );
			}
		}
		ImGui::EndChild( );
	}
	break;

	default:
		break;
	}

	ImGui::EndGroup( );

	ImGui::End( );
}