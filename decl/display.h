#pragma once

struct DisplayMode
{
	friend Window;
	friend Display;
	Pixel::Format Format;
	Point Size;
	int RefreshRate;
	void* DriverData;
	DisplayMode()=default;
	DisplayMode(Pixel::Format fmt, Point wh, int rate, void* driverdata):Format(fmt), Size(wh), RefreshRate(rate), DriverData(driverdata) {}
private:
	DisplayMode(uint32 fmt, int w, int h, int rate, void* driverdata):DisplayMode(Pixel::Format(fmt), Point(w,h), rate, driverdata) {}
};

class Display
{
private:
	friend Window;
	uint32 index;
	Display(uint32 index):index(index){}
public:
	uint32 GetIndex()const
	{
		return index;
	}
	DisplayMode GetMode(int modeindex)const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetDisplayMode(index, modeindex, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode GetCurrentMode()const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetCurrentDisplayMode(index, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode GetDesktopMode()const
	{
		SDL_DisplayMode mode;
		Error::IfNegative(SDL_GetDesktopDisplayMode(index, &mode));
		return DisplayMode(mode.format, mode.w,mode.h, mode.refresh_rate, mode.driverdata);
	}
	DisplayMode GetClosestMode(DisplayMode mode)const
	{
		SDL_DisplayMode result, wantedmode={uint32(mode.Format), mode.Size.x, mode.Size.y, mode.RefreshRate, mode.DriverData};
		Error::IfZero(SDL_GetClosestDisplayMode(index, &wantedmode, &result));
		return DisplayMode(result.format, result.w,result.h, result.refresh_rate, result.driverdata);
	}
	Rect GetBounds()const
	{
		SDL_Rect rect;
		Error::IfNegative(SDL_GetDisplayBounds(index, &rect));
		return Rect(rect.x, rect.y, rect.w, rect.h);
	}
	Rect GetUsableBounds()const
	{
		SDL_Rect rect;
		Error::IfNegative(SDL_GetDisplayUsableBounds(index, &rect));
		return Rect(rect.x, rect.y, rect.w, rect.h);
	}
	std::string GetName()const
	{
        return std::string(Error::IfZero(SDL_GetDisplayName(index)));
	}
	float GetDiagonalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, &dpi, nullptr, nullptr));
		return dpi;
	}
	float GetVerticalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, nullptr, &dpi, nullptr));
		return dpi;
	}
	float GetHorizontalDPI()const
	{
		float dpi;
		Error::IfNegative(SDL_GetDisplayDPI(index, nullptr, nullptr, &dpi));
		return dpi;
	}
	uint32 GetNumberOfModes()const
	{
        return Error::IfNegative(SDL_GetNumDisplayModes(index));
	}
	static uint32 GetNumber()
	{
		return Error::IfNegative(SDL_GetNumVideoDisplays());
	}
};
namespace VideoDriver
{
std::string GetNameOfCurrent()
{
    return std::string(SDL_GetCurrentVideoDriver()?SDL_GetCurrentVideoDriver():"");
}
std::string GetName(uint32 index)
{
    return std::string(SDL_GetVideoDriver(index)?SDL_GetCurrentVideoDriver():"");
}
uint32 GetNumber()
{
	return Error::IfNegative(SDL_GetNumVideoDrivers());
}
}