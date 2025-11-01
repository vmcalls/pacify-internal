#include <includes.h>
#include <unordered_set>

struct ABoundingBox
{
private:
    bool valid;
public:
    struct SDK::FVector2D Min, Max;

    ABoundingBox( class SDK::USkeletalMeshComponent* mesh ,SDK::APlayerController* player_controller ) noexcept;

    explicit operator bool( ) const noexcept
    {
        return valid;
    }
};

enum udbone
{
    root = 0,
    pelvis = 1,
    cc_base_pelvis = 2,
    spine_01 = 3,
    spine_02 = 4,
    spine_03 = 5,
    neck_01 = 6,
    cc_base_necktwist02 = 7,
    head = 8,
    cc_base_facialbone = 9,
    cc_base_jawroot = 10,
    cc_base_tongue01 = 11,
    cc_base_tongue02 = 12,
    cc_base_tongue03 = 13,
    cc_base_teeth02 = 14,
    cc_base_r_eye = 15,
    cc_base_l_eye = 16,
    cc_base_upperjaw = 17,
    cc_base_teeth01 = 18,
    clavicle_l = 19,
    upperarm_l = 20,
    lowerarm_l = 21,
    cc_base_l_forearmtwist01 = 22,
    cc_base_l_elbowsharebone = 23,
    hand_l = 24,
    middle_01_l = 25,
    middle_02_l = 26,
    middle_03_l = 27,
    index_01_l = 28,
    index_02_l = 29,
    index_03_l = 30,
    ring_01_l = 31,
    ring_02_l = 32,
    ring_03_l = 33,
    pinky_01_l = 34,
    pinky_02_l = 35,
    pinky_03_l = 36,
    thumb_01_l = 37,
    thumb_02_l = 38,
    thumb_03_l = 39,
    lowerarm_twist_01_l = 40,
    upperarm_twist_01_l = 41,
    cc_base_l_upperarmtwist02 = 42,
    clavicle_r = 43,
    upperarm_r = 44,
    upperarm_twist_01_r = 45,
    cc_base_r_upperarmtwist02 = 46,
    lowerarm_r = 47,
    cc_base_r_forearmtwist01 = 48,
    cc_base_r_elbowsharebone = 49,
    hand_r = 50,
    middle_01_r = 51,
    middle_02_r = 52,
    middle_03_r = 53,
    ring_01_r = 54,
    ring_02_r = 55,
    ring_03_r = 56,
    thumb_01_r = 57,
    thumb_02_r = 58,
    thumb_03_r = 59,
    index_01_r = 60,
    index_02_r = 61,
    index_03_r = 62,
    pinky_01_r = 63,
    pinky_02_r = 64,
    pinky_03_r = 65,
    lowerarm_twist_01_r = 66,
    cc_base_r_ribstwist = 67,
    cc_base_r_breast = 68,
    cc_base_l_ribstwist = 69,
    cc_base_l_breast = 70,
    thigh_l = 71,
    calf_l = 72,
    foot_l = 73,
    cc_base_l_toebasesharebone = 74,
    ball_l = 75,
    cc_base_l_pinkytoe1 = 76,
    cc_base_l_ringtoe1 = 77,
    cc_base_l_midtoe1 = 78,
    cc_base_l_indextoe1 = 79,
    cc_base_l_bigtoe1 = 80,
    calf_twist_01_l = 81,
    cc_base_l_kneesharebone = 82,
    cc_base_l_calftwist02 = 83,
    thigh_twist_01_l = 84,
    cc_base_l_thightwist02 = 85,
    thigh_r = 86,
    thigh_twist_01_r = 87,
    calf_r = 88,
    foot_r = 89,
    ball_r = 90,
    cc_base_r_pinkytoe1 = 91,
    cc_base_r_bigtoe1 = 92,
    cc_base_r_indextoe1 = 93,
    cc_base_r_midtoe1 = 94,
    cc_base_r_ringtoe1 = 95,
};

namespace features::bones
{
    constexpr int chest_top_2 = ( int )udbone::spine_03;       // top of chest/upper spine
    constexpr int l_arm_top = ( int )udbone::upperarm_l;     // left upper arm
    constexpr int r_arm_top = ( int )udbone::upperarm_r;     // right upper arm
    constexpr int l_elbow = ( int )udbone::lowerarm_l;     // left elbow joint
    constexpr int r_elbow = ( int )udbone::lowerarm_r;     // right elbow joint
    constexpr int l_wrist = ( int )udbone::hand_l;         // left wrist/hand root
    constexpr int r_wrist = ( int )udbone::hand_r;         // right wrist/hand root
    constexpr int pelvis_1 = ( int )udbone::pelvis;         // pelvis root
    constexpr int r_thigh = ( int )udbone::thigh_r;        // right thigh
    constexpr int l_thigh = ( int )udbone::thigh_l;        // left thigh
    constexpr int l_knee = ( int )udbone::calf_l;         // left knee/calf
    constexpr int r_knee = ( int )udbone::calf_r;         // right knee/calf
    constexpr int l_foot_root = ( int )udbone::foot_l;         // left foot root
    constexpr int r_foot_root = ( int )udbone::foot_r;         // right foot root
    constexpr int l_foot_low = ( int )udbone::ball_l;         // left foot tip/ball
    constexpr int r_foot_low = ( int )udbone::ball_r;         // right foot tip/ball

    constexpr int bone_array[ ] =
    {
        chest_top_2,
        l_arm_top, r_arm_top,
        l_elbow,   r_elbow,
        l_wrist,   r_wrist,
        pelvis_1,
        r_thigh,   l_thigh,
        l_knee,    r_knee,
        l_foot_root, r_foot_root,
        l_foot_low,  r_foot_low
    };
}

static inline SDK::FVector get_bone_world_pos( SDK::USkeletalMeshComponent* mesh, int bone_index )
{
    SDK::FName bone_name = mesh->GetBoneName( bone_index );
    return mesh->GetSocketLocation( bone_name );
}

ABoundingBox::ABoundingBox( SDK::USkeletalMeshComponent* mesh, SDK::APlayerController* player_controller ) noexcept
{
    if ( !mesh || !player_controller ) { valid = false; return; }

    SDK::FVector head3D = get_bone_world_pos( mesh, ( int )udbone::head );
    SDK::FVector bottom3D = get_bone_world_pos( mesh, 0 );

    SDK::FVector2D head2D{}, bottom2D{};
    if ( !player_controller->ProjectWorldLocationToScreen( head3D, &head2D, false ) || !player_controller->ProjectWorldLocationToScreen( bottom3D, &bottom2D, false ) )
    {
        valid = false;
        return;
    }

    Min = head2D;
    Max = head2D;

    for ( auto bone_id : features::bones::bone_array )
    {
        SDK::FVector bone3D = get_bone_world_pos( mesh, bone_id );
        SDK::FVector2D bone2D{};

        if ( !player_controller->ProjectWorldLocationToScreen( bone3D, &bone2D, false ) ) continue;

        Min.X = SDK::UKismetMathLibrary::Min( Min.X, bone2D.X );
        Min.Y = SDK::UKismetMathLibrary::Min( Min.Y, bone2D.Y );
        Max.X = SDK::UKismetMathLibrary::Max( Max.X, bone2D.X );
        Max.Y = SDK::UKismetMathLibrary::Max( Max.Y, bone2D.Y );
    }

    float w = Max.X - Min.X;
    float h = Max.Y - Min.Y;
    Min.X -= w * 0.1f;
    Max.X += w * 0.1f;
    Min.Y -= h * 0.20f;   // top
    Max.Y += h * 0.05f;   // bottom padding

    valid = true;
}

void features::esp::players::draw( SDK::APawn* pawn, SDK::APawn* my_player, SDK::USkeletalMeshComponent* mesh, SDK::APlayerController* player_controller )
{

}

void features::esp::entities::draw_ghost( SDK::AActor* actor, SDK::APawn* my_player, SDK::APlayerController* player_controller )
{
    if ( !actor || !my_player || !player_controller ) return;

    std::string name_str = actor->GetName( );
    if ( name_str.find( "HungryGhost" ) == std::string::npos && name_str.find( "Scary_MP" ) == std::string::npos ) return;

    auto character = reinterpret_cast< SDK::ACharacter* >( actor );
    if ( !character || !character->Mesh ) return;

    SDK::USkeletalMeshComponent* ghost_mesh = character->Mesh;
    ABoundingBox CurrentBox{ ghost_mesh, player_controller };
    if ( !CurrentBox ) return;

    SDK::FLinearColor box_color( 1.f, 0.f, 0.f, 1.f );

    render::line( { CurrentBox.Min.X, CurrentBox.Min.Y }, { CurrentBox.Max.X, CurrentBox.Min.Y }, 1, box_color ); // top
    render::line( { CurrentBox.Min.X, CurrentBox.Min.Y }, { CurrentBox.Min.X, CurrentBox.Max.Y }, 1, box_color ); // left
    render::line( { CurrentBox.Max.X, CurrentBox.Max.Y }, { CurrentBox.Min.X, CurrentBox.Max.Y }, 1, box_color ); // bottom
    render::line( { CurrentBox.Max.X, CurrentBox.Max.Y }, { CurrentBox.Max.X, CurrentBox.Min.Y }, 1, box_color ); // right

    std::wstring name_w = L"Karen";
    SDK::FString name_fstr( name_w.c_str( ) );

    float center_x = ( CurrentBox.Min.X + CurrentBox.Max.X ) * 0.5f;
    render::text( { center_x, CurrentBox.Min.Y - 17.f }, name_fstr, box_color );

    SDK::FVector my_loc = my_player->K2_GetActorLocation( );
    SDK::FVector ghost_loc = actor->K2_GetActorLocation( );

    float distance_cm = ( ghost_loc - my_loc ).GetDistanceTo( 0 );
    float distance_m = distance_cm / 100.f;

    std::string dist_ascii = "[" + std::to_string( ( int )distance_m ) + "m]";
    std::wstring dist_w( dist_ascii.begin( ), dist_ascii.end( ) );
    SDK::FString dist_fstr( dist_w.c_str( ) );

    render::text( { center_x, CurrentBox.Max.Y + 4.f }, dist_fstr, box_color );
}

void features::esp::entities::draw( SDK::AActor* actor, SDK::APawn* my_player, SDK::APlayerController* player_controller )
{
    if ( !actor || !my_player || !player_controller ) return;

    std::string name_str = actor->GetName( );
    SDK::FVector2D screen_position;
    if ( !player_controller->ProjectWorldLocationToScreen( actor->K2_GetActorLocation( ), &screen_position, false ) ) return;

    std::wstring name_w( name_str.begin( ), name_str.end( ) );
    SDK::FString name_label( name_w.c_str( ) );
    std::wstring scratch_w;

    auto draw = [ & ]( bool enabled, const char* needle, const char* custom_text, const float col_arr[ 4 ] )
    {
        if ( !enabled ) return;
        if ( name_str.find( needle ) == std::string::npos ) return;

        SDK::FLinearColor col{ col_arr[ 0 ], col_arr[ 1 ], col_arr[ 2 ], col_arr[ 3 ] };

        SDK::FString text_to_draw = name_label;
        if ( custom_text && custom_text[ 0 ] != '\0' )
        {
            scratch_w.assign( custom_text, custom_text + std::strlen( custom_text ) );
            text_to_draw = SDK::FString( scratch_w.c_str( ) );
        }

        render::text( screen_position, text_to_draw, col );
    };

    draw( variables::entities::hungryghost_esp, "HungryGhost", "Ghost", variables::entities::hungryghost_color );
    draw( variables::entities::chicken_esp, "Chicken_Alive_C", "Chicken", variables::entities::windmil_color );
    draw( variables::entities::poile_esp, "WeaponPan", "Pan", variables::entities::poile_color );
    draw( variables::entities::windmil_esp, "Activate_Windmill_Statue", "Windmill Statue", variables::entities::windmil_color );
    draw( variables::entities::poisonbag_esp, "PoisonBag", "Poison bag", variables::entities::poisonbag_color );
}


void features::debug::draw_hungryghost_bone_ids( SDK::AActor* actor, SDK::APlayerController* player_controller )
{
    //if ( !actor || !player_controller ) return;

    //std::string name_str = actor->GetName( );
    //if ( name_str.find( "HungryGhost" ) == std::string::npos ) return;

    //auto character = reinterpret_cast< SDK::ACharacter* >( actor );
    //if ( !character || !character->Mesh ) return;
    //auto mesh = character->Mesh;

    //std::string dump;
    //dump.reserve( 16 * 1024 );

    //int sw = 0, sh = 0;
    //player_controller->GetViewportSize( &sw, &sh );
    //float x = 40.f, y = 40.f;

    //SDK::FLinearColor col{ 0.55f, 0.85f, 1.f, 1.f };

    //const int32_t bone_count = mesh->GetNumBones( );
    //for ( int32_t i = 0; i < bone_count; ++i )
    //{
    //    // bone id text
    //    std::string id_ascii = "[" + std::to_string( i ) + "]";
    //    std::wstring id_w( id_ascii.begin( ), id_ascii.end( ) );
    //    SDK::FString id_fstr( id_w.c_str( ) );

    //    // bone name text
    //    SDK::FName bone_fname = mesh->GetBoneName( i );
    //    std::string bone_ascii = bone_fname.ToString( );    // std::string in your SDK
    //    dump += "[" + std::to_string( i ) + "] " + bone_ascii + "\n";

    //    const std::string out_path = get_exe_dir( ) + "\\HungryGhost_Bones.txt";
    //    const bool ok = write_text_file( out_path, dump );

    //    std::wstring name_w( bone_ascii.begin( ), bone_ascii.end( ) );
    //    SDK::FString bone_name_fstr( name_w.c_str( ) );

    //    // draw
    //    render::text( { x,      y }, id_fstr, col );
    //    render::text( { x + 50.f, y }, bone_name_fstr, col );

    //    y += 14.f;
    //}
}

void features::debug::lookatnames::run( SDK::APlayerController* controller )
{
    if ( !controller || !controller->PlayerCameraManager ) return;

    auto cam_mgr = controller->PlayerCameraManager;
    SDK::FVector  cam_loc = cam_mgr->GetCameraLocation( );
    SDK::FRotator cam_rot = cam_mgr->GetCameraRotation( );

    SDK::FVector forward = SDK::UKismetMathLibrary::GetForwardVector( cam_rot );
    SDK::FVector trace_end = cam_loc + forward * 5000.f;

    SDK::FHitResult hit{};
    SDK::TArray<SDK::AActor*> ignore{};
    SDK::FLinearColor trace_col{ 1.f,1.f,1.f,1.f };
    SDK::FLinearColor hit_col{ 1.f,0.f,0.f,1.f };

    const bool got = SDK::UKismetSystemLibrary::LineTraceSingle(
        controller,                                 // WorldContextObject
        cam_loc, trace_end,                         // Start / End
        SDK::ETraceTypeQuery::TraceTypeQuery1,      // pick any valid channel
        true,                                       // bTraceComplex
        ignore,                                     // ActorsToIgnore
        SDK::EDrawDebugTrace::None,                 // DrawDebugType
        &hit,                                       // OutHit
        true,                                       // bIgnoreSelf
        trace_col,                                  // TraceColor
        hit_col,                                    // TraceHitColor
        0.0f                                        // DrawTime
    );

    SDK::AActor* hit_actor = got ? hit.Actor.Get( ) : nullptr;
    if ( !hit_actor ) return;

    std::string  name_str = hit_actor->GetName( );
    std::wstring name_w( name_str.begin( ), name_str.end( ) );
    SDK::FString label( name_w.c_str( ) );

    int w = 0, h = 0;
    controller->GetViewportSize( &w, &h );
    SDK::FVector2D pos{ ( w > 0 ? w * 0.5f : 960.f ), 50.f };

    SDK::FLinearColor col{ 1.f,1.f,1.f,1.f };
    render::text( pos, label, col );
}