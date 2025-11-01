#pragma once

namespace render
{
	inline SDK::UCanvas* canvas{};
	inline SDK::FVector2D screen{ 0.f, 0.f };

	void text( SDK::FVector2D position, SDK::FString text, SDK::FLinearColor color );
	void circle( SDK::FVector2D position, float radius, SDK::FLinearColor color );
	void filled_circle( SDK::FVector2D position, float radius, SDK::FLinearColor color );
	void line( SDK::FVector2D position_1, SDK::FVector2D position_2, float thickness, SDK::FLinearColor color );
	SDK::FVector2D text_size( SDK::FString text );
}