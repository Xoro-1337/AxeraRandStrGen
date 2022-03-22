#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN) 
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

namespace Overlay
{
    void Loop();
}

namespace Render
{
    void UI();
}