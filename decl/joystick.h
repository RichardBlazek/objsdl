#pragma once

class Joystick: public NonCopyable
{
private:
    SDL_Joystick* joystick=nullptr;
public:
	using GUID=SDL_JoystickGUID;
    enum class HatState: uint8
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
    void Open(int device_index);
    Joystick(int device_index);
    ~Joystick();
    std::string Name();
    static std::string NameOf(int device_index);
    uint32 GetId();
    uint32 NumAxes();
    uint32 NumBalls();
    uint32 NumButtons();
    uint32 NumHats();
    static void Update();
    static uint32 Num();
    int16 GetAxis(int axis);
    Point GetBallPos(int ball);
    bool IsPressed(int button);
    HatState GetHatState(int hat);
    static void EnableEventPolling();
    static void DisableEventPolling();
    static bool IsEnabledEventPolling();
    bool IsAttached();
    GUID GetGUID();
	Power GetPower();
    static std::string GUID_ToString(GUID guid);
    static GUID GUID_FromString(std::string str);
};
