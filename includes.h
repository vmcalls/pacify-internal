#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <list>
#include <sstream>
#include <mutex>
#include <utility>
#include <cstdint>
#include <future>
#include <array>
#include <d3d11.h>

#include "SDK/Engine_classes.hpp"

namespace globals
{
	inline SDK::UGameViewportClient* viewport_client = nullptr;
	inline SDK::UCanvas* canvas = nullptr;
	inline float clipX, clipY, centerX, centerY;
	inline SDK::FVector2D cursor, cursorCorrected, start{ 140,140 }, end{ 520, 585 }, screenSize{ 1920, 1080 };
}

#include "utils/utils.h"
#include "utils/libraries/minhook/MinHook.h"
#include "utils/libraries/xor.h"
#include "utils/libraries/lazy_importer.h"
#include "utils/libraries/fnv.h"

#include "utils/libraries/imgui/imgui.h"
#include "utils/libraries/imgui/imgui_impl_dx11.h"
#include "utils/libraries/imgui/imgui_impl_win32.h"
#include "utils/libraries/imgui/imgui_internal.h"

#include "hooks/vftable.h"
#include "ue4/ue4.h"

#include "menu/d3d11/d3d11.h"
#include "menu/menu.h"
#include "features/features.h"
#include "render/render.h"