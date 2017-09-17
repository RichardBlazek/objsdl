#pragma once

namespace WindowManagement
{
	using Type=SDL_SYSWM_TYPE;
	constexpr uint8 Unknown=SDL_SYSWM_UNKNOWN,
					Windows=SDL_SYSWM_WINDOWS,
					X11=SDL_SYSWM_X11,
					DirectFB=SDL_SYSWM_DIRECTFB,
					Cocoa=SDL_SYSWM_COCOA,
					Uikit=SDL_SYSWM_UIKIT,
					Wayland=SDL_SYSWM_WAYLAND,
					Mir=SDL_SYSWM_MIR,
					WinRT=SDL_SYSWM_WINRT,
					Android=SDL_SYSWM_ANDROID,
					Vivante=SDL_SYSWM_VIVANTE;
	using Info=SDL_SysWMinfo;
	using Message=SDL_SysWMmsg;
}