#pragma once

class Joystick: public NonCopyable
{
private:
    SDL_Joystick* joystick=nullptr;
public:
	using GUID=SDL_JoystickGUID;
	enum class Type: uint8
	{
		Unknown=SDL_JOYSTICK_TYPE_UNKNOWN,
		GameController=SDL_JOYSTICK_TYPE_GAMECONTROLLER,
		Wheel=SDL_JOYSTICK_TYPE_WHEEL,
		ArcadeStick=SDL_JOYSTICK_TYPE_ARCADE_STICK,
		FlightStick=SDL_JOYSTICK_TYPE_FLIGHT_STICK,
		DancePad=SDL_JOYSTICK_TYPE_DANCE_PAD,
		Guitar=SDL_JOYSTICK_TYPE_GUITAR,
		DrumKit=SDL_JOYSTICK_TYPE_DRUM_KIT,
		ArcadePad=SDL_JOYSTICK_TYPE_ARCADE_PAD,
		Throttle=SDL_JOYSTICK_TYPE_THROTTLE
	};
    enum class Hat: uint8
    {
        Centred=SDL_HAT_CENTERED,
        Up=SDL_HAT_UP,
        Down=SDL_HAT_DOWN,
        Right=SDL_HAT_RIGHT,
        Left=SDL_HAT_LEFT,
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
    uint32 IdOf(int device_index);
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
    static void Lock();
    static void Unlock();
    bool IsAttached();
    GUID UniqueId();
    static GUID UniqueIdOf(int device_index);
	Power PowerState();
    static std::string StringFromGUID(GUID guid);
    static GUID StringToGUID(std::string str);
    uint16 Vendor();
    static uint16 VendorOf(int device_index);
    uint16 Product();
    static uint16 ProductOf(int device_index);
    uint16 ProductVersion();
    static uint16 ProductVersionOf(int device_index);
    Type Kind();
    static Type KindOf(int device_index);
};
