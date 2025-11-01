#include "../includes.h"

bool ue4::sdk::initialize( )
{
	// u_canvas
	ue4::sdk::font = reinterpret_cast< SDK::UFont* >( SDK::UObject::FindObject( _( "Font Roboto.Roboto" ) ) );
	ue4::sdk::draw_box = SDK::UObject::FindObject( _( "Function Engine.Canvas.K2_DrawBox" ) );
	ue4::sdk::draw_line = SDK::UObject::FindObject( _( "Function Engine.Canvas.K2_DrawLine" ) );
	ue4::sdk::draw_text = SDK::UObject::FindObject( _( "Function Engine.Canvas.K2_DrawText" ) );
	ue4::sdk::draw_polygon = SDK::UObject::FindObject( _( "Function Engine.Canvas.K2_DrawPolygon" ) );
	ue4::sdk::text_size = SDK::UObject::FindObject( _( "Function Engine.Canvas.K2_TextSize" ) );

	// a_player_controller
	ue4::sdk::world_to_screen = SDK::UObject::FindObject( _( "Function Engine.PlayerController.ProjectWorldLocationToScreen" ) );

	// a_actor
	ue4::sdk::get_actor_location = SDK::UObject::FindObject( _( "Function Engine.Actor.K2_GetActorLocation" ) );
	ue4::sdk::get_actor_rotation = SDK::UObject::FindObject( _( "Function Engine.Actor.K2_GetActorRotation" ) );
	ue4::sdk::get_actor_bounds = SDK::UObject::FindObject( _( "Function Engine.Actor.GetActorBounds" ) );
	ue4::sdk::get_distance_to = SDK::UObject::FindObject( _( "Function Engine.Actor.GetDistanceTo" ) );
	ue4::sdk::enable_input = SDK::UObject::FindObject( _( "Function Engine.Actor.EnableInput" ) );
	ue4::sdk::disable_input = SDK::UObject::FindObject( _( "Function Engine.Actor.DisableInput" ) );

	// a_pawn
	ue4::sdk::launch_character = SDK::UObject::FindObject( _( "Function Engine.Character.LaunchCharacter" ) );

	// a_player_camera_manager
	ue4::sdk::get_camera_rotation = SDK::UObject::FindObject( _( "Function Engine.PlayerCameraManager.GetCameraRotation" ) );

	// u_skeletal_mesh_component
	ue4::sdk::get_bone_name = SDK::UObject::FindObject( _( "Function Engine.SkinnedMeshComponent.GetBoneName" ) );
	ue4::sdk::get_bones_num = SDK::UObject::FindObject( _( "Function Engine.SkinnedMeshComponent.GetNumBones" ) );

	// u_gameplay_statics
	ue4::sdk::get_delta_time = SDK::UObject::FindObject( _( "Function Engine.GameplayStatics.GetWorldDeltaSeconds" ) );

	printf( "SDK Initialization done.\n" );
	return true;
}