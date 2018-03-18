#pragma once

class Joystick: public NonCopyable
{
private:
    SDL_Joystick* joystick=nullptr;
public:
	using GUID=SDL_JoystickGUID;
    enum class Hat: uint8
    {
        Centred=0x0,
        Up=0x1,
        Down=0x2,
        Right=0x4,
        Left=0x8,
        RightUp=Right|Up,
        LeftUp=Left|Up,
        RightDown=Right|Down,
        LeftDown=Left|Down
    };
	enum class Power: int8
	{
		Unknown=SDL_JOYSTICK_POWER_UNKNOWN,
		Empty=SDL_JOYSTICK_POWER_EMPTY,
		Low=SDL_JOYSTICK_POWER_LOW,
		Medium=SDL_JOYSTICK_POWER_MEDIUM,
		Full=SDL_JOYSTICK_POWER_FULL,
		Wired=SDL_JOYSTICK_POWER_WIRED,
		Max=SDL_JOYSTICK_POWER_MAX,
	};
    Joystick()=default;
    Joystick(Joystick&& joy);
    Joystick& operator=(Joystick&& joy);
    bool IsOpened()
	{
		return bool(joystick);
	}
    void Close();
    Joystick(int device_index);
    ~Joystick();
    std::string Name();
    static std::string NameOf(int device_index);
    uint32 Id();
    uint32 CountOfAxes();
    uint32 CountOfBalls();
    uint32 CountOfButtons();
    uint32 CountOfHats();
    static void Update();
    static uint32 Count();
    int16 Axis(uint32 axis);
    Point Ball(uint32 ball);
    bool IsPressed(uint32 button);
    Hat HatPosition(uint32 hat);
    static void EnableEventPolling();
    static void DisableEventPolling();
    static bool IsEnabledEventPolling();
    bool IsAttached();
    GUID UniqueId();
	Power PowerState();
    static std::string StringFromGUID(GUID guid);
    static GUID StringToGUID(std::string str);
};
