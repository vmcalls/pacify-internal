#include "../includes.h"

void render::text( const SDK::FVector2D position, const SDK::FString text, const SDK::FLinearColor color )
{
	if ( canvas )
	{
		canvas->K2_DrawText(
			ue4::sdk::font,                     // UFont* RenderFont
			text,                     // FString RenderText
			position,                 // FVector2D ScreenPosition
			{ 1.f, 1.f },             // FVector2D Scale
			color,                    // FLinearColor RenderColor
			1.f,                      // float Kerning
			SDK::FLinearColor( ),      // FLinearColor ShadowColor
			SDK::FVector2D( ),         // FVector2D ShadowOffset
			true,                     // bool bCentreX
			false,                    // bool bCentreY
			true,                     // bool bOutlined
			{ 0.f, 0.f, 0.f, 1.f }    // FLinearColor OutlineColor
		);
	}
}

void render::circle( const SDK::FVector2D position, const float radius, const SDK::FLinearColor color )
{
	if ( canvas )
	{
		constexpr float step = 3.14f / 16;

		for ( auto i = 0.f; i < 2.f * 3.14f; i += step )
		{
			const SDK::FVector2D from{ position.X + std::cosf( i - step ) * radius, position.Y + std::sinf( i - step ) * radius };
			const SDK::FVector2D to{ position.X + std::cosf( i ) * radius, position.Y + std::sinf( i ) * radius };

			render::line( from, to, 1.f, color );
		}
	}
}

void render::filled_circle( const SDK::FVector2D position, const float radius, const SDK::FLinearColor color )
{
	if ( canvas )
	{
		canvas->K2_DrawPolygon( nullptr, position, { radius, radius }, 32, color );
	}
}

void render::line( const SDK::FVector2D position_1, const SDK::FVector2D position_2, const float thickness, const SDK::FLinearColor color )
{
	if ( canvas )
	{
		canvas->K2_DrawLine( position_1, position_2, thickness, color );
	}
}

SDK::FVector2D render::text_size( const SDK::FString text )
{
	if ( canvas )
	{
		const auto text_size = canvas->K2_TextSize( ue4::sdk::font, text, { 1.f, 1.f } );
		return { text_size.X, text_size.Y };
	}

	return { 0, 0 };
}