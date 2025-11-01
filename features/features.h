#pragma once

namespace features
{
	void run( SDK::UWorld* world, SDK::APawn* my_player, SDK::APlayerController* player_controller );
}

namespace features::esp::players
{
	void draw( SDK::APawn* pawn, SDK::APawn* my_player, SDK::USkeletalMeshComponent* mesh, SDK::APlayerController* player_controller );
}

namespace features::esp::entities
{
	void draw( SDK::AActor* actor, SDK::APawn* my_player, SDK::APlayerController* player_controller );
	void draw_ghost( SDK::AActor* actor, SDK::APawn* my_player, SDK::APlayerController* player_controller );
}

namespace features::exploits::speed
{
	void run( SDK::ACharacter* character );
}

namespace features::exploits::fullbright
{
	void run( SDK::UWorld* world );
}

namespace features::exploits::freeze_ghost
{
	void run( SDK::UWorld* world );
}

namespace features::exploits::fly
{
	void run( SDK::ACharacter* character );
}

namespace features::debug::lookatnames
{
	void run( SDK::APlayerController* pc );
}

namespace features::debug
{
	void draw_hungryghost_bone_ids( SDK::AActor* actor, SDK::APlayerController* player_controller );
}