#pragma once

namespace ue4::sdk
{
	inline std::uintptr_t unlock_items;
	inline std::uintptr_t set_fov;

	// u_canvas
	inline SDK::UFont* font;
	inline SDK::UObject* draw_box;
	inline SDK::UObject* draw_line;
	inline SDK::UObject* draw_text;
	inline SDK::UObject* draw_polygon;
	inline SDK::UObject* text_size;

	// a_player_controller
	inline SDK::UObject* world_to_screen;

	// a_actor
	inline SDK::UObject* get_actor_location;
	inline SDK::UObject* get_actor_rotation;
	inline SDK::UObject* get_actor_bounds;
	inline SDK::UObject* get_distance_to;
	inline SDK::UObject* enable_input;
	inline SDK::UObject* disable_input;

	// a_pawn
	inline SDK::UObject* launch_character;

	// a_player_camera_maanger
	inline SDK::UObject* get_camera_rotation;

	// u_skeletal_mesh_component
	inline std::uintptr_t bone_matrix;
	inline SDK::UObject* get_bone_name;
	inline SDK::UObject* get_bones_num;

	// a_dbd_game_state
	inline SDK::UObject* get_player_game_state;

	// u_gameplay_statics
	inline SDK::UObject* get_delta_time;

	bool initialize( );
}