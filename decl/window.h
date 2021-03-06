#pragma once

#include "display.h"

struct GammaRamp
{
	uint16 r[16];
	uint16 g[16];
	uint16 b[16];
	GammaRamp()=default;
	GammaRamp(uint16* r, uint16* g, uint16* b)
	{
		for(uint8 i=0; i<16; ++i)
		{
			this->r[i]=r[i];
			this->g[i]=g[i];
			this->b[i]=b[i];
		}
	}
};

class Window: public NonCopyable
{
private:
	//Intern C window
	SDL_Window* window=nullptr;
public:
	friend Renderer;
	friend void MessageBox::Show(const std::string&, const std::string&, Flags flag, Window*);
	friend size_t MessageBox::Dialog(const std::string&, const std::string&, const std::vector<std::string>&, size_t, size_t, Flags, ColorScheme*, Window*);
	friend Cursor;
	constexpr static Point UndefinedPos=Point(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	constexpr static Point CenteredPos=Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	enum class HitTestResult: uint8
	{
		Normal=SDL_HITTEST_NORMAL,  ///Region has no special properties
		Draggable=SDL_HITTEST_DRAGGABLE,  ///Region can drag entire window
		TopLeft=SDL_HITTEST_RESIZE_TOPLEFT,
		Top=SDL_HITTEST_RESIZE_TOP,
		TopRight=SDL_HITTEST_RESIZE_TOPRIGHT,
		Right=SDL_HITTEST_RESIZE_RIGHT,
		BottomRight=SDL_HITTEST_RESIZE_BOTTOMRIGHT,
		Bottom=SDL_HITTEST_RESIZE_BOTTOM,
		BottomLeft=SDL_HITTEST_RESIZE_BOTTOMLEFT,
		Left=SDL_HITTEST_RESIZE_LEFT
	};
	using HitTest=std::function<HitTestResult(Window&, Point)>;
	enum class Flags:uint32
	{
		None=0,
		Fullscreen=SDL_WINDOW_FULLSCREEN,		///fullscreen window
		OpenGL=SDL_WINDOW_OPENGL,				///window usable with OpenGL context
		Shown=SDL_WINDOW_SHOWN,					///window is visible
		Hidden=SDL_WINDOW_HIDDEN,				///window is not visible
		Borderless=SDL_WINDOW_BORDERLESS,		///no window decoration
		Resizable=SDL_WINDOW_RESIZABLE,			///window can be resized
		Minimized=SDL_WINDOW_MINIMIZED,			///window is minimized
		Maximized=SDL_WINDOW_MAXIMIZED,			///window is maximized
		InputGrabbed=SDL_WINDOW_INPUT_GRABBED,	///window has grabbed input focus
		InputFocus=SDL_WINDOW_INPUT_FOCUS,		///window has input focus
		MouseFocus=SDL_WINDOW_MOUSE_FOCUS,		///window has mouse focus
		FullscreenDesktop=SDL_WINDOW_FULLSCREEN_DESKTOP,
		Foreign=SDL_WINDOW_FOREIGN,				///window not created by SDL
		AllowHighDPI=SDL_WINDOW_ALLOW_HIGHDPI,	///window should be created in high-DPI mode if supported
		MouseCapture=SDL_WINDOW_MOUSE_CAPTURE,	///window has mouse captured (unrelated to INPUT_GRABBED)
		AllwaysOnTop=SDL_WINDOW_ALWAYS_ON_TOP,	/// window should always be above others
		SkipTaskbar=SDL_WINDOW_SKIP_TASKBAR,	/// window should not be added to the taskbar
		Utility=SDL_WINDOW_UTILITY,				/// window should be treated as a utility window
		Tooltip=SDL_WINDOW_TOOLTIP,				/// window should be treated as a tooltip
		PopupMenu=SDL_WINDOW_POPUP_MENU			/// window should be treated as a popup menu
	};
	//Constructor
	Window()=default;
	//Constructor with parameters
	Window(const std::string& title, Rect pos, Flags flags=Flags::None);
	//Move
	Window(Window&&)noexcept;
	Window& operator=(Window&&)noexcept;
	//Destroying Window
	void Close()noexcept;
	//Destructor
	~Window()noexcept
	{
		Close();
	}
	//Window methods
	void Minimize()noexcept
	{
		SDL_MinimizeWindow(window);
	}
	void Maximize()noexcept
	{
		SDL_MaximizeWindow(window);
	}
	void Raise()noexcept
	{
		SDL_RaiseWindow(window);
	}
	void Restore()noexcept
	{
		SDL_RestoreWindow(window);
	}
	void Hide()noexcept
	{
		SDL_HideWindow(window);
	}
	void Show()noexcept
	{
		SDL_ShowWindow(window);
	}
	Point Position()noexcept
	{
		Point result;
		SDL_GetWindowPosition(window, &result.x, &result.y);
		return result;
	}
	void Move(Point newPoint)noexcept
	{
		SDL_SetWindowPosition(window, newPoint.x, newPoint.y);
	}
	Point Size()noexcept
	{
		Point result;
		SDL_GetWindowSize(window, &result.x, &result.y);
		return result;
	}
	void Resize(Point newSize)noexcept
	{
		SDL_SetWindowSize(window, newSize.x, newSize.y);
	}
	uint32 Id()noexcept
	{
		return SDL_GetWindowID(window);
	}
	Flags Options()noexcept
	{
		return Flags(SDL_GetWindowFlags(window));
	}
	float Brightness()noexcept
	{
		return SDL_GetWindowBrightness(window);
	}
	void SetBrightness(float brightness)
	{
		Error::IfNegative(SDL_SetWindowBrightness(window, brightness));
	}
	float Opacity()noexcept
	{
		float opacity=0;
		Error::IfNegative(SDL_GetWindowOpacity(window, &opacity));
		return opacity;
	}
	void SetOpacity(float opacity)
	{
		Error::IfNegative(SDL_SetWindowOpacity(window, opacity));
	}
	//Advanced window methods
	bool IsGrabbed()noexcept
	{
		return bool(SDL_GetWindowGrab(window));
	}
	void GrabInput()noexcept
	{
		SDL_SetWindowGrab(window, SDL_TRUE);
	}
	void SetInputFocus()noexcept
	{
		Error::IfNegative(SDL_SetWindowInputFocus(window));
	}
	void SetResizability(bool on)noexcept
	{
		SDL_SetWindowResizable(window, SDL_bool(on));
	}
	void ReleaseInput()noexcept
	{
		SDL_SetWindowGrab(window, SDL_FALSE);
	}
	uint32 DisplayIndex()noexcept
	{
		return uint32(Error::IfNegative(SDL_GetWindowDisplayIndex(window)));
	}
	std::string Title()noexcept
	{
		return std::string(SDL_GetWindowTitle(window));
	}
	void SetTitle(const std::string& title)
	{
		SDL_SetWindowTitle(window, title.c_str());
	}
	void BeModalFor(Window& parent)
	{
        Error::IfNegative(SDL_SetWindowModalFor(window, parent.window));
	}
	void* Data(const std::string& name)
	{
		return SDL_GetWindowData(window, name.c_str());
	}
	void SetData(const std::string& name, void* data)
	{
		SDL_SetWindowData(window, name.c_str(),data);
	}
	void DisableFullscreen()
	{
		Error::IfNegative(SDL_SetWindowFullscreen(window, 0));
	}
	void EnableFullscreen(bool fullscreen_desktop)
	{
		Error::IfNegative(SDL_SetWindowFullscreen(window, fullscreen_desktop?SDL_WINDOW_FULLSCREEN_DESKTOP:SDL_WINDOW_FULLSCREEN));
	}
	SDL::DisplayMode DisplayMode()
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetWindowDisplayMode(window, &mode));
		return SDL::DisplayMode(mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata);
	}
	void SetDisplayMode(const SDL::DisplayMode& mode)
	{
		SDL_DisplayMode mod{uint32(mode.format), mode.size.x, mode.size.y, mode.refresh_rate, mode.driver_data};
		Error::IfNegative(SDL_SetWindowDisplayMode(window, &mod));
	}
	void SetIcon(Surface& image)noexcept;
	Point MaxSize()noexcept
	{
		Point result;
		SDL_GetWindowMaximumSize(window, &result.x, &result.y);
		return result;
	}
	void SetMaxSize(Point newMaxSize)noexcept
	{
		SDL_SetWindowMaximumSize(window, newMaxSize.x, newMaxSize.y);
	}
	Point MinSize()noexcept
	{
		Point result;
		SDL_GetWindowMinimumSize(window, &result.x, &result.y);
		return result;
	}
	void SetMinSize(Point newMinSize)noexcept
	{
		SDL_SetWindowMinimumSize(window, newMinSize.x, newMinSize.y);
	}
	void AddBorder()noexcept
	{
		SDL_SetWindowBordered(window, SDL_TRUE);
	}
	void RemoveBorder()noexcept
	{
		SDL_SetWindowBordered(window, SDL_FALSE);
	}
	SDL::GammaRamp GammaRamp()
	{
		SDL::GammaRamp result;
		Error::IfNegative(SDL_GetWindowGammaRamp(window, result.r,result.g,result.b));
		return result;
	}
	void SetGammaRamp(const SDL::GammaRamp& gammaramp)
	{
		Error::IfNegative(SDL_SetWindowGammaRamp(window, gammaramp.r, gammaramp.g, gammaramp.b));
	}
	uint32 UpBorderSize()const
	{
        int size;
        Error::IfNegative(SDL_GetWindowBordersSize(window, &size, nullptr, nullptr, nullptr));
        return size;
	}
	uint32 LeftBorderSize()const
	{
        int size;
        Error::IfNegative(SDL_GetWindowBordersSize(window, nullptr, &size, nullptr, nullptr));
        return size;
	}
	uint32 DownBorderSize()const
	{
        int size;
        Error::IfNegative(SDL_GetWindowBordersSize(window, nullptr, nullptr, &size, nullptr));
        return size;
	}
	uint32 RightBorderSize()const
	{
        int size;
        Error::IfNegative(SDL_GetWindowBordersSize(window, nullptr, nullptr, nullptr, &size));
        return size;
	}
	void SetHitTest(HitTest callback)
	{
		Error::IfNegative(SDL_SetWindowHitTest(window, [](SDL_Window* win, const SDL_Point* area, void* data)->SDL_HitTestResult
		{
			Window window;
			window.window=win;
			auto result=(*(HitTest*)data)(window, Point(area->x, area->y));
			window.window=nullptr;
			return SDL_HitTestResult(result);
		}, (void*)&callback));
	}
	void DisableHitTesting()
	{
		Error::IfNegative(SDL_SetWindowHitTest(window, nullptr, nullptr));
	}
};
Window::Flags operator|(Window::Flags first, Window::Flags second)noexcept
{
	return Window::Flags(uint32(first)|uint32(second));
}
Window::Flags operator&(Window::Flags first, Window::Flags second)noexcept
{
	return Window::Flags(uint32(first)&uint32(second));
}
Window::Flags operator^(Window::Flags first, Window::Flags second)noexcept
{
	return Window::Flags(uint32(first)^uint32(second));
}
Window::Flags operator|=(Window::Flags& first, Window::Flags second)noexcept
{
	return first=(first|second);
}
Window::Flags operator&=(Window::Flags& first, Window::Flags second)noexcept
{
	return first=(first&second);
}
Window::Flags operator^=(Window::Flags& first, Window::Flags second)noexcept
{
	return first=(first^second);
}
Window::Flags operator~(Window::Flags param)noexcept
{
	return Window::Flags(~uint32(param));
}