#pragma once

struct DisplayMode
{
	friend Window;
	friend Display;
	Pixel::Format format;
	Point size;
	int refresh_rate;
	void* driver_data;
	DisplayMode()=default;
	DisplayMode(Pixel::Format fmt, Point wh, int rate, void* driverdata)
		:format(fmt), size(wh), refresh_rate(rate), driver_data(driverdata) {}
private:
	DisplayMode(uint32 fmt, int w, int h, int rate, void* driverdata)
		:DisplayMode(Pixel::Format(fmt), Point(w,h), rate, driverdata) {}
};

class Display
{
private:
	friend Window;
	uint32 index;
	Display(uint32 index):index(index){}
public:
	uint32 Index()const
	{
		return index;
	}
	DisplayMode Mode(int modeindex)const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetDisplayMode(index, modeindex, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode CurrentMode()const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetCurrentDisplayMode(index, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode DesktopMode()const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetDesktopDisplayMode(index, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode ClosestMode(DisplayMode mode)const
	{
		SDL_DisplayMode result, wantedmode={uint32(mode.format), mode.size.x, mode.size.y, mode.refresh_rate, mode.driver_data};
		Error::IfZero(SDL_GetClosestDisplayMode(index, &wantedmode, &result));
		return DisplayMode(result.format, result.w, result.h, result.refresh_rate, result.driverdata);
	}
	Rect Bounds()const
	{
		SDL_Rect rect;
		Error::IfNegative(SDL_GetDisplayBounds(index, &rect));
		return Rect(rect.x, rect.y, rect.w, rect.h);
	}
	Rect UsableBounds()const
	{
		SDL_Rect rect;
		Error::IfNegative(SDL_GetDisplayUsableBounds(index, &rect));
		return Rect(rect.x, rect.y, rect.w, rect.h);
	}
	std::string Name()const
	{
        return std::string(Error::IfZero(SDL_GetDisplayName(index)));
	}
	float DiagonalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, &dpi, nullptr, nullptr));
		return dpi;
	}
	float VerticalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, nullptr, &dpi, nullptr));
		return dpi;
	}
	float HorizontalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, nullptr, nullptr, &dpi));
		return dpi;
	}
	uint32 CountOfModes()const
	{
        return Error::IfNegative(SDL_GetNumDisplayModes(index));
	}
	static uint32 Count()
	{
		return Error::IfNegative(SDL_GetNumVideoDisplays());
	}
};
namespace VideoDriver
{
std::string NameOfCurrent()
{
    return std::string(SDL_GetCurrentVideoDriver()?SDL_GetCurrentVideoDriver():"");
}
std::string Name(uint32 index)
{
    return std::string(SDL_GetVideoDriver(index)?SDL_GetVideoDriver(index):"");
}
uint32 Count()
{
	return Error::IfNegative(SDL_GetNumVideoDrivers());
}
}