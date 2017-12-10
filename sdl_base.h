#pragma once

///SDL-Error
class Error: public std::exception
{
private:
    std::string message;
public:
	///Constructor
    Error()noexcept:message(SDL_GetError())
    {
        SDL_ClearError();
    }
    Error(const std::string& txt)noexcept:message(txt){}
    static void Condition(bool cond)
    {
    	if(cond)
		{
			throw Error();
		}
    }
    template<typename IntegralType>
    static IntegralType IfZero(IntegralType value)
    {
    	Condition(value==0);
    	return value;
    }
    template<typename IntegralType>
    static IntegralType IfNegative(IntegralType value)
    {
    	Condition(value<0);
    	return value;
    }
    ~Error()=default;
    virtual const char* what()const noexcept override
    {
    	return message.c_str();
    }
    void Show()const;
};

class Init
{
public:
	Init()
	{
		constexpr auto sdl_flags=SDL_INIT_EVERYTHING;
		constexpr auto img_flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP;
		SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
		Error::IfNegative(SDL_Init(sdl_flags));
		Error::Condition((IMG_Init(img_flags)&img_flags)!=img_flags);
		Error::IfNegative(TTF_Init());
	}
	~Init()
	{
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
};

constexpr bool IsBigEndian=(SDL_BYTEORDER==SDL_BIG_ENDIAN);

std::string GetPlatform()
{
	return SDL_GetPlatform();
}